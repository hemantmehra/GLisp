#include <iostream>
#include <Interpreter/Assertion.h>
#include <Interpreter/Parser.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>

// #define TOKENIZER_DEBUG

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
    void append_using_two_pointer(std::shared_ptr<Cons> two_pointer, std::shared_ptr<Cons> cons_ptr)
    {
        if (two_pointer->as_car()->is_nil() && two_pointer->as_cdr()->is_nil())
        {
#ifdef TOKENIZER_DEBUG
            // std::cout << "two pointer is empty" << '\n';
#endif
            two_pointer->set_car(cons_ptr);
            two_pointer->set_cdr(cons_ptr);
        }

        else
        {
            CHECK(!two_pointer->as_car()->is_nil());
            CHECK(!two_pointer->as_cdr()->is_nil());

            CONS_PTR_CAST(two_pointer->as_cdr())->set_cdr(cons_ptr);
            two_pointer->set_cdr(OBJECT_PTR_CAST(cons_ptr));
        }
    }

    void level_concat_using_two_pointer(std::shared_ptr<Cons> ptr1, std::shared_ptr<Cons> ptr2)
    {
        // CHECK(!ptr1->as_car()->is_nil());
        // CHECK(!ptr2->as_cdr()->is_nil());
        if (ptr1->as_car()->is_nil() && ptr1->as_cdr()->is_nil())
        {
            ptr1->set_car(ptr2->as_car());
            ptr1->set_cdr(ptr2->as_cdr());
            return;
        }

        std::shared_ptr<Cons> tmp_node = MAKE_NODE0();
        tmp_node->set_car(ptr2->as_car());
        CONS_PTR_CAST(ptr1->as_cdr())->set_cdr(tmp_node);
        ptr1->set_cdr(OBJECT_PTR_CAST(tmp_node));
    }

    std::shared_ptr<Object> Parser::parse(std::vector<Token> tokens)
    {
        std::shared_ptr<Cons> two_pointer = MAKE_NODE0();
        std::vector<std::shared_ptr<Cons>> stack;

        for (auto curr_token: tokens)
        {
#ifdef TOKENIZER_DEBUG
            // std::cout << "------------------------" << '\n';
            std::cout << curr_token.to_string() << '\n';
#endif
            switch (curr_token.type())
            {
            case Token::Type::LP:
            {
                stack.push_back(two_pointer);
                two_pointer = MAKE_NODE0();
                break;
            }

            case Token::Type::RP:
            {
                std::shared_ptr<Cons> tmp1 = stack.back();
#ifdef TOKENIZER_DEBUG
                std::cout << "Stack Top: " << tmp1->to_string() << '\n';
                std::cout << "Two Pointer: " << two_pointer->to_string() << '\n';
#endif
                level_concat_using_two_pointer(tmp1, two_pointer);
                two_pointer = tmp1;
#ifdef TOKENIZER_DEBUG
                std::cout << "New Two Pointer: " << two_pointer->to_string() << '\n';
#endif
                stack.pop_back();
                break;
            }

            case Token::Type::Symbol:
            {
                auto symbol_obj = OBJECT_PTR_CAST(MAKE_SYMBOL(curr_token.as_symbol_value()));
                auto node = MAKE_NODE1(symbol_obj);
                append_using_two_pointer(two_pointer, node);
                break;
            }

            case Token::Type::Scaler:
            {
                auto scaler_obj = OBJECT_PTR_CAST(MAKE_SCALER(curr_token.as_scaler_value()));
                auto node = MAKE_NODE1(scaler_obj);
                append_using_two_pointer(two_pointer, node);
                break;
            }
            
            default:
                break;
            }
#ifdef TOKENIZER_DEBUG
            std::cout << two_pointer->to_string() << '\n';
            // std::cout << "------------------------" << '\n';
#endif
        }

#ifdef TOKENIZER_DEBUG
            std::cout << "Final Parse Tree: " << two_pointer->as_car()->to_string() << '\n';
#endif
        return two_pointer->as_car();
    }
}
