#ifndef ROUTEOPTIMIZER_H
#define ROUTEOPTIMIZER_H

#include "optimizationstrategy.h"
#include <vector>
#include "route.h"

class RouteOptimizer {
public:
    RouteOptimizer(OptimizationStrategy* strategy);
    void setStrategy(OptimizationStrategy* newStrategy);
    std::vector<Route> optimize(const std::vector<Route>& routes);

private:
    OptimizationStrategy* strategy;
};

#endif // ROUTEOPTIMIZER_H
