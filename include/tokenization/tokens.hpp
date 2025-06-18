#pragma once

#include <memory>
#include <string>

// Possible types of token
enum class TokenType {
    Operator,
    Function,
    Number,
    Parenthesis,
    Separator,
    End
};

class Token;

using token_ptr = std::shared_ptr<Token>;

class Token {
private:
    const std::string data;
    const TokenType type;
public:
    explicit Token(const std::string &name, const TokenType &type) noexcept;

    const std::string &get_data() const noexcept;

    const TokenType get_type() const noexcept;

    virtual ~Token() = default;
};