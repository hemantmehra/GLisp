#include <Tokenizer.h>
#include <cctype>

namespace LISP {
    std::vector<Token*>* Tokenizer::get_tokens()
    {
        return &m_tokens;
    }
    
    void Tokenizer::tokenize(std::string s)
    {
        State state = State::Begin;
        auto it = s.begin();
        std::string tmp = "";
        while (it != s.end()) {
            if (*it = '(') {
                m_tokens.push_back(new Token(Token::Type::Open));
            }

            else if (*it = ')') {
                m_tokens.push_back(new Token(Token::Type::Close));
            }

            else if (isspace(*it) && tmp.length() != 0) {
                std::string s1(tmp);
                m_tokens.push_back(new Token(Token::Type::Symbol, &s1));
            }

            else if (isalpha(*it) && tmp.length() == 0) {
                tmp = "";
                tmp += *it;
            }

            else if (isalpha(*it)) {
                tmp += *it;
            }
            
            it++;
        }


        /*
        switch(state)
        {
        case Begin:
            {
                if (*it == '(') {
                    m_tokens.push_back(new Token(Token::Type::Open));
                    state = State::BeginList;
                    it++;
                    break;
                }
                assert(0);
            }
        
        case BeginList:
            {
                if (isalpha(*it)) {
                    state = State::BeginSymbol;
                }
                break;
            }
                
        }

        */
    }
}
