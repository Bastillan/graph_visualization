project(circular_plugin)

add_library(plugin_circular SHARED plugin_circular.cpp)
target_link_libraries(plugin_circular PRIVATE Boost::boost)
set_target_properties(plugin_circular PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/app/plugins/dist)
