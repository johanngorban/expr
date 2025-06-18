#include "tokenization/state_factory.hpp"

StateFactory::StateFactory() {}

state_ptr StateFactory::create(char c) {
    state_ptr new_state;

    static TokenManager token_manager;
    if (token_manager.is_valid_name(std::string(1, c))) {
        new_state = std::make_shared<OperatorState>();
    }
    else if (std::isdigit(c) || c == '.') {
        new_state = std::make_shared<NumberState>();
    }
    else if (std::isalpha(c)) {
        new_state = std::make_shared<IdentifierState>();
    }
    else if (c == ')' || c == '(') {
        new_state = std::make_shared<ParanthesisState>();
    }
    else if (c == ',') {
        new_state = std::make_shared<SeparatorState>();
    }
    else if (c == '\0') {
        new_state = std::make_shared<EndState>();
    }

    return new_state;
}