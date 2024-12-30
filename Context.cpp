#include "nslcc.hpp"

namespace Context {
Context &get_instance() {
    if (!instance) {
        instance = std::make_unique<Context>();
    }
    return *instance;
}

};  // namespace Context
