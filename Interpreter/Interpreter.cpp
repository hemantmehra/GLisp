#include <Interpreter/Cons.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Interpreter.h>
#include <Interpreter/PrimitiveProcedure.h>

#define CONS_PTR_CAST(x) std::dynamic_pointer_cast<Cons>(x)
#define SCALER_PTR_CAST(x) std::dynamic_pointer_cast<Scaler>(x)
#define OBJECT_PTR std::shared_ptr<Object>
#define CONS_PTR std::shared_ptr<Cons>

#define OBJECT_PTR_CAST(x) std::static_pointer_cast<Object>(x)
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
    OBJECT_PTR Interpreter::eval(OBJECT_PTR obj, std::shared_ptr<Environment> env)
    {
        if (obj->is_scaler()) {
            return obj;
        }

        else if (obj->is_symbol()) {
            return env->get(obj);
        }

        else {
            CONS_PTR cons_obj = CONS_PTR_CAST(obj);
            OBJECT_PTR proc = cons_obj->as_car();
            OBJECT_PTR args = cons_obj->as_cdr();
            return apply(eval(proc, env), eval_list(args, env));
        }
    }

    OBJECT_PTR Interpreter::apply(OBJECT_PTR proc, OBJECT_PTR args)
    {
        if (proc->is_primitive_procedure())
        {
            return apply_dispatch(proc, args);
        }
        return std::make_shared<Scaler>();
    }

    OBJECT_PTR Interpreter::eval_list(OBJECT_PTR obj, std::shared_ptr<Environment> env)
    {
        if (obj->is_nil()) return obj;

        OBJECT_PTR ptr0 = obj;
        OBJECT_PTR ptr1 = MAKE_NODE1(eval(CONS_PTR_CAST(ptr0)->as_car(), env));
        OBJECT_PTR ptr2 = ptr1;
        OBJECT_PTR tmp;

        ptr0 = CONS_PTR_CAST(ptr0)->as_cdr();

        while (!ptr0->is_nil())
        {
            tmp = MAKE_NODE1(eval(CONS_PTR_CAST(ptr0)->as_car(), env));
            SET_NODE_CDR(ptr2, tmp);
            ptr2 = CONS_PTR_CAST(ptr2)->as_cdr();
            ptr0 = CONS_PTR_CAST(ptr0)->as_cdr();
        }
        
        return ptr1;
    }

    OBJECT_PTR Interpreter::apply_dispatch(OBJECT_PTR proc, OBJECT_PTR args)
    {
        std::shared_ptr<PrimitiveProcedure> proc_obj = std::dynamic_pointer_cast<PrimitiveProcedure>(proc);

        switch (proc_obj->type())
        {
        case PrimitiveProcedure::Type::Add:
        {
            CONS_PTR cons_obj = CONS_PTR_CAST(args);
            OBJECT_PTR arg1 = cons_obj->as_car();
            OBJECT_PTR arg2 = CONS_PTR_CAST(cons_obj->as_cdr())->as_car();

            if (arg1->is_scaler() && arg2->is_scaler()) {
                std::shared_ptr<Scaler> arg1_s = SCALER_PTR_CAST(arg1);
                std::shared_ptr<Scaler> arg2_s = SCALER_PTR_CAST(arg2);
                return std::make_shared<Scaler>(arg1_s->as_integer() + arg2_s->as_integer());
            }
            break;
        }

        case PrimitiveProcedure::Type::Mul:
        {
            CONS_PTR cons_obj = CONS_PTR_CAST(args);
            OBJECT_PTR arg1 = cons_obj->as_car();
            OBJECT_PTR arg2 = CONS_PTR_CAST(cons_obj->as_cdr())->as_car();

            if (arg1->is_scaler() && arg2->is_scaler()) {
                std::shared_ptr<Scaler> arg1_s = SCALER_PTR_CAST(arg1);
                std::shared_ptr<Scaler> arg2_s = SCALER_PTR_CAST(arg2);
                return std::make_shared<Scaler>(arg1_s->as_integer() * arg2_s->as_integer());
            }
            break;
        }
        
        default:
            break;
        }
        return std::make_shared<Scaler>();
    }
}
