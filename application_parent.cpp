#include <boost/dll/import.hpp>
#include <iostream>
#include "parent_plugin_api.hpp"

namespace dll = boost::dll;

int main(int argc, char* argv[]) {
	boost::filesystem::path lib_path(argv[1]);
	boost::shared_ptr<parent_plugin_api> plugin_sum;
	std::cout << "Loading the plugin" << std::endl;

	plugin_sum = dll::import<parent_plugin_api> (
		lib_path / "parent_plugin_sum",
		"parent_plugin",
		dll::load_mode::append_decorations
	);

	std::cout << "plugin_sum->calculate(1.5, 1.5) call: " << plugin_sum->calculate(1.5,1.5) << std::endl;

}	
