#include <Interpreter/Tokenizer.h>

namespace LISP {
    Token::Token(Type type) : m_type(type) {}

    std::vector<std::string> Tokenizer::split_to_words(std::string code)
    {
        std::vector<std::string> words;
        std::string current_word = "";

        auto it = code.begin();
        while (it != code.end())
        {
            if (std::isspace(*it) && current_word.length() != 0) {
                words.push_back(current_word);
                current_word = "";
            }

            else if (*it == '(') {
                if (current_word.length() > 0) words.push_back(current_word);
                words.push_back("(");
                current_word = "";
            }

            else if (*it == ')') {
                if (current_word.length() > 0) words.push_back(current_word);
                words.push_back(")");
                current_word = "";
            }

            else if (std::isspace(*it)) {}

            else {
                current_word += *it;
            }

            it++;
        }

        if (current_word.length() > 0)
            words.push_back(current_word);

        return words;
    }

    bool Tokenizer::is_number(const std::string s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    std::vector<Token> Tokenizer::tokenize(std::string code)
    {
        std::vector<Token> tokens;
        std::vector<std::string> words = split_to_words(code);

        for(auto it: words) {
            if (it == "(") {
                tokens.push_back(Token(Token::Type::LP));
            }

            else if (it == ")") {
                tokens.push_back(Token(Token::Type::RP));
            }

            else if (is_number(it)) {
                tokens.push_back(Token(Token::Type::Scaler));
            }

            else {
                tokens.push_back(Token(Token::Type::Symbol));
            }
        }

        return tokens;
    }
}
