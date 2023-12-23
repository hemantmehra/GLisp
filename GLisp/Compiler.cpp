#include <iostream>
#include <sstream>
#include <GLisp/Cons.h>
#include <GLisp/Scaler.h>
#include <GLisp/Symbol.h>
#include <GLisp/Compiler.h>
#include <GLisp/PrimitiveProcedure.h>

#define CONS_PTR_CAST(x) std::dynamic_pointer_cast<Cons>(x)
#define SCALER_PTR_CAST(x) std::dynamic_pointer_cast<Scaler>(x)
#define SYMBOL_PTR_CAST(x) std::dynamic_pointer_cast<Symbol>(x)

#define OBJECT_PTR std::shared_ptr<Object>
#define CONS_PTR std::shared_ptr<Cons>

#define OBJECT_PTR_CAST(x) std::static_pointer_cast<Object>(x)
#define SCALER_PTR_CAST(x) std::dynamic_pointer_cast<Scaler>(x)
#define PRIM_PTR_CAST(x) std::dynamic_pointer_cast<PrimitiveProcedure>(x)

#define MAKE_NODE0() std::make_shared<Cons>()
#define MAKE_NODE1(x) std::make_shared<Cons>(x)
#define MAKE_NODE2(x, y) std::make_shared<Cons>(x, y)
#define NODE_CAR(x) std::dynamic_pointer_cast<Cons>(x)->as_car()
#define NODE_CDR(x) std::dynamic_pointer_cast<Cons>(x)->as_cdr()

#define SET_NODE_CAR(x, y) std::dynamic_pointer_cast<Cons>(x)->set_car(y)
#define SET_NODE_CDR(x, y) std::dynamic_pointer_cast<Cons>(x)->set_cdr(y)

#define MAKE_SCALER(x) std::make_shared<Scaler>(x)
#define MAKE_SYMBOL(x) std::make_shared<Symbol>(x)

#define MAKE_PRIMITVE_PROCEDURE(x) std::make_shared<LISP::PrimitiveProcedure>(x)
#define MAKE_PRIMITVE_PROCEDURE2(x, y) std::make_shared<LISP::PrimitiveProcedure>(x, y)
#define MAKE_PRIMITVE_PROCEDURE3(x, y, z) std::make_shared<LISP::PrimitiveProcedure>(x, y, z)

namespace LISP {
    int Compiler::generate_label_idx()
    {
        return m_label_idx++;
    }

    std::string Compiler::compile(std::shared_ptr<Object> obj, std::shared_ptr<Environment> env)
    {
        m_label_idx = 0;
        std::stringstream ss;
        m_bytecode.clear();
        eval(obj, env);

        ss << "segment .text" << '\n';
        ss << "global _start" << '\n';
        ss << "_start:" << '\n';

        for(auto obj: m_bytecode) {
            // std::cout << obj->to_string() << '\n';

            if (obj->is_scaler()) {
                ss << "    ;; push SCALER" << '\n';
                ss << "    push " << SCALER_PTR_CAST(obj)->as_integer() << '\n';
            }

            else if (obj->is_primitive_procedure()) {

                switch(PRIM_PTR_CAST(obj)->type()) {

                case PrimitiveProcedure::Type::Add:
                {
                    ss << "    ;; ADD" << '\n';
                    ss << "    pop rax" << '\n';
                    ss << "    pop rbx" << '\n';
                    ss << "    add rax, rbx" << '\n';
                    ss << "    push rax" << '\n';
                    break;
                }

                case PrimitiveProcedure::Type::Mul:
                {
                    break;
                }

                case PrimitiveProcedure::Type::If:
                {
                    
                    std::string else_label_name = "label_" + std::to_string(PRIM_PTR_CAST(obj)->data_1());

                    ss << "    ;; If" << '\n';
                    ss << "    pop rax" << '\n';
                    ss << "    test rax, rax" << '\n';
                    ss << "    jz " << else_label_name << '\n';
                    break;
                }

                case PrimitiveProcedure::Type::Else:
                {
                    
                    std::string else_label_name = "label_" + std::to_string(PRIM_PTR_CAST(obj)->data_1());
                    std::string endif_label_name = "label_" + std::to_string(PRIM_PTR_CAST(obj)->data_2());

                    ss << "    ;; Else" << '\n';
                    ss << "    jmp " << endif_label_name << '\n';
                    ss << else_label_name << ":" << '\n';
                    break;
                }

                case PrimitiveProcedure::Type::EndIf:
                {
                    
                    std::string endif_label_name = "label_" + std::to_string(PRIM_PTR_CAST(obj)->data_1());

                    ss << "    ;; End If" << '\n';
                    ss << endif_label_name << ":" << '\n';
                    break;
                }
                }
            }

            ss << '\n';
        }

        // EXIT asm code
        ss << "    ;; EXIT" << '\n';
        ss << "    mov rax, 60" << '\n';
        ss << "    pop rdi" << '\n';
        ss << "    syscall" << '\n';

        ss << '\n';

        return ss.str();
    }

    void Compiler::eval(OBJECT_PTR obj, std::shared_ptr<Environment> env)
    {
        if (obj->is_scaler()) {
            m_bytecode.push_back(obj);
            return;
        }

        else if (obj->is_symbol()) {
            m_bytecode.push_back(env->get(obj));
            return;
        }

        else if (obj->is_cons()) {
            OBJECT_PTR car = NODE_CAR(obj);
            if (car->is_symbol() && SYMBOL_PTR_CAST(car)->to_string() == "if") {
                int else_label_idx = generate_label_idx();
                int endif_label_idx = generate_label_idx();

                auto if_type = LISP::PrimitiveProcedure::Type::If;
                auto else_type = LISP::PrimitiveProcedure::Type::Else;
                auto endif_type = LISP::PrimitiveProcedure::Type::EndIf;

                auto p_if = MAKE_PRIMITVE_PROCEDURE2(if_type, else_label_idx);
                auto p_else = MAKE_PRIMITVE_PROCEDURE3(else_type, else_label_idx, endif_label_idx);
                auto p_endif = MAKE_PRIMITVE_PROCEDURE2(endif_type, endif_label_idx);

                auto exp = NODE_CAR(NODE_CDR(obj));
                auto if_block = NODE_CAR(NODE_CDR(NODE_CDR(obj)));
                auto else_block = NODE_CAR(NODE_CDR(NODE_CDR(NODE_CDR(obj))));

                eval(exp, env);
                m_bytecode.push_back(OBJECT_PTR_CAST(p_if));
                eval(if_block, env);
                m_bytecode.push_back(OBJECT_PTR_CAST(p_else));
                eval(else_block, env);
                m_bytecode.push_back(OBJECT_PTR_CAST(p_endif));
            }
        }

        else {
            CONS_PTR cons_obj = CONS_PTR_CAST(obj);
            OBJECT_PTR proc = cons_obj->as_car();
            OBJECT_PTR args = cons_obj->as_cdr();
            eval_list(args, env);
            eval(proc, env);
            return;
        }
    }

    void Compiler::eval_list(OBJECT_PTR obj, std::shared_ptr<Environment> env)
    {
        if (obj->is_nil()) {
            return;
        };

        OBJECT_PTR ptr0 = obj;
        eval(CONS_PTR_CAST(ptr0)->as_car(), env);
        ptr0 = CONS_PTR_CAST(ptr0)->as_cdr();

        while (!ptr0->is_nil())
        {
            eval(CONS_PTR_CAST(ptr0)->as_car(), env);
            ptr0 = CONS_PTR_CAST(ptr0)->as_cdr();
        }

        return;
    }

}
