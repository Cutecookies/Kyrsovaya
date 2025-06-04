#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <map>
#include <string>
#include <utility>
#include "route.h"

class Database {
public:
    Database();

    void saveRoutes(const std::vector<Route>& routes,
                    const std::string& from,
                    const std::string& to);

    std::vector<Route> getRoutes(const std::string& from,
                                 const std::string& to) const;

    bool hasRoutes(const std::string& from,
                   const std::string& to) const;

    void clear();

private:
    using AddressPair = std::pair<std::string, std::string>;

    std::map<AddressPair, std::vector<Route>> routeStorage;
};

#endif // DATABASE_H
