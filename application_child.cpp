#include "boost/shared_ptr.hpp"
#include <boost/dll/import.hpp>
#include "boost/function.hpp"
#include <iostream>
#include "parent_plugin_api.hpp"

namespace dll = boost::dll;

int main(int argc, char* argv[]) {
	boost::filesystem::path shared_library_path(argv[1]);    // argv[1] contains path to directory with our plugin library
    	boost::filesystem::path child_library_path = shared_library_path/"child_plugin_mult";
	boost::filesystem::path parent_library_path = shared_library_path/"parent_plugin_sum";
	std::cout << "Loading the child plugin" << std::endl;

	typedef boost::shared_ptr<parent_plugin_api> (p_pluginapi_create_t)();
	typedef boost::shared_ptr<parent_plugin_api> (c_pluginapi_create_t)(boost::shared_ptr<parent_plugin_api>);
	boost::function<p_pluginapi_create_t> p_creator;
	boost::function<c_pluginapi_create_t> c_creator;

	p_creator = boost::dll::import_alias<p_pluginapi_create_t>(   // type of imported symbol must be explicitly specified
        	parent_library_path,                                  // path to library
        	"create_parent_plugin",                               // symbol to import
        	dll::load_mode::append_decorations                    // do append extensions and prefixes
    	);

	c_creator = boost::dll::import_alias<c_pluginapi_create_t>(   // type of imported symbol must be explicitly specified
        	child_library_path,                                   // path to library
        	"create_plugin",                                      // symbol to import
        	dll::load_mode::append_decorations                    // do append extensions and prefixes
    	);


	//plugin_sum = dll::import<parent_plugin_api> (
	//	lib_path / "parent_plugin_sum"
	//	"parent_plugin",
	//	dll::load_mode::append_decorations
	//);

	//std::cout << "child_plugin->calculate(1.5, 1.5) call: " << child_plugin->calculate(1.5,1.5) << std::endl;
	
	boost::shared_ptr<parent_plugin_api> p_plugin = p_creator();
	boost::shared_ptr<parent_plugin_api> c_plugin = c_creator(p_plugin);
	std::cout << "p_plugin->calculate(1.5, 1.5) call:  " << p_plugin->calculate(1.5, 1.5) << std::endl;
    	std::cout << "c_plugin->calculate(1.5, 1.5) call:  " << c_plugin->calculate(1.5, 1.5) << std::endl;
    	//std::cout << "Plugin Name:  " << plugin->name() << std::endl;
}	
