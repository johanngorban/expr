#include "parsing/extended_tokens.hpp"

// OperatorToken
OperatorToken::OperatorToken(
    const Token& token,
    unsigned int precedance,
    Associativity associativity,
    Arity arity
) : Token(token),
    precedance(precedance),
    associativity(associativity),
    arity(arity)
{}

Arity OperatorToken::get_arity() const noexcept {
    return this->arity;
}

unsigned int OperatorToken::get_precedance() const noexcept {
    return this->precedance;
}

Associativity OperatorToken::get_associativity() const noexcept {
    return this->associativity;
}

// FunctionToken
FunctionToken::FunctionToken(const Token& token) noexcept : Token(token) {

}

// NumberToken
NumberToken::NumberToken(const Token& token) noexcept : Token(token) {

}

// ParenthesisToken
ParenthesisToken::ParenthesisToken(const Token& token) noexcept : Token(token) {

}

// SeparatorToken
SeparatorToken::SeparatorToken(const Token& token) noexcept : Token(token) {

}