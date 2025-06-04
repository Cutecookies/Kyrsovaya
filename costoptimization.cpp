#include "costoptimization.h"
#include <algorithm>

std::vector<Route> CostOptimization::optimize(const std::vector<Route>& routes) {
    std::vector<Route> sorted = routes;
    std::sort(sorted.begin(), sorted.end(),
              [](const Route& a, const Route& b) {
                  return a.getCost() < b.getCost();
              });
    return sorted;
}
