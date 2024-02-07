#ifndef _H__BSPLINE_H
#define _H__BSPLINE_H

#include "curve.h"

namespace vanyka{

template <typename V>
class BSpline : public Curve<V>
{
public:
	BSpline() : Curve<V>() {}

protected:
	virtual void _OnWayPointAdded();

protected:
	V interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);
};

// Definitions

template <typename V>
void BSpline<V>::_OnWayPointAdded()
{
	if (this->mWayPoints.size() < 4)
		return;

	int new_control_point_index = static_cast<int>(this->mWayPoints.size()) - 1;

	int pt = new_control_point_index - 3;

	for (int i = 0; i <= this->mSteps; i++)
	{
		float u = (float)i / (float)this->mSteps;

		this->AddNode(interpolate(u, this->mWayPoints[pt], this->mWayPoints[pt + 1], this->mWayPoints[pt + 2], this->mWayPoints[pt + 3]));
	}
}

template <typename V>
V BSpline<V>::interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3)
{
	V point;
	point =  (-P0 + P1 * 3 - P2 * 3 + P3) * (u * u * u) / 6;
	point += (P0 * 3 - P1 * 6 + P2 * 3) * (u * u) / 6;
	point += (P0 * (-3) + P2 * 3) * u / 6;
	point += (P0 + P1 * 4 + P2) / 6;

	return point;
}

} // vanyka

#endif