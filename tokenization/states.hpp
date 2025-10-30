#pragma once

#include <memory>

#include "context.hpp"

class TokenizerContext;

class State {
public:
    virtual void handle_char(TokenizerContext &context, char c) = 0;

    virtual void emit_token_from_buffer(TokenizerContext &context) = 0;

    virtual ~State() = default;
};


class StartState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class NumberState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class IdentifierState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class OperatorState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class ParanthesisState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class SeparatorState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};


class EndState : public State {
public:
    void handle_char(TokenizerContext &context, char c) override;

    void emit_token_from_buffer(TokenizerContext &context) override;
};