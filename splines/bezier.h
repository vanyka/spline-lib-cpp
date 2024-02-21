#ifndef __H_VANYKA_BEZIER
#define __H_VANYKA_BEZIER

#include "spline.h"

#include <stdexcept>

namespace vanyka {

template <class V>
class BezierSpline : public Spline<V>{
public:
    std::vector<V> GeneratePoints(int res = 10) const override;
};

template <class V>
std::vector<V> BezierSpline<V>::GeneratePoints(int res) const {
    throw std::logic_error("Not Implemented!");
}

} // vanyka
#endif