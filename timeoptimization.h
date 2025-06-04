#ifndef TIMEOPTIMIZATION_H
#define TIMEOPTIMIZATION_H

#include "optimizationstrategy.h"

class TimeOptimization : public OptimizationStrategy {
public:
    std::vector<Route> optimize(const std::vector<Route>& routes) override;
};
#endif // TIMEOPTIMIZATION_H
