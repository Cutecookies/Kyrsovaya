#include "busroutefactory.h"
#include "time.h"
#include <QJsonArray>
#include <QDateTime>

Route BusRouteFactory::createRoute(const QJsonObject& data) {
    Route route;

    if (data.contains("number")) {
        route.setRouteNumber(data["number"].toString().toInt());
    }

    if (data.contains("stops") && data["stops"].isArray()) {
        Stops stops;
        QJsonArray stopsArray = data["stops"].toArray();
        for (const auto& stopValue : stopsArray) {
            stops.addStop(stopValue.toString().toStdString());
        }
        route.setStops(stops);
    }

    if (data.contains("start_time") && data.contains("end_time")) {
        QStringList startParts = data["start_time"].toString().split(":");
        QStringList endParts = data["end_time"].toString().split(":");

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

    if (data.contains("distance")) {
        double distance = data["distance"].toDouble() / 1000.0;
        int maxCost = distance * 2.5 > 25 ? distance * 2.5 : 25;
        route.setCost(maxCost);
    }

    return route;
}
