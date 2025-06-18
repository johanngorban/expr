#include "sorting/sorter.hpp"
#include "sorting/command_manager.hpp"
#include "sorting/context.hpp"

#include <stack>
#include <stdexcept>

std::vector<token_ptr> Sorter::rpn_sort(const std::vector<token_ptr> &tokens) {
    // "Stack" for storing tokens in reverse polnish notation order
    std::vector<token_ptr> result;

    // Stack for intermediate computations
    std::stack<token_ptr> token_stack;

    SortContext context = SortContext(token_stack, result);

    static SortCommandManager command_manager;
    for (const auto& token : tokens) {
        context.set_current_token(token);
        auto command = command_manager.get_command(token);
        command->execute(context);
    }

    sort_command_ptr end_command = std::make_shared<SortEndCommand>();
    context.set_current_token(nullptr);
    end_command->execute(context);

    return context.get_result();
}   