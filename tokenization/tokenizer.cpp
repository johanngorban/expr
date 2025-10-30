#include "tokenization/tokenizer.hpp"
#include "tokenization/context.hpp"

std::vector<token_ptr> Tokenizer::tokenize(const std::string &expression) {
    TokenizerContext context;

    for (auto c : expression) {
        context.handle_char(c);
    }
    
    // Process to end the expression parsing
    context.handle_char('\0');
    context.handle_char('\0');

    return context.get_tokens();
}