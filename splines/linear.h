#ifndef __H_VANYKA_LINEAR_SPLINE
#define __H_VANYKA_LINEAR_SPLINE

#include "spline.h"

#define mSupportPoints this->mSupportPoints

namespace vanyka::spline
{

template <class V>
class LinearSpline : public Spline<V>
{
	V Lerp(const float &t, const V &p1, const V &p2) const { return p1 + (p2 - p1) * t; }
public:
	std::vector<V> GeneratePoints(int res = 10) const override;
	V operator()(const float& t) const override;
};

template <class V>
V LinearSpline<V>::operator()(const float& t) const {
	if(mSupportPoints.size() < 2) 
		throw "Not enough points";

	float localt; size_t index;
	std::tie(localt, index) = this->CalculateSegmentInfo(t, mSupportPoints.size() - 1);
	
	return Lerp(localt, mSupportPoints[index], mSupportPoints[index + 1]);
}

template <class V>
std::vector<V> LinearSpline<V>::GeneratePoints(int res) const
{
	std::vector<V> points;

	// Filtering the empty and one point case
	switch (mSupportPoints.size())
	{
	case 0:
		return points;
	case 1:
		return mSupportPoints;
	}

	// Calculation
	points.reserve(res * mSupportPoints.size());
	for (int i = 1; i < mSupportPoints.size(); ++i)
	{
		const V &prev = mSupportPoints[i - 1];
		const V &curr = mSupportPoints[i];
		points.push_back(prev);
		for (int j = 1; j < res; ++j)
		{
			const float t = (float)j / (float)res;
			points.push_back(this->Lerp(t, prev, curr));
		}
	}
	points.push_back(mSupportPoints.back());
	return points;
}

} // vanyka::spline

#undef mSupportPoints

#endif