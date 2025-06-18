#include "translating/commands.hpp"

#include <stdexcept>
#include <cmath>


NumberCommand::NumberCommand(const token_ptr& token) : token(token) {}

void NumberCommand::execute(std::stack<double>& computation_stack) {
    double number_data = std::stod(token->get_data());
    computation_stack.push(number_data);
}

AdditionCommand::AdditionCommand() {}

void AdditionCommand::execute(std::stack<double>& computation_stack) {
    double b = computation_stack.top();
    computation_stack.pop();
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(a + b);
}

SubstractCommand::SubstractCommand() {}

void SubstractCommand::execute(std::stack<double>& computation_stack) {
    double b = computation_stack.top();
    computation_stack.pop();
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(a - b);
}

MultiplyCommand::MultiplyCommand() {}

void MultiplyCommand::execute(std::stack<double>& computation_stack) {
    double b = computation_stack.top();
    computation_stack.pop();
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(a * b);
}

DivisionCommand::DivisionCommand() {}

void DivisionCommand::execute(std::stack<double>& computation_stack) {
    double b = computation_stack.top();
    computation_stack.pop();
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(a / b);
}

PowerCommand::PowerCommand() {}

void PowerCommand::execute(std::stack<double>& computation_stack) {
    double b = computation_stack.top();
    computation_stack.pop();
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(std::pow(a, b));
}

MinusCommand::MinusCommand() {}

void MinusCommand::execute(std::stack<double>& computation_stack) {
    double neg_a = -1 * computation_stack.top();
    computation_stack.pop();
    computation_stack.push(neg_a);
}

void SinCommand::execute(std::stack<double>& computation_stack) {
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(sin(a));
}

void CosCommand::execute(std::stack<double>& computation_stack) {
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(cos(a));
}

void TanCommand::execute(std::stack<double>& computation_stack) {
    double a = computation_stack.top();
    computation_stack.pop();
    computation_stack.push(tan(a));
}