#pragma once

#include "context.hpp"

class ParseState;
class ParseParserContext;

using parse_state_ptr = std::shared_ptr<ParseState>;

class ParseState {
public:
    virtual void handle_token(ParserContext &context, token_ptr token) = 0;

    virtual ~ParseState() = default;
};


class ParseStartState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseNumberState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseBinaryOperatorState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseUnaryOperatorState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseFunctionState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseSeparatorState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseLeftParenthesisState : public ParseState {
public:
    void handle_token(ParserContext &context, token_ptr token) override;
};


class ParseRightParenthesisState : public ParseState {
    public:
        void handle_token(ParserContext &context, token_ptr token) override;
    };
    


class ParseEndState : public ParseState {
public:
    void handle_token(ParserContext& context, token_ptr token) override;
};