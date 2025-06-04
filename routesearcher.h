#ifndef ROUTESEARCHER_H
#define ROUTESEARCHER_H

#include <vector>
#include <string>
#include <memory>
#include "route.h"
#include "workwithapi.h"
#include "database.h"

class RouteSearcher : public QObject {
    Q_OBJECT
public:
    RouteSearcher(std::shared_ptr<WorkWithAPI> api,
                  std::shared_ptr<Database> database,
                  QObject* parent = nullptr);

    void searchRoutes(const std::string& from, const std::string& to);

signals:
    void routesFound(const std::vector<Route>& routes);
    void searchError(const QString& message);

private:
    std::shared_ptr<WorkWithAPI> apiClient;
    std::shared_ptr<Database> db;

    void fetchFromAPI(const std::string& from, const std::string& to);
    void fetchFromDatabase(const std::string& from, const std::string& to);
};

#endif // ROUTESEARCHER_H
