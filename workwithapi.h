#ifndef WORKWITHAPI_H
#define WORKWITHAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "route.h"

class WorkWithAPI : public QObject {
    Q_OBJECT
public:
    WorkWithAPI(QObject *parent = nullptr);
    void getRoutes(const std::string& from, const std::string& to);

signals:
    void routesReceived(const std::vector<Route>& routes);
    void errorOccurred(const QString& message);

private slots:
    void handleNetworkReply(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    const QString apiKey = "29a8282b-6571-452e-bacc-f44b05d56e0c";

    void parseResponse(const QJsonDocument& json);
};

#endif // WORKWITHAPI_H
