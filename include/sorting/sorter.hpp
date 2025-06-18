#pragma once

#include "parsing/extended_tokens.hpp"

#include <vector>

class Sorter {
public:
    static std::vector<token_ptr> rpn_sort(const std::vector<token_ptr> &tokens);
};