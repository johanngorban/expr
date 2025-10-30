#include "sorting/commands.hpp"

#include <stdexcept>

void SortOperatorCommand::execute(SortContext &context) {
    token_ptr token = context.get_current_token();
    if (token->get_type() != TokenType::Operator) {
        throw std::runtime_error("SortOperatorCommand: token is not an operator");
    }

    auto op1 = std::static_pointer_cast<OperatorToken>(token);

    while (!context.stack_empty()) {
        token_ptr top_token = context.top_stack();

        if (top_token->get_type() != TokenType::Operator) {
            break;
        }

        auto op2 = std::static_pointer_cast<OperatorToken>(top_token);

        bool higher_precedence = op2->get_precedance() > op1->get_precedance();
        bool equal_precedence_left_associative =
            op2->get_precedance() == op1->get_precedance() &&
            op1->get_associativity() == Associativity::Left;

        if (higher_precedence || equal_precedence_left_associative) {
            context.add_to_result(op2);
            context.pop_stack();
        } else {
            break;
        }
    }

    context.push_stack(token);
}


void SortNumberCommand::execute(SortContext &context) {
    token_ptr token = context.get_current_token();
    context.add_to_result(token);
}


void SortFunctionCommand::execute(SortContext &context) {
    token_ptr token = context.get_current_token();
    context.push_stack(token);
}


void SortSeparatorCommand::execute(SortContext &context) {
    while (!context.stack_empty()) {
        token_ptr token_in_stack = context.top_stack();

        if (token_in_stack->get_data() == "LEFT_PARENTHESIS") {
            break;
        }

        context.add_to_result(token_in_stack);
        context.pop_stack();
    }

    if (context.stack_empty()) {
        throw std::runtime_error("Syntax error: missing parenthesis or function argument separator");
    }
}


void SortLeftParenthesisCommand::execute(SortContext &context) {
    token_ptr token = context.get_current_token();
    context.push_stack(token);
}


void SortRightParenthesisCommand::execute(SortContext &context) {
    while (!context.stack_empty()) {
        token_ptr token_in_stack = context.top_stack();

        if (token_in_stack->get_data() == "LEFT_PARENTHESIS") {
            break;
        }
        
        context.add_to_result(token_in_stack);
        context.pop_stack();
    }

    if (context.stack_empty()) {
        throw std::runtime_error("Syntax error: missing left parenthesis");
    }

    context.pop_stack();

    if (!context.stack_empty()) {
        token_ptr top_token = context.top_stack();
        if (top_token->get_type() == TokenType::Function) {
            context.add_to_result(top_token);
            context.pop_stack();
        }
    }
}


void SortEndCommand::execute(SortContext &context) {
    while (!context.stack_empty()) {
        token_ptr top_token = context.top_stack();

        if (top_token->get_data() == "LEFT_PARENTHESIS") {
            throw std::runtime_error("Syntax error: missing right parenthesis");
        }

        context.add_to_result(top_token);
        context.pop_stack();
    }
}