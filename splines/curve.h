#ifndef __H_VANYKA_CURVE
#define __H_VANYKA_CURVE

#include <algorithm>
#include <vector>
// #include <cassert>
// #include <stdexcept>

namespace vanyka {

template <class V>
class Curve
{
protected:
	std::vector<V> mSupportPoints;

public:
    void AddSupportPoint(const V& p);
    template<class It> 
    void AddSupportPoints(const It& begin, const It& end);
    virtual std::vector<V> GeneratePoints(int res = 10) const;
};

template<class V>
template<class It>
void Curve<V>::AddSupportPoints(const It& begin, const It& end){
    for(It current = begin; current != end; ++current)
        AddSupportPoint(*current);
}

template<class V>
void Curve<V>::AddSupportPoint(const V& p){
    mSupportPoints.push_back(p);
}

template<class V>
std::vector<V> Curve<V>::GeneratePoints(int res) const {
    std::vector<V> points;

    auto Lerp = [](float t, const V& p1, const V& p2){
        return p1 + (p2 - p1) * t;
    };

    // Filtering the empty and one point case
    switch (mSupportPoints.size())
    {
    case 0: return points;
    case 1: return mSupportPoints;
    }

    // Calculation
    points.reserve(res * mSupportPoints.size());
    for(int i = 1; i < mSupportPoints.size(); ++i){
        const V& prev = mSupportPoints[i - 1];
        const V& curr = mSupportPoints[i];
        points.push_back(prev);
        for(int j = 1; j < res; ++j){
            const float t = (float)j / (float) res;
            points.push_back(Lerp(t, prev, curr));
        }
    }
    points.push_back(mSupportPoints.back());
    return points;
}

} // vanyka
#endif