#include "route.h"

Route::Route()
    : routeNumber(0),
    cost(0.0),
    transferCount(0)
{}

Route::Route(int number, const Stops& stopsList,
             const Time& depTime, const Time& arrTime,
             double routeCost, const std::vector<Time>& sched,
             int transfers, int dur)
    : routeNumber(number),
    stops(stopsList),
    departureTime(depTime),
    arrivalTime(arrTime),
    cost(routeCost),
    schedule(sched),
    transferCount(transfers),
    duration(dur)
{}

void Route::calculateDuration() {
    int depMinutes = departureTime.toMinutes();
    int arrMinutes = arrivalTime.toMinutes();
    int durationMinutes = arrMinutes - depMinutes;

    if (durationMinutes < 0) {
        durationMinutes += 24 * 60;
    }

    duration.addMinutes(durationMinutes);
}

int Route::getDurationMinutes() const {
    return duration.getMinutes();
}

double Route::getCost() const {
    return cost;
}

int Route::getTransferCount() const {
    return transferCount;
}

const Stops& Route::getStops() const {
    return stops;
}

int Route::getRouteNumber() const {
    return routeNumber;
}

const Time& Route::getDepartureTime() const {
    return departureTime;
}

const Time& Route::getArrivalTime() const {
    return arrivalTime;
}

const std::vector<Time>& Route::getSchedule() const {
    return schedule;
}

void Route::setDurationMinutes(int min) {
    duration.clearTime();
    duration.addMinutes(min);
}

void Route::setRouteNumber(int number) {
    routeNumber = number;
}

void Route::setStops(const Stops& stopsList) {
    stops = stopsList;
}

void Route::setDepartureTime(const Time& time) {
    departureTime = time;
}

void Route::setArrivalTime(const Time& time) {
    arrivalTime = time;
}

void Route::setCost(double routeCost) {
    cost = routeCost;
}

void Route::setSchedule(const std::vector<Time>& sched) {
    schedule = sched;
}

void Route::setTransferCount(int transfers) {
    transferCount = transfers;
}
