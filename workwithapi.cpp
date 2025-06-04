#include "workwithapi.h"
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QSslConfiguration>


WorkWithAPI::WorkWithAPI(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setProtocol(QSsl::TlsV1_2OrLater);
    QSslConfiguration::setDefaultConfiguration(sslConfig);

    connect(networkManager, &QNetworkAccessManager::finished,
            this, &WorkWithAPI::handleNetworkReply);
}

void WorkWithAPI::getRoutes(const std::string& from, const std::string& to) {
    QString url = "https://api.routing.yandex.net/v2/route";

    QUrlQuery query;
    query.addQueryItem("apikey", "29a8282b-6571-452e-bacc-f44b05d56e0c");
    QString waypoints = QUrl::toPercentEncoding(QString::fromStdString(from))
                        + "|"
                        + QUrl::toPercentEncoding(QString::fromStdString(to));
    query.addQueryItem("waypoints", waypoints);
    query.addQueryItem("mode", "transit");

    QUrl fullUrl(url);
    fullUrl.setQuery(query);

    QNetworkRequest request;
    request.setUrl(fullUrl);
    request.setRawHeader("Accept", "application/json");

    qDebug() << "Sending request to:" << fullUrl.toString(QUrl::FullyEncoded);
    networkManager->get(request);
}

void WorkWithAPI::handleNetworkReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        QString error = "Network error: " + reply->errorString();
        qWarning() << error;
        emit errorOccurred(error);
        reply->deleteLater();
        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode == 502) {
        emit errorOccurred("API service temporarily unavailable (502 Bad Gateway)");
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    if (jsonDoc.isNull()) {
        QString error = "Invalid JSON response";
        qWarning() << error;
        emit errorOccurred(error);
        reply->deleteLater();
        return;
    }

    parseResponse(jsonDoc);
    reply->deleteLater();
}

void WorkWithAPI::parseResponse(const QJsonDocument& json) {
    std::vector<Route> routes;
    QJsonObject root = json.object();

    qDebug() << "Routing response:" << json.toJson(QJsonDocument::Indented);

    if (root.contains("routes") && root["routes"].isArray()) {
        QJsonArray routesArray = root["routes"].toArray();

        for (const QJsonValue& routeValue : routesArray) {
            QJsonObject routeObj = routeValue.toObject();
            if (routeObj.contains("legs") && routeObj["legs"].isArray()) {
                QJsonArray legs = routeObj["legs"].toArray();

                for (const QJsonValue& legValue : legs) {
                    QJsonObject leg = legValue.toObject();
                    if (leg.contains("steps") && leg["steps"].isArray()) {
                        QJsonArray steps = leg["steps"].toArray();

                        for (const QJsonValue& stepValue : steps) {
                            QJsonObject step = stepValue.toObject();
                            if (step["type"].toString() == "transit") {
                                Route route;
                                QJsonObject transport = step["transit"].toObject();

                                QString routeNumber = transport["number"].toString();
                                route.setRouteNumber(routeNumber.toInt());

                                Stops stops;
                                if (transport.contains("stops") && transport["stops"].isArray()) {
                                    QJsonArray stopsArray = transport["stops"].toArray();
                                    for (const QJsonValue& stopValue : stopsArray) {
                                        QJsonObject stop = stopValue.toObject();
                                        if (stop.contains("name")) {
                                            stops.addStop(stop["name"].toString().toStdString());
                                        }
                                    }
                                }
                                route.setStops(stops);

                                if (step.contains("start_time") && step.contains("end_time")) {
                                    QString start = step["start_time"].toString();
                                    QString end = step["end_time"].toString();

                                    QStringList startParts = start.split(':');
                                    QStringList endParts = end.split(':');

                                    if (startParts.size() >= 2 && endParts.size() >= 2) {
                                        Time departure(startParts[0].toInt(), startParts[1].toInt());
                                        Time arrival(endParts[0].toInt(), endParts[1].toInt());

                                        route.setDepartureTime(departure);
                                        route.setArrivalTime(arrival);

                                        int duration = arrival.toMinutes() - departure.toMinutes();
                                        if (duration < 0) duration += 24 * 60;
                                        route.setDurationMinutes(duration);
                                    }
                                }

                                if (step.contains("distance")) {
                                    double distance = step["distance"].toDouble() / 1000.0;
                                    int maxCost = distance * 2.5 > 25 ? distance * 2.5 : 25;
                                    route.setCost(maxCost);
                                }

                                route.setTransferCount(0);

                                routes.push_back(route);
                            }
                        }
                    }
                }
            }
        }
    }
    if (routes.empty()) {
        emit errorOccurred("No public transport routes found");
    } else {
        emit routesReceived(routes);
    }
}
