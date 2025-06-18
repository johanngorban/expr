#pragma once

#include "tokenization/tokens.hpp"
#include <stack>
#include <vector>

class SortContext {
private:
    std::stack<token_ptr> _stack;
    std::vector<token_ptr> _result;
    token_ptr _current_token;
public:
    SortContext(std::stack<token_ptr> &stack, std::vector<token_ptr> &result);

    token_ptr get_current_token() const;

    void pop_stack();

    token_ptr top_stack() const;

    void push_stack(token_ptr token);

    bool stack_empty() const;

    void set_current_token(token_ptr token);

    void add_to_result(token_ptr token);

    std::vector<token_ptr> get_result() const;
};