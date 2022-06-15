#include <boost/dll/import.hpp>
#include <iostream>
#include "parent_plugin_api.hpp"

namespace dll = boost::dll;

int main(int argc, char* argv[]) {
	boost::filesystem::path lib_path(argv[1]);
	boost::shared_ptr<parent_plugin_api> child_plugin;
	std::cout << "Loading the child plugin" << std::endl;

	child_plugin = dll::import<parent_plugin_api> (
		lib_path / "child_plugin_mult",
		"child_plugin",
		dll::load_mode::append_decorations
	);

	std::cout << "child_plugin->calculate(1.5, 1.5) call: " << child_plugin->calculate(1.5,1.5) << std::endl;

}	
