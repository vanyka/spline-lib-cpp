#ifndef __H_VANYKA_SPLINE
#define __H_VANYKA_SPLINE

#include <vector>

namespace vanyka::spline
{

template <class V>
class Spline
{
protected:
    std::vector<V> mSupportPoints;
    
    static std::pair<float, size_t> CalculateSegmentInfo(const float& t, size_t segmentCount);
public:
    virtual ~Spline() = default;
    std::vector<V>&         GetSupportPoints() { return mSupportPoints; }
    std::vector<V>          GetSupportPoints() const { return mSupportPoints; }
    void                    AddSupportPoint(const V &p);
    template <int N>
    void                    AddSupportPoints(V points[N]);
    template <class It>
    void                    AddSupportPoints(const It &begin, const It &end);
    virtual std::vector<V>  GeneratePoints(int res = 10) const = 0;
    virtual V               operator()(const float& t) const = 0;
};

template <class V>
std::pair<float, size_t> Spline<V>::CalculateSegmentInfo(const float& t, size_t segmentCount){
    if(t < 0.f || t > 1.f) throw "Out of bounds!";
    float localt = t * float(segmentCount);
    size_t index = floor(localt);
    localt -= float(index);
    return std::make_pair(localt, index);
}

template <class V>
template <int N>
void Spline<V>::AddSupportPoints(V points[N])
{
    auto prev_size = mSupportPoints.size();
    mSupportPoints.resize(prev_size + N);
        for (int i = 0; i < N; ++i)
            mSupportPoints[prev_size + i] = points[i];
}

template <class V>
template <class It>
void Spline<V>::AddSupportPoints(const It &begin, const It &end)
{
    int N = std::distance(begin, end);
    auto prev_size = mSupportPoints.size();
    mSupportPoints.resize(prev_size + N);

    int i = 0;
    for (It current = begin; current != end; ++current)
        mSupportPoints[prev_size + i++] = *current;
}

template <class V>
void Spline<V>::AddSupportPoint(const V &p)
{
    mSupportPoints.push_back(p);
}

} // vanyka::spline
#endif