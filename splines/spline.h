#ifndef __H_VANYKA_SPLINE
#define __H_VANYKA_SPLINE

#include <vector>

namespace vanyka {

template <class V>
class Spline
{
protected:
	std::vector<V> mSupportPoints;

public:
    void AddSupportPoint(const V& p);
    template<class It> 
    void AddSupportPoints(const It& begin, const It& end);
    virtual std::vector<V> GeneratePoints(int res = 10) const = 0;
};

template<class V>
template<class It>
void Spline<V>::AddSupportPoints(const It& begin, const It& end){
    for(It current = begin; current != end; ++current)
        AddSupportPoint(*current);
}

template<class V>
void Spline<V>::AddSupportPoint(const V& p){
    mSupportPoints.push_back(p);
}

} // vanyka
#endif