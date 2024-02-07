#ifndef _H__BEZIER_H
#define _H__BEZIER_H

// FIXME: Not passing all points

namespace vanyka{

#include "curve.h"
template <typename V>
class Bezier : public Curve<V>
{
public:
	Bezier() : Curve<V>() {}

protected:
	virtual void _OnWayPointAdded();

protected:
	V interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);
};

// Definitions

template <typename V>
void Bezier<V>::_OnWayPointAdded()
{
	if (this->mWayPoints.size() < 4)
		return;

	int new_control_point_index = this->mWayPoints.size() - 1;

	if (new_control_point_index == 3)
	{
		for (int i = 0; i <= this->mSteps; i++)
		{
			float u = (float)i / (float)this->mSteps;

			this->AddNode(interpolate(u, this->mWayPoints[0], this->mWayPoints[1], this->mWayPoints[2], this->mWayPoints[3]));
		}
	}
	else
	{
		if (new_control_point_index % 2 == 0)
			return;

		int pt = new_control_point_index - 2;
		for (int i = 0; i <= this->mSteps; i++)
		{
			float u = (float)i / (float)this->mSteps;
			V point4 = this->mWayPoints[pt] * 2 - this->mWayPoints[pt - 1];

			AddNode(interpolate(u, this->mWayPoints[pt], point4, this->mWayPoints[pt + 1], this->mWayPoints[pt + 2]));
		}
	}
}

template <typename V>
V Bezier<V>::interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3)
{
	V point;
	point = (-P0 + P1 * 3 - P2 * 3 + P3) * (u * u * u);
	point += (P0 * 3 - P1 * 6 + P2 * 3) * (u * u);
	point += (P0 * (-3) + P1 * 3) * u;
	point += P0;

	return point;
}

} // vanyka

#endif