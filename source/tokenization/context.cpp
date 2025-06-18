#include "tokenization/context.hpp"

TokenizerContext::TokenizerContext() : token_manager() {
    this->start_state = std::make_shared<StartState>();
}

void TokenizerContext::append_token(token_ptr token) noexcept {
    this->tokens.push_back(token);
}

void TokenizerContext::set_state(state_ptr new_state) noexcept {
    this->start_state = new_state;
}

void TokenizerContext::clear_buffer() noexcept {
    this->buffer.clear();
}

void TokenizerContext::append_buffer(char c) noexcept {
    this->buffer.push_back(c);
}

void TokenizerContext::handle_char(char c) {
    this->start_state->handle_char(*this, c);
}

const TokenManager &TokenizerContext::get_manager() const noexcept {
    return this->token_manager;
}

std::string TokenizerContext::get_buffer() const noexcept {
    return this->buffer;
}

std::vector<token_ptr> TokenizerContext::get_tokens() const noexcept {
    return this->tokens;
}