#include <cassert>
#include <cctype>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "nslcc.hpp"

int main(int argc, char **argv) {
    std::ifstream input;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    input.open(argv[1]);
    if (!input.is_open()) {
        std::cout << "Error: could not open file " << argv[1] << std::endl;
        return 1;
    }

    Context::get_instance().set_writer(std::make_shared<Writer>(std::cout));

    std::unique_ptr<Parser> parser = std::make_unique<Parser>(input);
    std::unique_ptr<Emitter> emitter =
        std::make_unique<Emitter>(std::move(parser));

    emitter->generate();

    return 0;
}
