#ifndef __H_VANYKA_CATMULL_ROM
#define __H_VANYKA_CATMULL_ROM

#include "curve.h"

namespace vanyka {

template <typename V>
class CatmullRom : public Curve<V>
{
	bool mGenerateEndControlPoints;
	V Interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);

public:
	CatmullRom(bool genPoints = false) : Curve<V>(), mGenerateEndControlPoints(genPoints) {}
	std::vector<V> GeneratePoints(int res = 10) override;
};

// Definitions

template <typename V>
V CatmullRom<V>::Interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3)
{
	V point;
	point = (-P0 + P1 * 3 - P2 * 3 + P3) * (u * u * u) / 2;
	point += (P0 * 2 - P1 * 5 + P2 * 4 - P3) * (u * u) / 2;
	point += (-P0 + P2) * u / 2;
	point += P1;

	return point;
}

template <typename V>
std::vector<V> CatmullRom<V>::GeneratePoints(int res) {
	std::vector<V> points;
	if (mSupportPoints.size() < 4) 
		// Here Should be a warning that too few support points available
		return points;

	// points.reserve((points.size() - 3) * res);
	points.push_back(mSupportPoints[1]);
	for (int i = 3; i < mSupportPoints.size(); ++i) {
		for (int j = 1; j < res; ++j) {
			const float t = (float)j / (float)res;
			points.push_back(Interpolate(t, mSupportPoints[i - 3], mSupportPoints[i - 2], mSupportPoints[i - 1], mSupportPoints[i]));
		}
		points.push_back(mSupportPoints[i - 1]);
	}

	return points;
}

} // vanyka
#endif