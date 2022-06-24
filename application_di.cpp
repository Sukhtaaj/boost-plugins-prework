#include "boost/shared_ptr.hpp"
#include <boost/dll/import.hpp>
#include "boost/function.hpp"
#include <boost/di.hpp>
include "ioperation.hpp"
#include "dot_product.cpp"
#include <iostream>

namespace di = boost::di;
namespace dll = boost::dll;

template <class T>
constexpr
std::string_view
type_name()
{
    using namespace std;
#ifdef __clang__
    string_view p = __PRETTY_FUNCTION__;
    return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
    return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

class app {
 private:
	 boost::shared_ptr<ioperation> ptr_;
 public:
  	app(boost::shared_ptr<ioperation> ptr)
	 : ptr_(ptr)
  	{
           std::cout<<"name: " << ptr_->name()<<std::endl;
	}

};


int main(int argc, char* argv[]) {

	//setting up paths to library(.so) files
        boost::filesystem::path shared_library_path(".");    // argv[1] contains path to directory with our plugin library
        boost::filesystem::path child_library_path = shared_library_path/"dot_product";
        boost::filesystem::path parent_library_path = shared_library_path/"sum";

        //defining function types for lib constructors
        typedef boost::shared_ptr<ioperation> (sum_create_t)();
        typedef boost::shared_ptr<ioperation> (dot_product_create_t)(boost::shared_ptr<ioperation>);
        boost::function<sum_create_t> sum_creator;
        boost::function<dot_product_create_t> dot_product_creator;

        //importing SUM lib constructor(takes no arg)
        sum_creator = boost::dll::import_alias<sum_create_t>(   // type of imported symbol must be explicitly specified
                parent_library_path,                            // path to library
                "create_sum",                                   // symbol to import
                dll::load_mode::append_decorations              // do append extensions and prefixes
        );

        //importing DOT_PRODUCT lib constructor(takes 1 arg of ptr to IOPERATION)
        dot_product_creator = boost::dll::import_alias<dot_product_create_t>(   // type of imported symbol must be explicitly specified
                child_library_path,                                             // path to library
                "create_dot_product",                                           // symbol to import
                dll::load_mode::append_decorations                              // do append extensions and prefixes
        );

        //creating a ptr to SUM object
        boost::shared_ptr<ioperation> sum_ptr = sum_creator();

        //creating a ptr to DOT_PRODUCT object(passing above created SUM object ptr)
        boost::shared_ptr<ioperation> dot_product_ptr = dot_product_creator(sum_ptr);
        auto use_sum = true;

	//std::cout << typeid(sum_ptr).name() << '\n';
        //std::cout << typeid(dot_product_ptr).name() << '\n';
	std::cout << type_name<decltype(sum_ptr)>() << '\n';

	const auto injector = di::make_injector(
          di::bind<ioperation>().to([&](const auto& injector) -> boost::shared_ptr<ioperation> {
            if (use_sum)
              return injector.template create<boost::shared_ptr<sum_namespace::sum>>();
            else
              return injector.template create<boost::shared_ptr<dot_product_namespace::dot_product>>();
        })
	);
  
        //const auto injector = di::make_injector(
	//  di::bind<ioperation>().to<boost::shared_ptr<sum_namespace::sum>>()
	//);
	injector.create<app>();
//        
//	//boost::shared_ptr<ioperation> arg;
//	app app_obj(sum_ptr);
}

