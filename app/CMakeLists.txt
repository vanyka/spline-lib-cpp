project(App VERSION 0.1.0)
file(GLOB_RECURSE source_list "*.cpp" "*.hpp" "*.h")
add_executable(App ${source_list})
configure_file(config.h.in config.h)
target_link_libraries(App PUBLIC Core)
target_include_directories(App PUBLIC 
    "${CMAKE_SOURCE_DIR}/core"
    "${CMAKE_BINARY_DIR}"
)