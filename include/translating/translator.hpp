#pragma once

#include <vector>

#include "parsing/extended_tokens.hpp"
#include "command_manager.hpp"
#include "commands.hpp"


class Translator {
public:
    static const std::vector<command_ptr> translate_tokens(std::vector<token_ptr> &tokens);
};