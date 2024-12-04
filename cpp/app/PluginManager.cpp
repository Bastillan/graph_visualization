#include <boost/dll/import.hpp> // for import_alias
#include <iostream>
#include <memory>
#include "PluginInterface.hpp"

namespace dll = boost::dll;

int main(int argc, char* argv[]) {
    if (argc == 2)
    {
        boost::dll::fs::path plugin_path = argv[1];

        boost::dll::shared_library lib(plugin_path);             // argv[1] contains path to directory with our plugin library

        auto create_plugin = lib.get<my_plugin_api*()>("create_plugin");

        std::shared_ptr<my_plugin_api> plugin(create_plugin());

        std::cout << "plugin->calculate(1.5, 1.5) call:  " << plugin->calculate(1.5, 1.5) << std::endl;
    }
}