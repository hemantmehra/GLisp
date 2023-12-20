#include <utility>
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
        std::shared_ptr<Cons> two_pointer = MAKE_NODE0();
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
                while(stack.size() != 0) {
                    std::shared_ptr<Cons> tmp = stack.back();
                    two_pointer->set_car(tmp);
                    tmp->set_cdr(curr_obj);
                    stack.pop_back();
                }
                break;
            }

            case Token::Type::Symbol:
            {
                auto symbol_obj = OBJECT_PTR_CAST(MAKE_SYMBOL(curr_token.as_symbol_value()));
                auto node = MAKE_NODE1(symbol_obj);
                curr_obj->set_cdr(OBJECT_PTR_CAST(node));
                if (two_pointer->as_car()->is_nil()) {
                    two_pointer->set_car(OBJECT_PTR_CAST(node));
                }
                two_pointer->set_cdr(OBJECT_PTR_CAST(node));
                curr_obj = node;
                break;
            }

            case Token::Type::Scaler:
            {
                auto scaler_obj = OBJECT_PTR_CAST(MAKE_SCALER(curr_token.as_scaler_value()));
                auto node = MAKE_NODE1(scaler_obj);
                curr_obj->set_cdr(OBJECT_PTR_CAST(node));
                if (two_pointer->as_car()->is_nil()) {
                    two_pointer->set_car(OBJECT_PTR_CAST(node));
                }
                two_pointer->set_cdr(OBJECT_PTR_CAST(node));
                curr_obj = node;
                break;
            }
            
            default:
                break;
            }

        }

        return MAKE_NODE0();
    }
}
