#include "addressvalidator.h"
#include <QUrlQuery>
#include <QEventLoop>
#include <QDebug>

AddressValidator::AddressValidator(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)), isValid(false)  {
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &AddressValidator::handleGeocodeReply);
}

AddressValidator::~AddressValidator() {
    delete networkManager;
}

void AddressValidator::validateAddress(const std::string& address) {
    rawAddress = address;
    correctedAddress = "";
    isValid = false;

    QString fullAddress = QString::fromStdString(address);
    // if (!fullAddress.contains("белгород", Qt::CaseInsensitive) &&
    //     !fullAddress.contains("belgorod", Qt::CaseInsensitive)) {
    //     fullAddress = "Белгород, " + fullAddress;
    // }

    QString url = "https://geocode-maps.yandex.ru/1.x/";
    QUrlQuery query;
    query.addQueryItem("apikey", "5ee91c1d-f9f0-42cc-9ac3-b4e6f826c434");
    query.addQueryItem("geocode", fullAddress);
    query.addQueryItem("format", "json");
    query.addQueryItem("results", "1");
    query.addQueryItem("region", "31");

    QUrl fullUrl(url);
    fullUrl.setQuery(query);

    QNetworkRequest request;
    request.setUrl(fullUrl);
    request.setRawHeader("Accept", "application/json");

    networkManager->get(request);
}

void AddressValidator::handleGeocodeReply(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        qDebug() << "Geocode response:" << jsonDoc.toJson(QJsonDocument::Indented);

        if (jsonObj.contains("response")) {
            QJsonObject response = jsonObj["response"].toObject();

            if (response.contains("GeoObjectCollection")) {
                QJsonObject collection = response["GeoObjectCollection"].toObject();
                QJsonArray features = collection["featureMember"].toArray();

                if (!features.isEmpty()) {
                    QJsonObject feature = features[0].toObject();
                    QJsonObject geoObject = feature["GeoObject"].toObject();
                    QJsonObject metaData = geoObject["metaDataProperty"].toObject()
                                               ["GeocoderMetaData"].toObject();
                    correctedAddress = metaData["text"].toString().toStdString();

                    QJsonObject point = geoObject["Point"].toObject();
                    QStringList coords = point["pos"].toString().split(" ");
                    if (coords.size() == 2) {
                        double lon = coords[0].toDouble();
                        double lat = coords[1].toDouble();
                        lastCoordinate = Coordinate(lat, lon);
                    }

                    isValid = true;
                    qDebug() << "Valid address:" << QString::fromStdString(correctedAddress);
                } else {
                    qDebug() << "No results found for address:" << QString::fromStdString(rawAddress);
                }
            }
        }
    } else {
        qWarning() << "Geocode API error:" << reply->errorString();
    }

    reply->deleteLater();
    emit validationCompleted(isValid);
}

std::string AddressValidator::correctAddress() const {
    return correctedAddress;
}

bool AddressValidator::isAddressValid() const {
    return isValid;
}

AddressValidator::Coordinate AddressValidator::getCoordinate() const {
    return lastCoordinate;
}
