#pragma once

#include "tokenization/tokens.hpp"

#include <vector>
#include <string>

class History {
private:
    std::vector<std::string> expressions;
    std::size_t current_index = 0;
public:
    void save(const std::string &expression) noexcept;

    bool empty() const noexcept;

    // Returns empty string if invalid index given
    const std::string get_prev();

    const std::string get_next();
};