#pragma once

#include "parsing/extended_tokens.hpp"
#include "context.hpp"

#include <vector>
#include <stack>
#include <memory>

class SortCommand;

typedef std::shared_ptr<SortCommand> sort_command_ptr;

class SortCommand {
public:
    virtual void execute(SortContext &context) = 0;
    virtual ~SortCommand() = default;
};


class SortOperatorCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortNumberCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortFunctionCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortSeparatorCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortLeftParenthesisCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortRightParenthesisCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};


class SortEndCommand : public SortCommand {
public:
    void execute(SortContext &context) override;
};