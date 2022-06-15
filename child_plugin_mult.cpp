#include <boost/config.hpp>
#include <boost/dll/import.hpp>
#include <iostream>
#include "parent_plugin_api.hpp"

namespace child_plugin_namespace {

class child_plugin_mult: public parent_plugin_api {
public:
	parent_plugin_api plugin_sum;
	child_plugin_mult(parent_plugin_api &plugin_sum_arg) {
		plugin_sum = plugin_sum_arg;
		std::cout << "child_plugin_mult_constructor" << std::endl;
	}

	std::string name() const {
		return "sum";
	}

	float calculate(float x, float y) {

		//std::cout << "parent_plugin->calculate(1.5, 1.5) call: " << plugin_sum->calculate(1.5,1.5) << std::endl;
		return x * y;
	}

	    // Factory method
	static boost::shared_ptr<child_plugin_mult> create() {
        	return boost::shared_ptr<child_plugin_mult>(
            		new child_plugin_mult()
        	);
    	}

	~child_plugin_mult() {
		std::cout << "child_plugin_mult_destructor" << std::endl;
	}
};

//extern "C" BOOST_SYMBOL_EXPORT child_plugin_mult child_plugin;
//child_plugin_mult child_plugin;
//

BOOST_DLL_ALIAS(
    child_plugin_namespace::child_plugin_mult::create, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
