project(SplineExample)
file(GLOB_RECURSE source_list "*.cpp" "*.hpp" "*.h" "../spline/*.h")
add_executable(SplineExample ${source_list})
target_include_directories(SplineExample PUBLIC 
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_BINARY_DIR}"
)