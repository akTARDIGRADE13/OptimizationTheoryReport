#include "SA_base.hpp"

#include <cmath>

double SABase::acceptanceProb(Cost currentCost, Cost newCost, double temp) {
    if (newCost < currentCost) {
        return 1.0;
    }
    return exp((currentCost - newCost) / temp);
}

double SABase::updateTemp(double startTemp, double endTemp, double elapsed,
                          double duration) {
    return startTemp + (endTemp - startTemp) * elapsed / duration;
}