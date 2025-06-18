#pragma once

#include <stack>

#include "parsing/extended_tokens.hpp"

class Command;

typedef std::shared_ptr<Command> command_ptr;

class Command {
public:
    virtual void execute(std::stack<double> &computation_stack) = 0;
    
    virtual ~Command() = default;
};

class NumberCommand : public Command {
private:
    const token_ptr token;
public:
    explicit NumberCommand(const token_ptr &token);

    NumberCommand() = delete; 

    void execute(std::stack<double> &computation_stack) override;
};

class AdditionCommand : public Command {
public:
    AdditionCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class SubstractCommand : public Command {
public:
    SubstractCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class MultiplyCommand : public Command {
public:
    MultiplyCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class DivisionCommand : public Command {
public:
    DivisionCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class PowerCommand : public Command {
public:
    PowerCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class MinusCommand : public Command {
public:
    MinusCommand();
    void execute(std::stack<double> &computation_stack) override;
};

class SinCommand : public Command {
public: 
    void execute(std::stack<double> &computation_stack) override;
};

class CosCommand : public Command {
public: 
    void execute(std::stack<double> &computation_stack) override;
};

class TanCommand : public Command {
public: 
    void execute(std::stack<double> &computation_stack) override;
};