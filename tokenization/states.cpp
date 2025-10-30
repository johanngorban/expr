#include "tokenization/states.hpp"
#include "tokenization/context.hpp"
#include "tokenization/tokens.hpp"
#include "tokenization/state_factory.hpp"

#include "token_manager.hpp"

#include <memory>
#include <algorithm>
#include <stdexcept>


void State::emit_token_from_buffer(TokenizerContext &context) {
    // Nothing here
}

//////////////////////////////////////////////////////////////////////////////////////////

void StartState::handle_char(TokenizerContext &context, char c) {
    context.append_buffer(c);

    static StateFactory state_factory;
    state_ptr new_state = state_factory.create(c);

    context.set_state(new_state);
}

void StartState::emit_token_from_buffer(TokenizerContext &context) {

}

//////////////////////////////////////////////////////////////////////////////////////////

void NumberState::handle_char(TokenizerContext &context, char c) {
    state_ptr new_state = std::make_shared<NumberState>();

    if (std::isdigit(c)) {
        context.append_buffer(c);
    }

    else if (c == '.') {
        auto current_buffer = context.get_buffer();
        
        // Need to check how much floating points are in the number
        // If there is a point and now there is a new point, it is lexical error

        if (std::count(current_buffer.begin(), current_buffer.end(), '.') != 0) {
            throw std::runtime_error("Lexical error: invalid float number format");
        }
        else {
            context.append_buffer(c);
        }
    }
    
    else {
        // Create token after the state changed
        this->emit_token_from_buffer(context);
        context.append_buffer(c);

        static StateFactory state_factory;
        new_state = state_factory.create(c);
    }
    context.set_state(new_state);
}

void NumberState::emit_token_from_buffer(TokenizerContext &context) {
    // Get buffer that stores number
    auto current_buffer = context.get_buffer();
    
    // Create new number token
    auto number_token = std::make_shared<Token>(current_buffer, TokenType::Number);

    // Append the created token to context
    context.append_token(number_token);

    context.clear_buffer();
}

//////////////////////////////////////////////////////////////////////////////////////////

void OperatorState::handle_char(TokenizerContext &context, char c) {
    state_ptr new_state = std::make_shared<OperatorState>();
    TokenManager token_manager = context.get_manager();

    if (token_manager.is_valid_name(std::string(1, c))) {
        new_state = std::make_shared<OperatorState>();
        context.append_buffer(c);
    }
    else {
        this->emit_token_from_buffer(context);
        context.append_buffer(c);
        static StateFactory state_factory;
        new_state = state_factory.create(c);
    }

    context.set_state(new_state);
}

void OperatorState::emit_token_from_buffer(TokenizerContext &context) {
    // Get buffer that stores operator
    auto current_buffer = context.get_buffer();

    // Create token manager to define operator we got
    auto token_manager = context.get_manager();

    if (!token_manager.is_valid_name(current_buffer)) {
        throw std::runtime_error("Lexical error: no operators with such syntax: " + current_buffer);
    }
    else {
        if (token_manager.is_valid_name(current_buffer)) {
            context.append_token(std::make_shared<Token>(current_buffer, TokenType::Operator));
            context.clear_buffer();
        }
        else {
            throw std::runtime_error("Lexical error: unknown operator");
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

void IdentifierState::handle_char(TokenizerContext &context, char c) {
    state_ptr new_state = std::make_shared<IdentifierState>();

    if (std::isalpha(c)) {
        context.append_buffer(c);
    }
    else if (std::isdigit(c)) {
        std::string current_buffer = context.get_buffer();
        if (!current_buffer.empty() && std::isalpha(current_buffer[0])) {
            context.append_buffer(c);
        }
        else {
            throw std::runtime_error("Lexical error: function name cannot start with digit");
        }
    }
    else {
        this->emit_token_from_buffer(context);
        context.append_buffer(c);

        static StateFactory state_factory;
        new_state = state_factory.create(c);
    }
    
    context.set_state(new_state);
}

void IdentifierState::emit_token_from_buffer(TokenizerContext &context) {
    std::string current_buffer = context.get_buffer();

    TokenManager token_manager = context.get_manager();

    if (token_manager.is_valid_name(current_buffer)) {
        context.append_token(std::make_shared<Token>(current_buffer, TokenType::Function));
        context.clear_buffer();
    }
    else {
        throw std::runtime_error("No such function available: " + current_buffer);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

void ParanthesisState::handle_char(TokenizerContext &context, char c) {
    state_ptr new_state = std::make_shared<ParanthesisState>();
    
    this->emit_token_from_buffer(context);
    context.append_buffer(c);

    static StateFactory state_factory;
    new_state = state_factory.create(c);

    context.set_state(new_state);
}

void ParanthesisState::emit_token_from_buffer(TokenizerContext &context) {
    std::string current_buffer = context.get_buffer();

    if (current_buffer == "(") {
        context.append_token(std::make_shared<Token>("LEFT_PARENTHESIS", TokenType::Parenthesis));
        context.clear_buffer();
    }
    else if (current_buffer == ")") {
        context.append_token(std::make_shared<Token>("RIGHT_PARENTHESIS", TokenType::Parenthesis));
        context.clear_buffer();
    }
    else {
        throw std::runtime_error("Lexical error: no such paranthesis");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

void SeparatorState::handle_char(TokenizerContext &context, char c) {
    state_ptr new_state = std::make_shared<SeparatorState>();
    
    this->emit_token_from_buffer(context);
    context.append_buffer(c);

    static StateFactory state_factory;
    new_state = state_factory.create(c);

    context.set_state(new_state);
}

void SeparatorState::emit_token_from_buffer(TokenizerContext &context) {
    std::string current_buffer = context.get_buffer();

    if (current_buffer != ",") {
        throw std::runtime_error("Lexical error: no such separator: " + current_buffer); 
    }
    else {
        context.append_token(std::make_shared<Token>("", TokenType::Separator));
        context.clear_buffer();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

void EndState::handle_char(TokenizerContext &context, char c) {
    this->emit_token_from_buffer(context);
    context.set_state(std::make_shared<StartState>());
}

void EndState::emit_token_from_buffer(TokenizerContext &context) {
    context.append_token(std::make_shared<Token>("", TokenType::End));
    context.clear_buffer();
}

//////////////////////////////////////////////////////////////////////////////////////////