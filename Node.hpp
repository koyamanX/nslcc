#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <string>
#include <variant>

struct Signal {
    Signal(std::string &signal_name) : name(signal_name){};
    Signal(std::string &signal_name, size_t width)
        : name(signal_name), width(width){};
    Signal(std::string &signal_name, size_t width, bool assigned)
        : name(signal_name), width(width), assigned(assigned){};
    ~Signal(){};
    std::string name;
    size_t width = 1;
    bool assigned = false;
};

struct Wire : Signal {
    Wire(std::string &wire_name) : Signal(wire_name){};
    Wire(std::string &wire_name, size_t width) : Signal(wire_name, width){};
    Wire(std::string &wire_name, size_t width, bool assigned)
        : Signal(wire_name, width, assigned){};
    ~Wire(){};
};

struct Reg : Signal {
    Reg(std::string &reg_name) : Signal(reg_name){};
    Reg(std::string &reg_name, size_t width) : Signal(reg_name, width){};
    Reg(std::string &reg_name, size_t width, bool assigned)
        : Signal(reg_name, width, assigned){};
    ~Reg(){};
};

struct Input : Signal {
    Input(std::string &input_name) : Signal(input_name){};
    Input(std::string &input_name, size_t width) : Signal(input_name, width){};
    Input(std::string &input_name, size_t width, bool assigned)
        : Signal(input_name, width, assigned){};
    ~Input(){};
};

struct Output : Signal {
    Output(std::string &output_name) : Signal(output_name){};
    Output(std::string &output_name, size_t width)
        : Signal(output_name, width){};
    Output(std::string &output_name, size_t width, bool assigned)
        : Signal(output_name, width, assigned){};
    ~Output(){};
};

struct Inout : Signal {
    Inout(std::string &inout_name) : Signal(inout_name){};
    Inout(std::string &inout_name, size_t width) : Signal(inout_name, width){};
    Inout(std::string &inout_name, size_t width, bool assigned)
        : Signal(inout_name, width, assigned){};
    ~Inout(){};
};

class Node;
struct Module {
    Module(std::string &module_name) : name(module_name){};
    Module(std::string &module_name, bool declared)
        : name(module_name), declared(declared){};
    ~Module(){};

    std::string name;
    bool declared = false;
    std::map<std::string, std::shared_ptr<Node>> ports;
};

class Node {
    using NodeType = std::variant<Module, Wire, Reg, Input, Output, Inout>;

   public:
    template <typename T>
    Node(T &&value) : value(std::forward<T>(value)) {}

    template <typename T>
    constexpr bool is() const noexcept {
        return std::holds_alternative<T>(value);
    }

    template <typename T>
    constexpr bool isNot() const noexcept {
        return !is<T>();
    }

    template <typename T>
    constexpr const T &get() const noexcept {
        return std::get<T>(value);
    }

    template <typename T>
    bool operator==(const T &rhs) const noexcept {
        return std::holds_alternative<T>(value) && std::get<T>(value) == rhs;
    }

    template <typename T>
    bool operator!=(const T &rhs) const noexcept {
        return !(*this == rhs);
    }

   private:
    NodeType value;
};

#endif  // NODE_HPP
