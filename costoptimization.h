#ifndef COSTOPTIMIZATION_H
#define COSTOPTIMIZATION_H

#include "optimizationstrategy.h"

class CostOptimization : public OptimizationStrategy {
public:
    std::vector<Route> optimize(const std::vector<Route>& routes) override;
};

#endif // COSTOPTIMIZATION_H
