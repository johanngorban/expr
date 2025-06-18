#pragma once

#include <vector>

#include "extended_tokens.hpp"

class ParseState;

using state_ptr = std::shared_ptr<ParseState>;

class ParserContext {
private:
    std::vector<token_ptr> extended_tokens;
    state_ptr current_state;
public:
    ParserContext();

    std::vector<token_ptr> get_extended_tokens() const noexcept;
    
    void handle_token(token_ptr token);
    
    void append_extended_token(token_ptr token) noexcept;
    
    void set_state(state_ptr new_state) noexcept;
};