#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Writer.hpp"

namespace Context {

class Context {
   public:
    Context(){};
    ~Context(){};

    Context(const Context &) = delete;
    Context(Context &&) = delete;
    Context &operator=(const Context &) = delete;
    Context &operator=(Context &&) = delete;

    void set_writer(std::shared_ptr<Writer> writer) { this->writer = writer; }

    Writer &get_writer() { return *writer; }

    std::shared_ptr<Writer> writer;
};

#define WRITER Context::get_instance().get_writer()

static std::unique_ptr<Context> instance = nullptr;

Context &get_instance();
};  // namespace Context

#endif  // CONTEXT_HPP
