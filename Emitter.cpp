#include "nslcc.hpp"

void emit_input(const Input &input) {
    WRITER << "input ";
    if (input.width != 1) {
        WRITER << "[" << input.width - 1 << ":0"
               << "]";
    }
    WRITER << " " << input.name;
}

void emit_output(const Output &output) {
    WRITER << "output ";
    if (output.width != 1) {
        WRITER << "[" << output.width - 1 << ":0"
               << "]";
    }
    WRITER << " " << output.name;
}

void emit_inout(const Inout &inout) {
    WRITER << "inout ";
    if (inout.width != 1) {
        WRITER << "[" << inout.width - 1 << ":0"
               << "]";
    }
    WRITER << " " << inout.name;
}

void emit_module(const Module &module) {
    auto name = module.name;

    WRITER << "module " << name << " (" << std::endl;
    WRITER.indent_in();

    for (auto &port : module.ports) {
        if (port.second->is<Input>()) {
            emit_input(port.second->get<Input>());
        } else if (port.second->is<Output>()) {
            emit_output(port.second->get<Output>());
        } else if (port.second->is<Inout>()) {
            emit_inout(port.second->get<Inout>());
        } else {
            assert(!"Unknown port type");
        }
        if (port.first != module.ports.rbegin()->first) {
            WRITER << "," << std::endl;
        } else {
            WRITER << std::endl;
        }
    }
    WRITER.indent_out();
    WRITER << ");" << std::endl;
    WRITER << "endmodule" << std::endl;
}

void Emitter::generate() const {
    auto nodes = parser->parse();

    for (auto &node : nodes) {
        if (node->is<Module>()) {
            auto module = node->get<Module>();
            emit_module(module);
        }
    }
}
