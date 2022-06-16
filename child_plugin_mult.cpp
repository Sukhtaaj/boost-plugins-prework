#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include <iostream>
#include "parent_plugin_api.hpp"

namespace child_plugin_namespace {

class child_plugin_mult: public parent_plugin_api {
	boost::shared_ptr<parent_plugin_api> pps;

public:
	child_plugin_mult(boost::shared_ptr<parent_plugin_api> &arg) {
		pps = arg;
		std::cout << "child_plugin_mult_constructor" << std::endl;
	}

	std::string name() const {
		return "mult";
	}

	float calculate(float x, float y) {
		std::cout << "Inside child calculate:" << pps->calculate(x,y) << std::endl;
		return x * y;
	}

	// Factory method
	static boost::shared_ptr<parent_plugin_api> create_child(boost::shared_ptr<parent_plugin_api> pps) {
        	return boost::shared_ptr<parent_plugin_api>(
            		new child_plugin_mult(pps)
        	);
    	}

	~child_plugin_mult() {
		std::cout << "child_plugin_mult_destructor" << std::endl;
	}
    };
};

//extern "C" BOOST_SYMBOL_EXPORT child_plugin_mult child_plugin;
//child_plugin_mult child_plugin;
//

BOOST_DLL_ALIAS(
    child_plugin_namespace::child_plugin_mult::create_child, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
