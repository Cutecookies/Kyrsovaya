#ifndef BUSROUTEFACTORY_H
#define BUSROUTEFACTORY_H

#include "routefactory.h"

class BusRouteFactory : public RouteFactory {
public:
    Route createRoute(const QJsonObject& data) override;
};

#endif // BUSROUTEFACTORY_H
