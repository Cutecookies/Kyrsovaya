#ifndef COMBINEDOPTIMIZATION_H
#define COMBINEDOPTIMIZATION_H

#include "optimizationstrategy.h"

class CombinedOptimization : public OptimizationStrategy {
public:
    std::vector<Route> optimize(const std::vector<Route>& routes) override;
};


#endif // COMBINEDOPTIMIZATION_H
