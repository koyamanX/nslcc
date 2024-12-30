#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <memory>
#include <vector>

#include "Node.hpp"

class Parser {
   public:
    Parser(std::ifstream &in);
    ~Parser();

    std::vector<std::shared_ptr<Node>> parse();

   private:
    std::map<std::string, std::shared_ptr<Node>> parse_iolists();
    Lexer lexer;
    std::vector<std::shared_ptr<Node>> nodes;
};

#endif  // PARSER_HPP
