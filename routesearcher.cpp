#include "routesearcher.h"
#include <QDebug>

RouteSearcher::RouteSearcher(std::shared_ptr<WorkWithAPI> api,
                             std::shared_ptr<Database> database,
                             QObject* parent)
    : QObject(parent), apiClient(api), db(database)
{
    connect(apiClient.get(), &WorkWithAPI::routesReceived,
            this, &RouteSearcher::routesFound);
    connect(apiClient.get(), &WorkWithAPI::errorOccurred,
            this, &RouteSearcher::searchError);
}

void RouteSearcher::searchRoutes(const std::string& from, const std::string& to) {
    auto dbRoutes = db->getRoutes(from, to);
    if (!dbRoutes.empty()) {
        emit routesFound(dbRoutes);
        return;
    }

    fetchFromAPI(from, to);
}

void RouteSearcher::fetchFromAPI(const std::string& from, const std::string& to) {
    apiClient->getRoutes(from, to);
}

void RouteSearcher::fetchFromDatabase(const std::string& from, const std::string& to) {
    auto routes = db->getRoutes(from, to);
    if (!routes.empty()) {
        emit routesFound(routes);
    } else {
        emit searchError("No routes found in database");
    }
}
