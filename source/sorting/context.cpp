#include "sorting/context.hpp"

SortContext::SortContext(std::stack<token_ptr> &stack, std::vector<token_ptr> &result) : _stack(stack), _result(result) {
}

token_ptr SortContext::get_current_token() const {
    return this->_current_token;
}

void SortContext::set_current_token(token_ptr token) {
    this->_current_token = token;
}

void SortContext::push_stack(token_ptr token) {
    this->_stack.push(token);
}

void SortContext::add_to_result(token_ptr token) {
    this->_result.push_back(token);
}

bool SortContext::stack_empty() const {
    return this->_stack.empty();
}

std::vector<token_ptr> SortContext::get_result() const {
    return this->_result;
}

token_ptr SortContext::top_stack() const {
    return this->_stack.top();
}

void SortContext::pop_stack() {
    this->_stack.pop();
}