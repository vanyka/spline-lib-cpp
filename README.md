# C++ Header-Only Spline Library
This Library calculates different types of splines(Linear, Catmull Rom, Bezier) based on the given support points.

## Features
- For Catmull-Rom splines there is a setting by which you can set your spline to pass all your given points or if it is unset then the first and last given point is a control point only (curve does not passes through).

## Setup the Test project
you will need to have the following installed:
- CMake (3.10 or newer)
- Python (only for scripts)

Available scripts for building IDE projects:
- Visual Studio 2019, 2022

Or you can always generate it in the command line by using the following command at the root directory:
```
cmake -B build
```