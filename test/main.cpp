#include <iostream>
#include <memory>

#include <catmull_rom.h>
#include "vector2.h"

using std::cout;
using namespace vanyka;

inline void VectorTest() {
	Vector2f vec1 = {0.5f, 0.2f};
	Vector2f vec2 = { 5.3f, -8.65f };
	cout << vec1 << '\t' << vec2 << std::endl;
	cout << "+: " << (vec1 + vec2) << std::endl;
	cout << "-: " << (vec1 - vec2) << std::endl;
	cout << "*: " << (vec1 * vec2) << std::endl;
	cout << "/: " << (vec1 / vec2) << std::endl;
	cout << "* 2.5: " << vec1 * 2.5f << " | " << 2.5f * vec1 << std::endl;
	cout << "/ 2.5: " << vec1 / 2.5f << std::endl;
}

int main(){
	// VectorTest();

    vanyka::CatmullRom<Vector2<float>> curve;
	curve.SetSteps(10); // generate 100 interpolate points between the last 4 way points

	std::vector<Vector2<float>> points;
	points.push_back({ 2.f, 3.f });
	points.push_back({ 3.f, 2.f });
	points.push_back({ 4.f, 3.f });
	points.push_back({ 5.f, 8.f });

	curve.AddWayPoints(points.begin(), points.end());

	std::cout << "nodes: " << curve.NodeCount() << std::endl;
	std::cout << "total length: " << curve.TotalLength() << std::endl;
	for (int i = 0; i < curve.NodeCount(); ++i) {
		std::cout << "node #" << i << ": " << curve.Node(i) << std::endl;
	}
}