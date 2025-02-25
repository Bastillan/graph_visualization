# graph_visualization
## Description
Graph visualization app written in `C++` and `Python`.

It supports GraphML format.

The app can be extended with user plugins that implement additional graph layout algorithms.

It was written in the fifth semester (2024Z) as a project for the course *Advanced programming in C++ (ZPR)* at the Warsaw University of Technology.

## Getting started
Project uses `conan` and `pdm` so make sure that you have them installed and that you have your `conan` profile set (`conan profile detect --force`).

### Compilation
To compile `C++` part of the app simply run `make compile` in the root folder of the repository.

It will install all required dependencies using `conan` and compile the app in `Release` mode.

### Python setup
To setup `Python` project dependencies using `pdm` run `make py_setup`.

### Run app
To run whole app run `make run`.

## Development commands
### Documentation
To generate documentation from code ensure you have `doxygen` installed and run `make doxy` then open */docs/html/index.html* file.

### Tests
To test the app run `make compile_debug` and then `make test`.

### Linting and formatting
`C++` code is linted using `clang tidy` during compilation.

To format `C++` code run `make format_cpp`.

To lint `Python` code run `make lint_py`.

To format `Python` code run `make format_py`.

## Plugins
User plugins must implement **plugin interface** defined in *plugin_interface.hpp* file and be compiled as dynamic libraries.

### Adding custom plugin
The easiest and most recommended option is to place your custom plugin in a dedicated directory in *cpp/app/plugins* directory.

You must then add `add_subdirectory(*your_plugin_directory_name*)` line at the end of *cpp/app/plugins/CMakeLists.txt* file.

You can model your plugin *CMakeLists.txt* file on the ones provided with default plugins.

```cmake
project(*your_plugin_name*)

add_library(*your_plugin_name* SHARED *your_plugin_name.cpp*)
target_link_libraries(*your_plugin_name* PRIVATE Boost::boost)
set_target_properties(*your_plugin_name* PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/app/plugins/dist)
```

Compiled plugins are stored in *cpp/app/plugins/dist* directory.
