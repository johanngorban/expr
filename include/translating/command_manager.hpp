#pragma once

#include "commands.hpp"
#include "parsing/extended_tokens.hpp"

#include <unordered_map>
#include <memory>

 

class CommandManager {
private:
    std::unordered_map<std::string, command_ptr> functions;
    std::unordered_map<std::string, command_ptr> unary_operators;
    std::unordered_map<std::string, command_ptr> binary_operators;
public:
    CommandManager();

    const command_ptr get_command(const token_ptr &token) const;

    bool function_has_command(const std::string &token_name) const;

    bool binary_operator_has_command(const std::string &token_name) const;

    bool unary_operator_has_command(const std::string &token_name) const;
};