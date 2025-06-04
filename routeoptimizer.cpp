#include "routeoptimizer.h"

RouteOptimizer::RouteOptimizer(OptimizationStrategy* strategy)
    : strategy(strategy) {}

void RouteOptimizer::setStrategy(OptimizationStrategy* newStrategy) {
    strategy = newStrategy;
}

std::vector<Route> RouteOptimizer::optimize(const std::vector<Route>& routes) {
    return strategy->optimize(routes);
}
