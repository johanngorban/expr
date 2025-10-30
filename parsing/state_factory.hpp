#pragma once

#include "states.hpp"

class ParsingStateFactory {
public:
    virtual parse_state_ptr create(const token_ptr &token) = 0; 
};