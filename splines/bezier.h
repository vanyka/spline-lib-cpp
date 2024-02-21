#ifndef __H_VANYKA_BEZIER
#define __H_VANYKA_BEZIER

#include "spline.h"

namespace vanyka
{
    template <class V>
    class BezierSpline : public Spline<V>
    {
        static inline V Lerp(const float& t, const V& v1, const V& v2) {
            return v1 * (1.f - t) + v2 * t;
        }
        static V Interpolate(const float &t, const V &P0, const V &P1, const V &P2, const V &P3);
    public:
        std::vector<V> GeneratePoints(int res = 10) const override;
    };

    template <class V>
    V BezierSpline<V>::Interpolate(const float &t, const V &p1, const V &p2, const V &p3, const V &p4)
    {
        // TODO: Calculate the below's equation
        const V c1 = Lerp(t, p1, p2);
        const V c2 = Lerp(t, p2, p3);
        const V c3 = Lerp(t, p3, p4);
        const V c4 = Lerp(t, c1, c2);
        const V c5 = Lerp(t, c2, c3);
        return Lerp(t, c4, c5);
    }

    template <class V>
    std::vector<V> BezierSpline<V>::GeneratePoints(int res) const
    {
		std::vector<V> points;
		if (mSupportPoints.size() < 4)
			// Here Should be a warning that too few support points available
			return points;

		points.reserve((mSupportPoints.size() - 1) / 3 * res);
		for (int i = 3; i < mSupportPoints.size(); i += 3) {
			const V& v1 = mSupportPoints[i - 3];
			const V& v2 = mSupportPoints[i - 2];
			const V& v3 = mSupportPoints[i - 1];
			const V& v4 = mSupportPoints[i];
			for (int j = 0; j <= res; ++j) {
				const float t = (float)j / (float)res;
				points.push_back(Interpolate(t, v1, v2, v3, v4));
			}
		}
		return points;
    }

} // vanyka
#endif