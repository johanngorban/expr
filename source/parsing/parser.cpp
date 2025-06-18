#include "parsing/parser.hpp"
#include "parsing/context.hpp"

#include <iostream>

std::vector<token_ptr> Parser::parse(const std::vector<token_ptr> &tokens) {
    ParserContext context;

    for (const auto &token : tokens) {
        context.handle_token(token);
    }

    return context.get_extended_tokens();
}