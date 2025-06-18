#include "token_manager.hpp"

#include <stdexcept>
#include <algorithm>

TokenManager::TokenManager() {
    // Token types for debugging
    this->tokentype_names[TokenType::Number] = "NUMBER";
    this->tokentype_names[TokenType::Function] = "FUNCTION";
    this->tokentype_names[TokenType::Operator] = "OPERATOR";
    this->tokentype_names[TokenType::Parenthesis] = "PARENTHESIS";
    this->tokentype_names[TokenType::Separator] = "SEPARATOR";

    // Precedance table (for operators)
    this->precedance_table["+"][Arity::Binary] = 1;
    this->precedance_table["-"][Arity::Binary] = 1;
    this->precedance_table["-"][Arity::Unary] = 3;
    this->precedance_table["*"][Arity::Binary] = 2;
    this->precedance_table["/"][Arity::Binary] = 2;
    this->precedance_table["^"][Arity::Binary] = 4;

    this->available_token_names.push_back("-");
    this->available_token_names.push_back("+");
    this->available_token_names.push_back("*");
    this->available_token_names.push_back("/");
    this->available_token_names.push_back("^");

    this->available_token_names.push_back("sin");
    this->available_token_names.push_back("cos");
    this->available_token_names.push_back("tan");
}

bool TokenManager::is_valid_name(const std::string &name) const noexcept {
    bool exists = (std::find(
        this->available_token_names.begin(),
        this->available_token_names.end(),
        name
    ) != this->available_token_names.end());

    return exists;
}

const std::string &TokenManager::get_type_name(TokenType type) const {
    if (this->tokentype_names.count(type) != 0) {
        return this->tokentype_names.at(type);
    }
    else {
        throw std::runtime_error("Token type error: no tokens type with such index");
    }
}

unsigned int TokenManager::get_precedance(const std::string& operator_name, Arity operator_arity) const {
    if (!this->precedance_table.count(operator_name)) {
        throw std::runtime_error("Token error: token has no precedance");
    }

    const auto& operator_table = this->precedance_table.at(operator_name);
    if (!operator_table.count(operator_arity)) {
        throw std::runtime_error("Token error: token has no precedance for given arity");
    }
    return operator_table.at(operator_arity);
}