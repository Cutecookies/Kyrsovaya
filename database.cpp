#include "database.h"
#include <QDebug>

Database::Database() {}

void Database::saveRoutes(const std::vector<Route>& routes,
                          const std::string& from,
                          const std::string& to) {
    AddressPair key = std::make_pair(from, to);
    routeStorage[key] = routes;

    qDebug() << "Saved" << routes.size() << "routes for"
             << QString::fromStdString(from) << "->"
             << QString::fromStdString(to);
}

std::vector<Route> Database::getRoutes(const std::string& from,
                                       const std::string& to) const {
    AddressPair key = std::make_pair(from, to);

    auto it = routeStorage.find(key);
    if (it != routeStorage.end()) {
        return it->second;
    }

    return {};
}

bool Database::hasRoutes(const std::string& from,
                         const std::string& to) const {
    AddressPair key = std::make_pair(from, to);

    return routeStorage.find(key) != routeStorage.end();
}

void Database::clear() {
    routeStorage.clear();
    qDebug() << "Database cleared";
}
