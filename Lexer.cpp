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

void Lexer::expect(ReservedKeywordType type) {
    if (*tokens.front() != type) {
        std::cout << "Error: expected " << static_cast<int>(type) << std::endl;
        assert(false);
    }
}

bool Lexer::tokenize() {
    while (true) {
        std::string token_str;

        skip_whitespace();

        if (input.eof()) {
            tokens.push_back(std::make_shared<Token>(ReservedKeywordType::EoF));
            break;
        }

        auto it = reserved_symbols.find(std::string(1, peek_char()));
        if (it != reserved_symbols.end()) {
            token_str += get_char();
            tokens.push_back(std::make_shared<Token>(it->second));
            continue;
        }

        while (std::isalnum(peek_char())) {
            token_str += get_char();
        }

        it = reserved_keywords.find(token_str);
        if (it != reserved_keywords.end()) {
            tokens.push_back(std::make_shared<Token>(it->second));
            continue;
        }

        if (std::isdigit(token_str[0])) {
            tokens.push_back(std::make_shared<Token>(Number(stoi(token_str))));
            continue;
        }

        tokens.push_back(std::make_shared<Token>(Identifier(token_str)));
    }
    return true;
}
