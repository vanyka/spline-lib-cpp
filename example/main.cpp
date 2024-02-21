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

inline void PrintGeoguessrData(const std::vector<Vector2f>& points) {
	std::cout << '{';
	for (int i = 0; i < points.size(); ++i) {
		// std::cout << "node #" << i << ": " << genps[i] << std::endl;
		if (i != 0) std::cout << ',';
		std::cout << points[i];
	}
	std::cout << '}' << std::endl;
}

int main(){
	// VectorTest();

	std::unique_ptr<vanyka::Curve<Vector2f>> curve = std::make_unique<vanyka::CatmullRom<Vector2f, true>>();

	std::vector<Vector2<float>> points;
	points.push_back({ 3.f, 2.f });
	points.push_back({ 4.f, 6.f });
	points.push_back({ 8.f, 8.f });
	points.push_back({ 10.f, 14.f });

	curve->AddSupportPoints(points.begin(), points.end());

	std::vector<Vector2f> genps = curve->GeneratePoints(10);

	PrintGeoguessrData(genps);
	/*std::cout << "nodes: " << genps.size() << std::endl;
	for (int i = 0; i < genps.size(); ++i) {
		std::cout << "node #" << i << ": " << genps[i] << std::endl;
	}*/
}