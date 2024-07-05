#ifndef __H_VANYKA_SPLINE_EVEN_ADAPTER
#define __H_VANYKA_SPLINE_EVEN_ADAPTER

#include <vector>
#include "spline.h"

namespace vanyka
{

template <class V>
class Spline;

template <class V>
class EvenDistributedSplineAdapter {
	std::vector<V>		mPoints;
	std::vector<float>	mSegmentLengths;
	float				mSplineLength;
	V Lerp(const V& v1, const V& v2, const float& t) const { return v1 + (v2 - v1) * t; }
public:
	EvenDistributedSplineAdapter(const Spline<V>& spline, const int& processResolution, const float& demandedLength = 0.f);
	V operator()(float distance) const;
	std::vector<V> GeneratePoints(int res = 100) const;
	float GetSplineLength() const { return mSplineLength; }
};

template <class V>
EvenDistributedSplineAdapter<V>::EvenDistributedSplineAdapter(
	const Spline<V>& spline, const int& procRes, const float& demandedLength
) {
	mPoints = spline.GeneratePoints(procRes);

	mSplineLength = 0.f;
	mSegmentLengths = std::vector<float>(mPoints.size() - 1);
	for (int right = 1; right < mPoints.size(); ++right) {
		int left = right - 1;

		mSegmentLengths[left] = (mPoints[right] - mPoints[left]).Length();
		mSplineLength += mSegmentLengths[left];

		if (demandedLength > 0.f && mSplineLength >= demandedLength) {
			if (right != mPoints.size()) {
				mSegmentLengths.resize(right);
				mPoints.resize(right + 1);
			}
			break;
		}
	}
}

template <class V>
V EvenDistributedSplineAdapter<V>::operator()(float distance) const {
	if(distance >= 0.f || distance <= mSplineLength)
		throw std::runtime_error("The given distance is invalid!");

	if (distance == 0.f)
		return mPoints.front();
	if (distance == mSplineLength)
		return mPoints.back();

	for (int i = 0; i < mSegmentLengths.size(); ++i) {
		if (mSegmentLengths[i] < distance) {
			distance -= mSegmentLengths[i];
			continue;
		}
		const float t = distance / mSegmentLengths[i];
		return Lerp(mPoints[i], mPoints[i + 1], t);
	}
	throw std::runtime_error("The given distance is greater, than the length of spline!");
	return V();
}

template <class V>
std::vector<V> EvenDistributedSplineAdapter<V>::GeneratePoints(int res) const {
	if(res < 2)
		throw std::runtime_error("The even spline resolution must be at least 2!");

	std::vector<V> evenPoints;
	evenPoints.push_back(mPoints.front());

	const float stepSize = mSplineLength / float(res - 1);
	float d = stepSize;
	int i = 0;
	while (i < mSegmentLengths.size()) {
		if(d >= mSegmentLengths[i]) {
			d -= mSegmentLengths[i];
			++i;
			continue;
		}
		const float t = d / mSegmentLengths[i];
		evenPoints.push_back(Lerp(mPoints[i], mPoints[i + 1], t));
		d += stepSize;
	}
	evenPoints.push_back(mPoints.back());
	return evenPoints;
}

} // vanyka
#endif
