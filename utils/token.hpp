#pragma once

namespace OperatorTraits {
    constexpr unsigned int precedence(std::string_view op, Arity arity) noexcept;
    constexpr Associativity associativity(std::string_view op) noexcept;
    constexpr bool is_valid(std::string_view op) noexcept;
}
