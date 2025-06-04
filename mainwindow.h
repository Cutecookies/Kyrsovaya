#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "addressvalidator.h"
#include "workwithapi.h"
#include "database.h"
#include "routesearcher.h"
#include "routeoptimizer.h"
#include "optimizationstrategy.h"
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_startAddressValidated(bool valid);
    void on_endAddressValidated(bool valid);
    void on_routesFound(const std::vector<Route>& routes);
    void on_searchError(const QString& message);
    void on_optimizationTypeChanged(bool checked);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<AddressValidator> startValidator;
    std::unique_ptr<AddressValidator> endValidator;
    std::shared_ptr<WorkWithAPI> apiClient;
    std::shared_ptr<Database> dbManager;
    std::unique_ptr<RouteSearcher> routeSearcher;
    std::unique_ptr<RouteOptimizer> routeOptimizer;
    OptimizationStrategy* currentStrategy;
    QTextBrowser *mapView;

    bool startValid = false;
    bool endValid = false;

    void setupStrategies();
    void displayRoutes(const std::vector<Route>& routes);
    void validateAddresses();
};

#endif // MAINWINDOW_H
