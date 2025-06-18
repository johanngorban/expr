#pragma once

#include "commands.hpp"

#include <unordered_map>
#include <string>

class SortCommandManager {
private:
    std::unordered_map<TokenType, sort_command_ptr> commands;
    std::unordered_map<std::string, sort_command_ptr> parenthesis_command;
public:
    SortCommandManager();

    const sort_command_ptr get_command(const token_ptr &token) const;
};