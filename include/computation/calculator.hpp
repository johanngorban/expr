#pragma once

#include <vector>
#include <memory>

#include "translating/translator.hpp"


class Calculator {
public:
    static double calculate(const std::vector<command_ptr> &commands);
};