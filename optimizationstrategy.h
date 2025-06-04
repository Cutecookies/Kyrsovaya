#ifndef OPTIMIZATIONSTRATEGY_H
#define OPTIMIZATIONSTRATEGY_H

#include <vector>
#include "route.h"

class OptimizationStrategy {
public:
    virtual ~OptimizationStrategy() = default;
    virtual std::vector<Route> optimize(const std::vector<Route>& routes) = 0;
};

#endif // OPTIMIZATIONSTRATEGY_H
