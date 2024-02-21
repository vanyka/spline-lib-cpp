#include <iostream>
#include <memory>

#include <splines/catmull_rom.h>
#include <splines/bezier.h>
#include "vector2.h"

#pragma region Macros

#ifndef NDEBUG
#define DEBUG
#endif

#pragma endregion


using namespace vanyka;

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

	std::vector<Vector2<float>> points;
	points.push_back({ 3.f, 2.f });
	points.push_back({ 4.f, 6.f });
	points.push_back({ 8.f, 8.f });
	points.push_back({ 10.f, 14.f });

	curve->AddSupportPoints(points.begin(), points.end());

#ifdef DEBUG
	PrintAsArray(curve->GeneratePoints());
#else
	PrintVectorNodeData(curve->GeneratePoints());
#endif // DEBUG

	
}