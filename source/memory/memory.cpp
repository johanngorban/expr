#include "memory/memory.hpp"

void Memory::add(double value) noexcept {
    this->value += value;
}

void Memory::substract(double value) noexcept {
    this->value -= value;
}

void Memory::clear() noexcept {
    this->value = 0;
}

double Memory::get_value() const noexcept {
    return this->value;
}