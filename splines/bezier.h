#ifndef __H_VANYKA_BEZIER
#define __H_VANYKA_BEZIER

#include "spline.h"

namespace vanyka
{
    template <class V>
    class BezierSpline : public Spline<V>
    {
        static V Interpolate(const float &t, const V &P0, const V &P1, const V &P2, const V &P3);

    public:
        std::vector<V> GeneratePoints(int res = 10) const override;
    };

    template <class V>
    V BezierSpline<V>::Interpolate(const float &t, const V &p1, const V &p2, const V &p3, const V &p4)
    {
        const float nt = 1.f - t;
        return p1 * (nt * nt * nt) + p2 * (3 * nt * nt * t) + p3 * (3 * nt * t * t) + p4 * (t * t * t);
    }

    template <class V>
    std::vector<V> BezierSpline<V>::GeneratePoints(int res) const
    {
        std::vector<V> points;
        if (mSupportPoints.size() < 4)
            // Here Should be a warning that too few support points available
            return points;

        points.reserve((mSupportPoints.size() - 1) / 3 * res);
        for (int i = 3; i < mSupportPoints.size(); i += 3)
        {
            const V &v1 = mSupportPoints[i - 3];
            const V &v2 = mSupportPoints[i - 2];
            const V &v3 = mSupportPoints[i - 1];
            const V &v4 = mSupportPoints[i];
            for (int j = 0; j <= res; ++j)
            {
                const float t = (float)j / (float)res;
                points.push_back(Interpolate(t, v1, v2, v3, v4));
            }
        }
        return points;
    }

} // vanyka
#endif