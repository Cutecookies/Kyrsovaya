#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timeoptimization.h"
#include "costoptimization.h"
#include "combinedoptimization.h"
#include "reportgenerator.h"
#include "errorhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startValidator = std::make_unique<AddressValidator>();
    endValidator = std::make_unique<AddressValidator>();
    apiClient = std::make_shared<WorkWithAPI>();
    dbManager = std::make_shared<Database>();
    routeSearcher = std::make_unique<RouteSearcher>(apiClient, dbManager);

    connect(ui->searchButton, &QPushButton::clicked,
            this, &MainWindow::on_searchButton_clicked);
    connect(startValidator.get(), &AddressValidator::validationCompleted,
            this, &MainWindow::on_startAddressValidated);
    connect(endValidator.get(), &AddressValidator::validationCompleted,
            this, &MainWindow::on_endAddressValidated);
    connect(routeSearcher.get(), &RouteSearcher::routesFound,
            this, &MainWindow::on_routesFound);
    connect(routeSearcher.get(), &RouteSearcher::searchError,
            this, &MainWindow::on_searchError);
    connect(ui->costRadio, &QRadioButton::toggled,
            this, &MainWindow::on_optimizationTypeChanged);
    connect(ui->timeRadio, &QRadioButton::toggled,
            this, &MainWindow::on_optimizationTypeChanged);
    connect(ui->combinedRadio, &QRadioButton::toggled,
            this, &MainWindow::on_optimizationTypeChanged);

    setupStrategies();
    ui->statusLine->setText("Введите адреса и нажмите 'Найти маршрут'");
}

MainWindow::~MainWindow() {
    delete ui;
    delete currentStrategy;
}

void MainWindow::setupStrategies() {
    currentStrategy = new CombinedOptimization();
    routeOptimizer = std::make_unique<RouteOptimizer>(currentStrategy);
}

void MainWindow::on_searchButton_clicked() {
    startValid = false;
    endValid = false;

    QString startAddress = ui->startAddressLine->text();
    QString endAddress = ui->endAddressLine->text();

    if (startAddress.isEmpty() || endAddress.isEmpty()) {
        ErrorHandler::handle(ErrorHandler::ADDRESS_ERROR, "Адреса не могут быть пустыми");
        ui->statusLine->setText("Ошибка: адреса не могут быть пустыми");
        return;
    }

    startValidator->validateAddress(startAddress.toStdString());
    endValidator->validateAddress(endAddress.toStdString());
    ui->statusLine->setText("Проверка адресов...");
}

void MainWindow::on_startAddressValidated(bool valid) {
    startValid = valid;
    if (!valid) {
        ErrorHandler::handle(ErrorHandler::ADDRESS_ERROR,
                             "Некорректный адрес отправления");
        ui->statusLine->setText("Ошибка: некорректный адрес отправления");
        return;
    }

    std::string corrected = startValidator->correctAddress();
    ui->startAddressLine->setText(QString::fromStdString(corrected));
    validateAddresses();
}

void MainWindow::on_endAddressValidated(bool valid) {
    endValid = valid;
    if (!valid) {
        ErrorHandler::handle(ErrorHandler::ADDRESS_ERROR,
                             "Некорректный адрес назначения");
        ui->statusLine->setText("Ошибка: некорректный адрес назначения");
        return;
    }

    std::string corrected = endValidator->correctAddress();
    ui->endAddressLine->setText(QString::fromStdString(corrected));
    validateAddresses();
}

void MainWindow::validateAddresses() {
    if (startValid && endValid) {
        QString start = ui->startAddressLine->text();
        QString end = ui->endAddressLine->text();

        start = start.simplified().replace("\"", "");
        end = end.simplified().replace("\"", "");

        ui->statusLine->setText("Поиск маршрутов...");
        routeSearcher->searchRoutes(start.toStdString(), end.toStdString());
    }
}

void MainWindow::on_routesFound(const std::vector<Route>& routes) {
    if (routes.empty()) {
        ui->statusLine->setText("Маршруты не найдены");
        ErrorHandler::handle(ErrorHandler::ROUTE_NOT_FOUND);
        return;
    }

    delete currentStrategy;
    if (ui->costRadio->isChecked()) {
        currentStrategy = new CostOptimization();
    } else if (ui->timeRadio->isChecked()) {
        currentStrategy = new TimeOptimization();
    } else {
        currentStrategy = new CombinedOptimization();
    }

    routeOptimizer->setStrategy(currentStrategy);
    auto optimizedRoutes = routeOptimizer->optimize(routes);
    displayRoutes(optimizedRoutes);
    ui->statusLine->setText("Найдено маршрутов: " + QString::number(routes.size()));
}

void MainWindow::on_searchError(const QString& message) {
    ui->statusLine->setText("Ошибка: " + message);
    ErrorHandler::handle(ErrorHandler::API_ERROR, message);
}

void MainWindow::on_optimizationTypeChanged(bool checked) {
    if (checked) {
        std::string start = ui->startAddressLine->text().toStdString();
        std::string end = ui->endAddressLine->text().toStdString();
        routeSearcher->searchRoutes(start, end);
    }
}

void MainWindow::displayRoutes(const std::vector<Route>& routes) {
    QString textReport = ReportGenerator::generateTextReport(routes);
    ui->textBrowser->setText(textReport);
}
