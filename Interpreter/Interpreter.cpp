#include <Interpreter/Cons.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Interpreter.h>
#include <Interpreter/PrimitiveProcedure.h>

#define CONS_PTR_CAST(x) std::dynamic_pointer_cast<Cons>(x)
#define SCALER_PTR_CAST(x) std::dynamic_pointer_cast<Scaler>(x)
#define OBJECT_PTR std::shared_ptr<Object>

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
            std::shared_ptr<Cons> cons_obj = CONS_PTR_CAST(obj);
            OBJECT_PTR proc = cons_obj->as_car();
            OBJECT_PTR args = cons_obj->as_cdr();
            return apply(eval(proc, env), args);
        }
    }

    OBJECT_PTR Interpreter::apply(OBJECT_PTR proc, OBJECT_PTR args)
    {
        (void) args;

        if (proc->is_primitive_procedure())
        {
            return apply_dispatch(proc, args);
        }
        return std::make_shared<Scaler>();
    }

    OBJECT_PTR Interpreter::apply_dispatch(OBJECT_PTR proc, OBJECT_PTR args)
    {
        std::shared_ptr<PrimitiveProcedure> proc_obj = std::dynamic_pointer_cast<PrimitiveProcedure>(proc);

        switch (proc_obj->type())
        {
        case PrimitiveProcedure::Type::Add:
        {
            std::shared_ptr<Cons> cons_obj = CONS_PTR_CAST(args);
            OBJECT_PTR arg1 = cons_obj->as_car();
            OBJECT_PTR arg2 = CONS_PTR_CAST(cons_obj->as_cdr())->as_car();

            if (arg1->is_scaler() && arg2->is_scaler()) {
                std::shared_ptr<Scaler> arg1_s = SCALER_PTR_CAST(arg1);
                std::shared_ptr<Scaler> arg2_s = SCALER_PTR_CAST(arg2);
                return std::make_shared<Scaler>(arg1_s->as_integer() + arg2_s->as_integer());
            }
        }
        
        default:
            break;
        }
        return std::make_shared<Scaler>();
    }
}
