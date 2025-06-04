#ifndef ADDRESSVALIDATOR_H
#define ADDRESSVALIDATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <string>

class AddressValidator : public QObject {
    Q_OBJECT
public:
    AddressValidator(QObject *parent = nullptr);
    ~AddressValidator();

    void validateAddress(const std::string& address);
    std::string correctAddress() const;
    bool isAddressValid() const;

    struct Coordinate {
        double latitude;
        double longitude;
        Coordinate(double lat = 0.0, double lon = 0.0) : latitude(lat), longitude(lon) {}
    };

    Coordinate getCoordinate() const;


signals:
    void validationCompleted(bool isValid);

private slots:
    void handleGeocodeReply(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    std::string rawAddress;
    std::string correctedAddress;
    bool isValid;
    const QString apiKey = "5ee91c1d-f9f0-42cc-9ac3-b4e6f826c434";

    Coordinate lastCoordinate;
};

#endif // ADDRESSVALIDATOR_H
