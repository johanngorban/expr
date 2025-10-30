#include <stdexcept>
#include "parsing/states.hpp"
#include "token_manager.hpp"

void ParseStartState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();
    const std::string token_data = token->get_data();
    
    if (token_type == TokenType::Operator) {
        TokenManager token_manager;
        unsigned int precedance = token_manager.get_precedance(token->get_data(), Arity::Unary);
        token_ptr extended_token = std::make_shared<OperatorToken>(*token, precedance, Associativity::Right, Arity::Unary);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseUnaryOperatorState>();
    }
    else if (token_type == TokenType::Number) {
        token_ptr extended_token = std::make_shared<NumberToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseNumberState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else {
            throw std::runtime_error("Syntax error: right parenthesis cannot be in the beginning");
        }
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: separator cannot be in the beginning");
    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Empty expression given");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseNumberState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Number) {
        throw std::runtime_error("Syntax error: a number cannot follow after other numbers");
    }
    else if (token_type == TokenType::Operator) {
        TokenManager token_manager;
        unsigned int precedance = token_manager.get_precedance(token->get_data(), Arity::Binary);
        token_ptr extended_token = std::make_shared<OperatorToken>(*token, precedance, Associativity::Left, Arity::Binary);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseBinaryOperatorState>();
    }
    else if (token_type == TokenType::Separator) {
        token_ptr extended_token = std::make_shared<SeparatorToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseSeparatorState>();
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        const Token &multiplication_token = Token("*", TokenType::Operator);
        extended_token = std::make_shared<OperatorToken>(multiplication_token, 0, Associativity::Left, Arity::Binary);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            const Token &multiplication_token = Token("*", TokenType::Operator);
            token_ptr extended_token = std::make_shared<OperatorToken>(multiplication_token, 0, Associativity::Left, Arity::Binary);
            context.append_extended_token(extended_token);

            extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseRightParenthesisState>();
        }

    }
    else if (token_type == TokenType::End) {
        next_state = std::make_shared<ParseEndState>();
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseBinaryOperatorState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Number) {
        token_ptr extended_token = std::make_shared<NumberToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseNumberState>();
    }
    else if (token_type == TokenType::Operator) {
        throw std::runtime_error("Syntax error: operator cannot follow after operator");
    }
    else if (token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: separator cannot follow after operator");
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: left parenthesis cannot follow after operator");
        }
    
    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Syntax error: expression cannot end with binary operator");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseUnaryOperatorState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Number) {
        token_ptr extended_token = std::make_shared<NumberToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseNumberState>();
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: right parenthesis cannot follow after unary operator");
        }

    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Syntax error: unary operator cannot end the expression");
    }
    else if (token_type == TokenType::Operator || token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: operator or separator cannot follow after unary operator");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseFunctionState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: right parenthesis cannot follow after function");
        }

    }
    else if (token_type == TokenType::Operator || token_type == TokenType::Number || token_type == TokenType::Function || token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: only left parenthesis can follow after function");
    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Syntax error: expression cannot end with function name");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseSeparatorState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: separator cannot follow after separator");
    }
    else if (token_type == TokenType::Operator) {
        throw std::runtime_error("Syntax error: operator (unary/binary) cannot follow after separator");
    }
    else if (token_type == TokenType::Number) {
        token_ptr extended_token = std::make_shared<NumberToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseNumberState>();
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: right parenthesis cannot follow after separator");
        }

    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Syntax error: expression cannot end with separator");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseLeftParenthesisState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Separator) {
        throw std::runtime_error("Syntax error: separator cannot follow after left parenthesis");
    }
    else if (token_type == TokenType::Operator) {
        TokenManager token_manager;
        unsigned int precedance = token_manager.get_precedance(token->get_data(), Arity::Unary);

        token_ptr extended_token = std::make_shared<OperatorToken>(*token, precedance, Associativity::Right, Arity::Unary);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseUnaryOperatorState>();
    }
    else if (token_type == TokenType::Number) {
        token_ptr extended_token = std::make_shared<NumberToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseNumberState>();
    }
    else if (token_type == TokenType::Function) {
        token_ptr extended_token = std::make_shared<FunctionToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseFunctionState>();
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: right parenthesis cannot follow after separator");
        }

    }
    else if (token_type == TokenType::End) {
        throw std::runtime_error("Syntax error: expression cannot end with left parenthesis");
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseRightParenthesisState::handle_token(ParserContext& context, token_ptr token) {
    state_ptr next_state = std::make_shared<ParseEndState>();
    TokenType token_type = token->get_type();

    if (token_type == TokenType::Separator) {
        token_ptr extended_token = std::make_shared<SeparatorToken>(*token);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseSeparatorState>();
    }
    else if (token_type == TokenType::Operator) {
        TokenManager token_manager;
        unsigned int precedance = token_manager.get_precedance(token->get_data(), Arity::Binary);
        token_ptr extended_token = std::make_shared<OperatorToken>(*token, precedance, Associativity::Left, Arity::Binary);
        context.append_extended_token(extended_token);
        next_state = std::make_shared<ParseBinaryOperatorState>();
    }
    else if (token_type == TokenType::Number) {
        throw std::runtime_error("Syntax error: number cannot follow after separator");
    }
    else if (token_type == TokenType::Function) {
        throw std::runtime_error("Syntax error: function cannot follow after separator");
    }
    else if (token_type == TokenType::Parenthesis) {
        const std::string token_data = token->get_data();
        if (token_data == "LEFT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            const Token &multiplication_token = Token("*", TokenType::Operator);

            TokenManager token_manager;
            unsigned int precedance = token_manager.get_precedance("*", Arity::Binary);

            extended_token = std::make_shared<OperatorToken>(multiplication_token, precedance, Associativity::Left, Arity::Binary);
            context.append_extended_token(extended_token);

            next_state = std::make_shared<ParseLeftParenthesisState>();
        }
        else if (token_data == "RIGHT_PARENTHESIS") {
            token_ptr extended_token = std::make_shared<ParenthesisToken>(*token);
            context.append_extended_token(extended_token);
            next_state = std::make_shared<ParseRightParenthesisState>();
        }
    }
    else if (token_type == TokenType::End) {
        next_state = std::make_shared<ParseEndState>();
    }
    else {
        throw std::runtime_error("Syntax error: unknown token type");
    }
    context.set_state(next_state);
}

void ParseEndState::handle_token(ParserContext& context, token_ptr token) {}