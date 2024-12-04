#include <iostream>
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include "PluginInterface.hpp"

namespace my_namespace {

class my_plugin_sum : public my_plugin_api {
public:
    my_plugin_sum() {}

    std::string name() const {
        return "sum";
    }

    float y(float x, float a, float b) {
        return a * x + b;
    }

    ~my_plugin_sum() {}
};

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT my_plugin_api* create_plugin() {
    return new my_plugin_sum();
}

} // namespace my_namespace 