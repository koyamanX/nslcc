#ifndef EMITTER_HPP
#define EMITTER_HPP

#include "Parser.hpp"
#include "Writer.hpp"

class Emitter {
   public:
    Emitter(std::unique_ptr<Parser> parser) : parser(std::move(parser)){};
    ~Emitter(){};

    void generate() const;

   private:
    std::unique_ptr<Parser> parser;
};

#endif  // EMITTER_HPP
