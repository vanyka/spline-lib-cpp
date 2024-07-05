project(spline_example)
file(GLOB_RECURSE source_list "*.cpp" "*.hpp" "*.h" "../splines/*.h")
add_executable(spline_example ${source_list})
target_include_directories(spline_example PUBLIC 
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_BINARY_DIR}"
)