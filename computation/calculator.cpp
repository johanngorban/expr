#include "computation/calculator.hpp"
#include "translating/translator.hpp"

#include <stack>
#include <stdexcept>

double Calculator::calculate(const std::vector<command_ptr> &commands){
    // Stack for computation. There the intermediate calculations are being stored
    std::stack<double> computations;
    
    for (const auto &command : commands) {
        command->execute(computations);
    } 
    
    if (computations.empty()) {
        throw std::runtime_error("Empty expression");
    }
    else {
        return computations.top();
    }
}