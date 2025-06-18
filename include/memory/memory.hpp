#pragma once

class Memory {
private:
    double value;
public:
    void clear() noexcept;

    void add(double value) noexcept;

    void substract(double value) noexcept;
    
    double get_value() const noexcept;
};