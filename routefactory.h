#ifndef ROUTEFACTORY_H
#define ROUTEFACTORY_H

#include "route.h"
#include <QJsonObject>

class RouteFactory {
public:
    virtual ~RouteFactory() = default;
    virtual Route createRoute(const QJsonObject& data) = 0;
};

#endif // ROUTEFACTORY_H
