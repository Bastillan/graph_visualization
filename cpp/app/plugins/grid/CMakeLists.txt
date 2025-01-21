project(grid_plugin)

add_library(plugin_grid SHARED plugin_grid.cpp)
target_link_libraries(plugin_grid PRIVATE Boost::boost)
set_target_properties(plugin_grid PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/app/plugins/dist)
