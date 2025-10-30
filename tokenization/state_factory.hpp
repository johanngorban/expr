#pragma once

#include <unordered_map>

#include "tokens.hpp"
#include "token_manager.hpp"
#include "states.hpp"


class StateFactory {
private:
    std::unordered_map<char, state_ptr> states;
public:
    StateFactory();
    
    state_ptr create(char c);
};