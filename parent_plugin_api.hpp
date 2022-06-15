#include <string>

class parent_plugin_api {
public:
    virtual std::string name() const = 0;
    virtual float calculate(float x, float y) = 0;

    virtual ~parent_plugin_api() {}
};


