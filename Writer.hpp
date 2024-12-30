#ifndef WRITER_HPP
#define WRITER_HPP

#include <cassert>
#include <iostream>
#include <string>

class Writer {
   public:
    Writer(std::ostream &out) : output(out), indent(0), newline(true) {}
    ~Writer() {}

    void indent_in() {
        indent += 4;
        assert(indent >= 0);
    }
    void indent_out() {
        indent -= 4;
        assert(indent >= 0);
    }

    template <typename T>
    Writer &operator<<(const T &data) {
        if (newline) {
            output << std::string(indent, ' ');
            newline = false;
        }

        output << data;
        return *this;
    }

    Writer &operator<<(std::ostream &(*manip)(std::ostream &)) {
        output << std::string(indent, ' ');
        manip(output);
        newline = true;
        return *this;
    }

   private:
    std::ostream &output;
    int indent = 0;
    bool newline = true;
};

#endif  // WRITER_HPP
