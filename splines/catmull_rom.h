#pragma once
#include "curve.h"

namespace vanyka {

template <typename V>
class CatmullRom : public Curve<V>
{
public:
	CatmullRom() : Curve<V>() {}

	virtual void _OnWayPointAdded();

protected:
	V interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);
};

// Definitions

template <typename V>
void CatmullRom<V>::_OnWayPointAdded()
{
	if (this->mWayPoints.size() < 4)
		return;

	size_t new_control_point_index = this->mWayPoints.size() - 1;
	size_t pt = new_control_point_index - 2;
	for (int i = 0; i <= this->mSteps; i++)
	{
		float u = (float)i / (float)this->mSteps;

		this->AddNode(interpolate(u, this->mWayPoints[pt - 1], this->mWayPoints[pt], this->mWayPoints[pt + 1], this->mWayPoints[pt + 2]));
	}
}

template <typename V>
V CatmullRom<V>::interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3)
{
	V point;
	point = (-P0 + P1 * 3 - P2 * 3 + P3) * (u * u * u) / 2;
	point += (P0 * 2 - P1 * 5 + P2 * 4 - P3) * (u * u) / 2;
	point += (-P0 + P2) * u / 2;
	point += P1;

	return point;
}

} // vanyka