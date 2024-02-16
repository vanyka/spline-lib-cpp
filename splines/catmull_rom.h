#ifndef __H_VANYKA_CATMULL_ROM
#define __H_VANYKA_CATMULL_ROM

#include "curve.h"

namespace vanyka {

template <typename V>
class CatmullRom : public Curve<V>
{
public:
	CatmullRom() : Curve<V>() {}

protected:
	V interpolate(float u, const V &P0, const V &P1, const V &P2, const V &P3);
};

// Definitions

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
#endif