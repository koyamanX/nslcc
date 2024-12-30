#ifndef LEXER_HPP
#define LEXER_HPP

#include <cassert>
#include <cctype>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Token.hpp"

class Lexer {
   public:
    Lexer(std::ifstream &in) : input(in){};
    ~Lexer(){};

    template <typename T>
    const T &get() {
        auto token = tokens.front();
        tokens.pop_front();
        return token->get<T>();
    }

    bool peek(ReservedKeywordType type) { return *tokens.front() == type; }

    template <typename T>
    bool peek() {
        return tokens.front()->is<T>();
    }

    bool consume(ReservedKeywordType type) {
        if (*tokens.front() == type) {
            tokens.pop_front();
            return true;
        }
        return false;
    }

    template <typename T>
    bool consume() {
        if (tokens.front()->is<T>()) {
            tokens.pop_front();
            return true;
        }
        return false;
    }

    template <typename T>
    void expect() {
        if (tokens.front()->isNot<T>()) {
            std::cout << "Error: expected " << typeid(T).name() << std::endl;
            assert(false);
        }
    }

    void expect(ReservedKeywordType type);

    bool tokenize();

   private:
    inline char get_char() { return input.get(); }

    inline char peek_char() { return input.peek(); }

    inline void skip_whitespace() {
        while (std::isspace(peek_char())) {
            get_char();
        }
    }

    std::ifstream &input;
    std::unordered_map<std::string, ReservedKeywordType> reserved_keywords = {
        {"declare", ReservedKeywordType::DECLARE},
        {"module", ReservedKeywordType::MODULE},
        {"input", ReservedKeywordType::INPUT},
        {"output", ReservedKeywordType::OUTPUT},
        {"inout", ReservedKeywordType::INOUT},
    };
    std::unordered_map<std::string, ReservedKeywordType> reserved_symbols = {
        {"{", ReservedKeywordType::LBRACE},
        {"}", ReservedKeywordType::RBRACE},
        {";", ReservedKeywordType::SEMICOLON},
        {"[", ReservedKeywordType::LBRACKET},
        {"]", ReservedKeywordType::RBRACKET},
    };
    std::deque<std::shared_ptr<Token>> tokens;
};

#endif  // LEXER_HPP
