project(Core)

file(GLOB_RECURSE header_list "*cpp" "*.h" "*.hpp")
add_library(Core ${header_list})
