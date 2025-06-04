#ifndef ROUTE_H
#define ROUTE_H

#include "stops.h"
#include "time.h"
#include <vector>

class Route {
private:
    int routeNumber;
    Stops stops;
    Time departureTime;
    Time arrivalTime;
    double cost;
    std::vector<Time> schedule;
    int transferCount;
    Time duration;

public:
    Route();
    Route(int number, const Stops& stopsList,
          const Time& depTime, const Time& arrTime,
          double routeCost, const std::vector<Time>& sched,
          int transfers, int dur);

    void calculateDuration();

    double getCost() const;
    int getDurationMinutes() const;
    int getTransferCount() const;
    const Stops& getStops() const;
    int getRouteNumber() const;
    const Time& getDepartureTime() const;
    const Time& getArrivalTime() const;
    const std::vector<Time>& getSchedule() const;

    void setDurationMinutes(int min);
    void setRouteNumber(int number);
    void setStops(const Stops& stopsList);
    void setDepartureTime(const Time& time);
    void setArrivalTime(const Time& time);
    void setCost(double routeCost);
    void setSchedule(const std::vector<Time>& sched);
    void setTransferCount(int transfers);
};

#endif // ROUTE_H
