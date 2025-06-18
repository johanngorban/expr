#pragma once

#include <vector>

#include "tokenization/tokens.hpp"

class Parser {
public:
    static std::vector<token_ptr> parse(const std::vector<token_ptr> &tokens);
};