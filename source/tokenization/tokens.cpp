#include "tokenization/tokens.hpp"

Token::Token(const std::string &name, const TokenType &type) noexcept : data(name), type(type) {

}

const std::string &Token::get_data() const noexcept {
    return this->data;
}

const TokenType Token::get_type() const noexcept {
    return this->type;
}