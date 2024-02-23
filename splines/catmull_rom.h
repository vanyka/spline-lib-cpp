#ifndef __H_VANYKA_CATMULL_ROM
#define __H_VANYKA_CATMULL_ROM

#include "spline.h"

namespace vanyka
{

template <class V, bool PassAllSupportPoint = true>
class CatmullRomSpline : public Spline<V>
{
	static V Interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);

public:
	std::vector<V> GeneratePoints(int res = 10) const override;
};

template <class V, bool PassAllSupportPoint>
V CatmullRomSpline<V, PassAllSupportPoint>::Interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3)
{
	V point;
	point = (-P0 + P1 * 3 - P2 * 3 + P3) * (u * u * u) / 2;
	point += (P0 * 2 - P1 * 5 + P2 * 4 - P3) * (u * u) / 2;
	point += (-P0 + P2) * u / 2;
	point += P1;

	return point;
}

template <class V, bool PassAllSupportPoint>
std::vector<V> CatmullRomSpline<V, PassAllSupportPoint>::GeneratePoints(int res) const
{
	std::vector<V> points;
	if (mSupportPoints.size() < 4)
		// Here Should be a warning that too few support points available
		return points;

	if (PassAllSupportPoint)
	{
		points.reserve((mSupportPoints.size() - 1) * res);
		points.push_back(mSupportPoints[0]);
		for (int i = 2; i <= mSupportPoints.size(); ++i)
		{
			const V &v1 = i - 3 < 0 ? mSupportPoints[0] : mSupportPoints[i - 3];
			const V &v2 = mSupportPoints[i - 2];
			const V &v3 = mSupportPoints[i - 1];
			const V &v4 = i == mSupportPoints.size() ? mSupportPoints[mSupportPoints.size() - 1] : mSupportPoints[i];
			for (int j = 1; j < res; ++j)
			{
				const float t = (float)j / (float)res;
				points.push_back(Interpolate(t, v1, v2, v3, v4));
			}
			points.push_back(v3);
		}
		return points;
	}

	points.reserve((mSupportPoints.size() - 3) * res);
	points.push_back(mSupportPoints[1]);
	for (int i = 3; i < mSupportPoints.size(); ++i)
	{
		const V &v1 = mSupportPoints[i - 3];
		const V &v2 = mSupportPoints[i - 2];
		const V &v3 = mSupportPoints[i - 1];
		const V &v4 = mSupportPoints[i];
		for (int j = 1; j < res; ++j)
		{
			const float t = (float)j / (float)res;
			points.push_back(Interpolate(t, v1, v2, v3, v4));
		}
		points.push_back(v3);
	}

	return points;
}

} // vanyka
#endif