#include "nslcc.hpp"

Parser::Parser(std::ifstream &in) : lexer(in) {}
Parser::~Parser() {}

std::vector<std::shared_ptr<Node>> Parser::parse() {
    lexer.tokenize();

    while (true) {
        if (lexer.peek(ReservedKeywordType::MODULE)) {
            lexer.consume(ReservedKeywordType::MODULE);

            lexer.expect<Identifier>();

            std::string module_name = lexer.get<Identifier>();

            lexer.consume(ReservedKeywordType::LBRACE);
            lexer.consume(ReservedKeywordType::RBRACE);

            nodes.push_back(std::make_shared<Node>(Module(module_name)));
        } else if (lexer.peek(ReservedKeywordType::DECLARE)) {
            lexer.consume(ReservedKeywordType::DECLARE);

            lexer.expect<Identifier>();

            std::string module_name = lexer.get<Identifier>();

            lexer.consume(ReservedKeywordType::LBRACE);

            auto iolists = parse_iolists();

            lexer.consume(ReservedKeywordType::RBRACE);

            Module module(module_name, true);
            module.ports.insert(iolists.begin(), iolists.end());

            nodes.push_back(std::make_shared<Node>(module));
        } else if (lexer.peek(ReservedKeywordType::EoF)) {
            break;
        } else {
            std::cout << "Error: unexpected token" << std::endl;
            assert(false);
        }
    }
    return nodes;
}

std::map<std::string, std::shared_ptr<Node>> Parser::parse_iolists() {
    std::map<std::string, std::shared_ptr<Node>> iolists;

    while (1) {
        if (lexer.peek(ReservedKeywordType::INPUT) ||
            lexer.peek(ReservedKeywordType::OUTPUT) ||
            lexer.peek(ReservedKeywordType::INOUT)) {
            bool is_input = false;
            bool is_output = false;
            bool is_inout = false;

            is_input = lexer.consume(ReservedKeywordType::INPUT);
            if (!is_input) {
                is_output = lexer.consume(ReservedKeywordType::OUTPUT);
                if (!is_output) {
                    is_inout = lexer.consume(ReservedKeywordType::INOUT);
                }
            }
            if (!is_input && !is_output && !is_inout) {
                std::cout << "Error: expected input, output, or inout"
                          << std::endl;
                assert(false);
            }

            lexer.expect<Identifier>();

            auto wire_name = lexer.get<Identifier>();

            u64 width = 1;
            if (lexer.peek(ReservedKeywordType::LBRACKET)) {
                lexer.consume(ReservedKeywordType::LBRACKET);

                lexer.expect<Number>();

                width = lexer.get<Number>();

                lexer.consume(ReservedKeywordType::RBRACKET);
                lexer.consume(ReservedKeywordType::SEMICOLON);
            }
            lexer.consume(ReservedKeywordType::SEMICOLON);

            if (is_input) {
                iolists.insert({wire_name, std::make_shared<Node>(
                                               Input(wire_name, width))});
            } else if (is_output) {
                iolists.insert({wire_name, std::make_shared<Node>(
                                               Output(wire_name, width))});
            } else if (is_inout) {
                iolists.insert({wire_name, std::make_shared<Node>(
                                               Inout(wire_name, width))});
            }
        } else {
            break;
        }
    }

    return iolists;
}
