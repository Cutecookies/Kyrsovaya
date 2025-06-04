#include "timeoptimization.h"
#include <algorithm>

std::vector<Route> TimeOptimization::optimize(const std::vector<Route>& routes) {
    std::vector<Route> sorted = routes;
    std::sort(sorted.begin(), sorted.end(),
              [](const Route& a, const Route& b) {
                  return a.getDurationMinutes() < b.getDurationMinutes();
              });
    return sorted;
}
