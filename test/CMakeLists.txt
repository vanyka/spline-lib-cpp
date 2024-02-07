project(Test VERSION 0.1.0)
file(GLOB_RECURSE source_list "*.cpp" "*.hpp" "*.h" "../splines/*.h")
add_executable(Test ${source_list})
target_include_directories(Test PUBLIC 
    "${CMAKE_SOURCE_DIR}/splines"
    "${CMAKE_BINARY_DIR}"
)