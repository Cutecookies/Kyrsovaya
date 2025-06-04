#include "reportgenerator.h"
#include <sstream>
#include <iomanip>
#include <QUrlQuery>
#include <QUrl>
#include <QDebug>

QString ReportGenerator::generateTextReport(const std::vector<Route>& routes) {
    if (routes.empty()) {
        return "No routes found";
    }

    std::stringstream report;
    report << "Found " << routes.size() << " routes:\n\n";

    for (size_t i = 0; i < routes.size(); ++i) {
        const Route& route = routes[i];
        report << "Route #" << i + 1 << ":\n";
        report << "  Number: " << route.getRouteNumber() << "\n";
        report << "  Duration: " << route.getDurationMinutes() << " minutes\n";
        report << "  Cost: " << std::fixed << std::setprecision(2)
               << route.getCost() << " RUB\n";
        report << "  Transfers: " << route.getTransferCount() << "\n";
        report << "  Departure: " << route.getDepartureTime().toString() << "\n";
        report << "  Arrival: " << route.getArrivalTime().toString() << "\n";

        report << "  Stops: ";
        const Stops& stops = route.getStops();
        for (size_t j = 0; j < stops.getSize(); ++j) {
            report << stops[j];
            if (j < stops.getSize() - 1) report << " → ";
        }
        report << "\n\n";
    }

    return QString::fromStdString(report.str());
}
