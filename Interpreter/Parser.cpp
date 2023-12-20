#include <Interpreter/Parser.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>

#define OBJECT_PTR_CAST(x) std::static_pointer_cast<Object>(x)
#define CONS_PTR_CAST(x) std::dynamic_pointer_cast<Cons>(x)
#define MAKE_NODE0() std::make_shared<Cons>()
#define MAKE_NODE1(x) std::make_shared<Cons>(x)
#define MAKE_NODE2(x, y) std::make_shared<Cons>(x, y)
#define NODE_CAR(x) std::dynamic_pointer_cast<Cons>(x)->as_car()
#define NODE_CDR(x) std::dynamic_pointer_cast<Cons>(x)->as_cdr()

#define SET_NODE_CAR(x, y) std::dynamic_pointer_cast<Cons>(x)->set_car(y)
#define SET_NODE_CDR(x, y) std::dynamic_pointer_cast<Cons>(x)->set_cdr(y)

#define MAKE_SCALER(x) std::make_shared<Scaler>(x)
#define MAKE_SYMBOL(x) std::make_shared<Symbol>(x)

namespace LISP {
    std::shared_ptr<Object> Parser::parse(std::vector<Token> tokens)
    {
        std::shared_ptr<Cons> start = MAKE_NODE0();
        std::shared_ptr<Cons> curr_obj = start;
        std::vector<std::shared_ptr<Cons>> stack;

        for (auto curr_token: tokens)
        {
            switch (curr_token.type())
            {
            case Token::Type::LP:
            {
                stack.push_back(curr_obj);
                break;
            }

            case Token::Type::RP:
            {
                break;
            }

            case Token::Type::Symbol:
            {
                break;
            }

            case Token::Type::Scaler:
            {
                break;
            }
            
            default:
                break;
            }

        }

        return MAKE_NODE0();
    }
}
