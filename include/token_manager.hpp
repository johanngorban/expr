#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "parsing/extended_tokens.hpp"

class TokenManager {
private:
    std::vector<std::string> available_token_names;
    std::unordered_map<TokenType, std::string> tokentype_names;
    std::unordered_map<std::string, std::unordered_map<Arity, unsigned int>> precedance_table;
public:
    TokenManager();

    bool is_valid_name(const std::string &name) const noexcept;

    const std::string &get_type_name(TokenType) const;

    unsigned int get_precedance(const std::string &operator_name, Arity operator_arity) const;
};