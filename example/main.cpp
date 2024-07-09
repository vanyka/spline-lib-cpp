#include <iostream>
#include <memory>

#include <spline/catmull_rom.h>
#include <spline/even_distributed_spline_adapter.h>
#include "vector2.h"

#pragma region Macros

#ifndef NDEBUG
#define DEBUG
#endif

#pragma endregion


using vanyka::Vector2f;
using namespace vanyka::spline;

inline void VectorTest() {
	Vector2f vec1 = {0.5f, 0.2f};
	Vector2f vec2 = { 5.3f, -8.65f };
	std::cout << vec1 << '\t' << vec2 << std::endl;
	std::cout << "+: " << (vec1 + vec2) << std::endl;
	std::cout << "-: " << (vec1 - vec2) << std::endl;
	std::cout << "*: " << (vec1 * vec2) << std::endl;
	std::cout << "/: " << (vec1 / vec2) << std::endl;
	std::cout << "* 2.5: " << vec1 * 2.5f << " | " << 2.5f * vec1 << std::endl;
	std::cout << "/ 2.5: " << vec1 / 2.5f << std::endl;
	std::cout << Vector2f::one << std::endl;
	std::cout << Vector2f::left << std::endl;
	std::cout << Vector2f::Distance(vec1, vec2) << std::endl;
	std::cout << vec2.Normalize() << std::endl;
}

template<class T>
inline void PrintAsArray(const std::vector<T>& data) {
	std::cout << '{';
	for (int i = 0; i < data.size(); ++i) {
		if (i != 0) std::cout << ',';
		std::cout << data[i];
	}
	std::cout << '}' << std::endl;
}

template<class T>
inline void PrintVectorNodeData(const std::vector<T>& data) {
	std::cout << "nodes: " << data.size() << std::endl;
	for (int i = 0; i < data.size(); ++i) {
		std::cout << "node #" << i << ": " << data[i] << std::endl;
	}
}

int main(){
	// VectorTest();

	std::unique_ptr<Spline<Vector2f>> curve = std::make_unique<CatmullRomSpline<Vector2f>>();

	/*std::vector<Vector2f> points;
	points.push_back({ 3.f, 2.f });
	points.push_back({ -2.f, 6.f });
	points.push_back({ 12.f, 12.f });
	points.push_back({ 10.f, 14.f });
	points.push_back({ 5.f, 19.f });
	curve->AddSupportPoints(points.begin(), points.end());*/

	curve->AddSupportPoints<5>(new Vector2f[]{
		{ 3.f, 2.f },
		{ -2.f, 6.f },
		{ 12.f, 12.f },
		{ 10.f, 14.f },
		{ 5.f, 19.f }
	});

	std::vector<Vector2f> res;
	for (float t = 0.f; t <= 1.f; t += 1.f / 100.f) {
		res.push_back((*curve)(t));
	}

	std::cout << "[Normal Spline]" << std::endl;
	PrintAsArray(res);
	std::cout << "[Even Spline]" << std::endl;
	PrintAsArray(EvenDistributedSplineAdapter(*curve).GeneratePoints());
}