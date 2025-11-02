#include "expr.hpp"

#include "sorting/sorter.hpp"
#include "translating/translator.hpp"
#include "computation/calculator.hpp"
#include "tokenization/tokenizer.hpp"
#include "parsing/parser.hpp"
#include "parsing/extended_tokens.hpp"

const std::string expr::calculate(const std::string &expression) noexcept {
    std::string result;

    try {
        std::vector<token_ptr> tokens = Tokenizer::tokenize(expression);
        std::vector<token_ptr> extended_tokens = Parser::parse(tokens);
        std::vector<token_ptr> sorted_tokens = Sorter::rpn_sort(extended_tokens);
        std::vector<command_ptr> commands = Translator::translate_tokens(sorted_tokens);

        result = std::to_string(Calculator::calculate(commands));
    }
    catch (std::exception &error) {
        result = error.what();
    }
    
    return result;
}