#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include "route.h"
#include <QString>

struct GeoCoordinate {
    double latitude;
    double longitude;

    GeoCoordinate(double lat = 0.0, double lon = 0.0)
        : latitude(lat), longitude(lon) {}
};


class ReportGenerator {
public:
    static QString generateTextReport(const std::vector<Route>& routes);
};
#endif // REPORTGENERATOR_H
