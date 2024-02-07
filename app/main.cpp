#include <iostream>
#include <memory>

#include <catmull_rom.h>
#include "vec2.h"

using VEC2F = VEC2<float>;

using std::cout;
int main(){
    vanyka::CatmullRom<VEC2F> curve;
	curve.SetSteps(10); // generate 100 interpolate points between the last 4 way points

	std::vector<VEC2F> points;
	points.push_back(VEC2F(2.f, 3.f));
	points.push_back(VEC2F(3.f, 2.f));
	points.push_back(VEC2F(4.f, 3.f));
	points.push_back(VEC2F(5.f, 8.f));

	curve.AddWayPoints(points.begin(), points.end());

	std::cout << "nodes: " << curve.NodeCount() << std::endl;
	std::cout << "total length: " << curve.TotalLength() << std::endl;
	for (int i = 0; i < curve.NodeCount(); ++i) {
		std::cout << "node #" << i << ": (" << curve.Node(i).x << ", " << curve.Node(i).y << ")" << std::endl;
	}
}