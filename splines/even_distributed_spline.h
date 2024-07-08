#ifndef __H_VANYKA_EVEN_DISTRIBUTED_SPLINE
#define __H_VANYKA_EVEN_DISTRIBUTED_SPLINE

#include <vector>
#include "spline.h"

namespace vanyka::spline
{

template <class V>
class EvenDistributedSpline {
	std::vector<V>		mPoints;
	std::vector<float>	mSegmentLengths;
	float				mSplineLength;
	void Init(const Spline<V>& spline, float demandedLength, int resolution);
	V Lerp(const V& v1, const V& v2, const float& t) const { return v1 + (v2 - v1) * t; }
public:
	EvenDistributedSpline(const Spline<V>& spline, const float& demandedLength = 0.f, const int& resolution = 10)
		{ Init(spline, demandedLength, resolution); }
	EvenDistributedSpline(const Spline<V>& spline, const int& resolution)
		{ Init(spline, 0.f, resolution); }
	V operator()(const float& distance) const;
	std::vector<V> GeneratePoints(int res = 100) const;
	float GetSplineLength() const { return mSplineLength; }
};

template <class V>
void EvenDistributedSpline<V>::Init(
	const Spline<V>& spline, float demandedLength, int res
) {
	mPoints = spline.GeneratePoints(res);

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
V EvenDistributedSpline<V>::operator()(const float& distance) const {
	if (distance < 0.f || distance > mSplineLength)
		throw std::runtime_error("The given distance is invalid!");

	if (distance == 0.f)
		return mPoints.front();
	if (distance == mSplineLength)
		return mPoints.back();

	float d = distance;
	for (int i = 0; i < mSegmentLengths.size(); ++i) {
		if (mSegmentLengths[i] < d) {
			d -= mSegmentLengths[i];
			continue;
		}
		const float t = d / mSegmentLengths[i];
		return Lerp(mPoints[i], mPoints[i + 1], t);
	}
	throw std::runtime_error("The given distance is greater, than the length of spline!");
	return V();
}

template <class V>
std::vector<V> EvenDistributedSpline<V>::GeneratePoints(int res) const {
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

} // vanyka::spline
#endif
