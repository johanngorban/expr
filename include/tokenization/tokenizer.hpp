#pragma once

#include <string>
#include <vector>

#include "tokens.hpp"

class Tokenizer {
public:
    static std::vector<token_ptr> tokenize(const std::string &expression);
};

