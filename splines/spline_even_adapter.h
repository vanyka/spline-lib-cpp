#ifndef __H_VANYKA_SPLINE_EVEN_ADAPTER
#define __H_VANYKA_SPLINE_EVEN_ADAPTER

#include <vector>
#include <optional>
#include "spline.h"

namespace vanyka
{

template <class V>
class EvenlySpacedSplineAdapter {
	std::vector<V>		mPoints;
	std::vector<float>	mSegmentLengths;
	float				mSplineLength;
	void Init(const Spline<V>& spline, float demanded_length, int resolution);
	V GetPoint(float distance) const;
	V Lerp(const V& v1, const V& v2, const float& t) const { return v1 + (v2 - v1) * t; }
public:
	EvenlySpacedSplineAdapter(const Spline<V>& spline, const float& demanded_length = 0.f, const int& resolution = 30)
		{ Init(spline, demanded_length, resolution); }
	EvenlySpacedSplineAdapter(const Spline<V>& spline, const int& resolution) 
		{ Init(spline, 0.f, resolution); }
	V operator()(const float& distance) const { return GetPoint(distance); }
	std::vector<V> GeneratePoints(int res = 30) const;
	float GetSplineLength() const { return mSplineLength; }
};

template <class V>
void EvenlySpacedSplineAdapter<V>::Init(
	const Spline<V>& spline, float demanded_length, int res
) {
	mPoints = spline.GeneratePoints(res);

	mSplineLength = 0.f;
	mSegmentLengths = std::vector<float>(mPoints.size() - 1);
	for (int right = 1; right < mPoints.size(); ++right) {
		int left = right - 1;

		V diff = mPoints[right] - mPoints[left];
		mSegmentLengths[left] = diff.Length();
		mSplineLength += mSegmentLengths[left];

		if (demanded_length > 0.f && mSplineLength >= demanded_length) {
			if (right != mPoints.size()) {
				mSegmentLengths.resize(right);
				mPoints.resize(right + 1);
			}
			break;
		}
	}
}

template <class V>
V EvenlySpacedSplineAdapter<V>::GetPoint(float distance) const {
	for (int i = 0; i < mSegmentLengths.size(); ++i) {
		if (mSegmentLengths[i] < distance) {
			distance -= mSegmentLengths[i];
			continue;
		}
		float t = distance / mSegmentLengths[i];
		return Lerp(mPoints[i], mPoints[i + 1], t);
	}
	throw std::runtime_error("The given distance is greater, than the length of spline!");
	return V();
}

template <class V>
std::vector<V> EvenlySpacedSplineAdapter<V>::GeneratePoints(int res) const {
	std::vector<V> evenPoints;
	const float step_size = mSplineLength / float(res);
	for (float t = 0.f; t < mSplineLength; t += step_size) 
		evenPoints.push_back(GetPoint(t));
	return evenPoints;
}

} // vanyka
#endif
