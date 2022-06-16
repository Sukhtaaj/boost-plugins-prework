#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include "parent_plugin_api.hpp"
#include <iostream>

namespace parent_plugin_namespace {

class parent_plugin_sum: public parent_plugin_api {
public:
	parent_plugin_sum() {
		std::cout << "parent_plugin_sum_constructor" << std::endl;
	}

	std::string name() const {
		return "sum";
	}

	float calculate(float x, float y) {
		return x + y;
	}

	~parent_plugin_sum() {
		std::cout << "parent_plugin_sum_destructor" << std::endl;
	}


       // Factory method
        static boost::shared_ptr<parent_plugin_sum> create() {
                return boost::shared_ptr<parent_plugin_sum>(
                        new parent_plugin_sum()
                );
        }
};
//extern "C" BOOST_SYMBOL_EXPORT parent_plugin_sum parent_plugin;
//parent_plugin_sum parent_plugin;

}

BOOST_DLL_ALIAS(
    parent_plugin_namespace::parent_plugin_sum::create, // <-- this function is exported with...
    create_parent_plugin                               // <-- ...this alias name
)

