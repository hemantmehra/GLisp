#include <Tokenizer.h>
#include <cctype>
#include <iostream>

namespace LISP {
    std::string Token::to_string()
    {
        if (is_open()) {
            return "Token::Open";
        }

        else if (is_close()) {
            return "Token::Close";
        }

        else if (is_integer()) {
            return "Token::Int";
        }

        else if (is_symbol()) {
            return "Token::Sym::" + *as_symbol(); 
        }

        assert(0);
    }
    
    bool Tokenizer::is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    
    std::vector<Token>* Tokenizer::get_tokens()
    {
        return &m_tokens;
    }
    
    void Tokenizer::tokenize(std::string s)
    {
        auto it = s.begin();
        std::vector<std::string> str_vec;
        std::string tmp = "";
        while (it != s.end()) {
            if (*it == '(') {
                str_vec.push_back("(");
            }

            else if (*it == ')') {
                str_vec.push_back(tmp);
                tmp = "";
                str_vec.push_back(")");
            }

            else if (isspace(*it) && tmp.length() != 0) {
                str_vec.push_back(tmp);
                tmp = "";
            }

            else if (isspace(*it)) {}

            else {
                tmp += *it;
            }
            it++;
        }

        for(auto s: str_vec) {
            std::cout << "[0]" << s << std::endl;
            if (s == "(") {
                m_tokens.push_back(Token(Token::Type::Open));
            }

            else if (s == ")") {
                m_tokens.push_back(Token(Token::Type::Close));
            }

            else if (is_number(s)) {
                int num = stoi(s);
                m_tokens.push_back(Token(Token::Type::Integer, num));
            }

            else {
                m_tokens.push_back(Token(Token::Type::Symbol, &s));
                std::cout << "[1]" << s << std::endl;
                
            }
        }
    }
}
