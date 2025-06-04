#include "combinedoptimization.h"
#include <algorithm>
#include <limits>

std::vector<Route> CombinedOptimization::optimize(const std::vector<Route>& routes) {
    if (routes.empty()) return routes;

    int maxTime = std::numeric_limits<int>::min();
    double maxCost = std::numeric_limits<double>::min();

    for (const auto& route : routes) {
        if (route.getDurationMinutes() > maxTime) maxTime = route.getDurationMinutes();
        if (route.getCost() > maxCost) maxCost = route.getCost();
    }

    if (maxTime <= 0) maxTime = 1;
    if (maxCost <= 0.0) maxCost = 1.0;

    std::vector<Route> sorted = routes;
    std::sort(sorted.begin(), sorted.end(),
              [maxTime, maxCost](const Route& a, const Route& b) {
                  double scoreA = 0.6 * (a.getDurationMinutes() / static_cast<double>(maxTime)) +
                                  0.4 * (a.getCost() / maxCost);
                  double scoreB = 0.6 * (b.getDurationMinutes() / static_cast<double>(maxTime)) +
                                  0.4 * (b.getCost() / maxCost);
                  return scoreA < scoreB;
              });

    return sorted;
}
