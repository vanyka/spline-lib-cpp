#pragma once

#include <algorithm>
#include <vector>
#include <cassert>

namespace vanyka {

template <typename V>
class Curve
{
protected:
	std::vector<V> mWayPoints;
	std::vector<V> mNodes;
	std::vector<float> mDistances;
	int mSteps;

public:
	Curve() : mSteps(10) {}

	void AddWayPoint(const V &point);
	template <class It>
	void AddWayPoints(const It &begin, const It &end, bool genControlPoints = true);
	void Clear();

	V Node(int i) const { return mNodes[i]; }
	float LengthFromStartingPoint(int i) const { return mDistances[i]; }
	size_t NodeCount() const { return static_cast<int>(mNodes.size()); }
	bool IsEmpty() { return mNodes.empty(); }
	double TotalLength() const
	{
		assert(!mDistances.empty());
		return mDistances[mDistances.size() - 1];
	}

	void SetSteps(int steps) { mSteps = steps; }

protected:
	void AddNode(const V &node);
	virtual void _OnWayPointAdded() = 0;
};

// Definitions
template <typename V>
template <class It>
void Curve<V>::AddWayPoints(const It &begin, const It &end, bool genControlPoints)
{
	const auto size = std::distance(begin, end);
	if (size < 2)
		genControlPoints = false;

	if (genControlPoints)
	{
		const V c1 = *begin * 2 - *(begin + 1);
		this->AddWayPoint(c1);
	}

	std::for_each(begin, end, [this](const V &p){ 
		this->AddWayPoint(p); 
	});

	if (genControlPoints)
	{
		const V c2 = *(end - 1) * 2 - *(end - 2);
		this->AddWayPoint(c2);
	}
}

template <typename V>
void Curve<V>::Clear()
{
	mNodes.clear();
	mWayPoints.clear();
	mDistances.clear();
}

template <typename V>
void Curve<V>::AddWayPoint(const V &point)
{
	mWayPoints.push_back(point);
	_OnWayPointAdded();
}

template <typename V>
void Curve<V>::AddNode(const V &node)
{
	if (!mNodes.empty() && mNodes.back() == node)
		return;

	mNodes.push_back(node);

	if (mNodes.size() == 1)
	{
		mDistances.push_back(0);
	}
	else
	{
		size_t new_node_index = mNodes.size() - 1;

		float segment_distance = (mNodes[new_node_index] - mNodes[new_node_index - 1]).Length();
		mDistances.push_back(segment_distance + mDistances[new_node_index - 1]);
	}
}

} // vanyka