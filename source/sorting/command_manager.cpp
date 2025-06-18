#include "sorting/command_manager.hpp"

#include <stdexcept>

SortCommandManager::SortCommandManager() {
    this->commands[TokenType::Number] = std::make_shared<SortNumberCommand>();
    this->commands[TokenType::Operator] = std::make_shared<SortOperatorCommand>();
    this->commands[TokenType::Function] = std::make_shared<SortFunctionCommand>();
    this->commands[TokenType::Separator] = std::make_shared<SortSeparatorCommand>();

    this->parenthesis_command["LEFT_PARENTHESIS"] = std::make_shared<SortLeftParenthesisCommand>();
    this->parenthesis_command["RIGHT_PARENTHESIS"] = std::make_shared<SortRightParenthesisCommand>();
}

const sort_command_ptr SortCommandManager::get_command(const token_ptr &token) const {
    sort_command_ptr command(nullptr);

    if (!token) {
        throw std::runtime_error("Sort error: null token was given");
    }

    TokenType token_type = token->get_type();
    if (token_type == TokenType::Parenthesis) {
        std::string parenthesis_type = token->get_data();
        if (this->parenthesis_command.count(parenthesis_type)) {
            command = parenthesis_command.at(parenthesis_type);
        }
        else {
            throw std::runtime_error("Sort error: command for token not found");
        }
    }
    else if (this->commands.count(token_type)) {
        command = this->commands.at(token_type);
    }
    else {
            throw std::runtime_error("Sort error: command for token not found");
    }
    
    return command;
}