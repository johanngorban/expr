#pragma once

#include <vector>
#include <string>

#include "states.hpp"
#include "tokens.hpp"
#include "token_manager.hpp"

class State;

using state_ptr = std::shared_ptr<State>;

class TokenizerContext {
private:
    TokenManager token_manager;
    std::vector<token_ptr> tokens;
    state_ptr start_state;
    std::string buffer;
public:
    TokenizerContext();
    
    std::vector<token_ptr> get_tokens() const noexcept;
    
    std::string get_buffer() const noexcept;

    const TokenManager &get_manager() const noexcept;
    
    void clear_buffer() noexcept;
    
    void handle_char(char c);
    
    void append_buffer(char c) noexcept;
    
    void append_token(token_ptr token) noexcept;
    
    void set_state(state_ptr new_state) noexcept;
};