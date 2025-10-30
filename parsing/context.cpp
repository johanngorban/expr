#include "parsing/context.hpp"
#include "parsing/states.hpp"

ParserContext::ParserContext() {
    this->current_state = std::make_shared<ParseStartState>();
}

void ParserContext::append_extended_token(token_ptr token) noexcept {
    this->extended_tokens.push_back(token);
}

void ParserContext::set_state(state_ptr new_state) noexcept {
    this->current_state = new_state;
}

void ParserContext::handle_token(token_ptr token) {
    this->current_state->handle_token(*this, token);
}

std::vector<token_ptr> ParserContext::get_extended_tokens() const noexcept {
    return this->extended_tokens;
}