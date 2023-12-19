#include <Interpreter/Cons.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Interpreter.h>
#include <Interpreter/PrimitiveProcedure.h>

namespace LISP {
    std::shared_ptr<Object> Interpreter::eval(std::shared_ptr<Object> obj, std::shared_ptr<Environment> env)
    {
        if (obj->is_scaler()) {
            return obj;
        }

        else if (obj->is_symbol()) {
            return env->get(obj);
        }

        else {
            std::shared_ptr<Cons> cons_obj = std::dynamic_pointer_cast<Cons>(obj);
            std::shared_ptr<Object> proc = cons_obj->as_car();
            std::shared_ptr<Object> args = cons_obj->as_cdr();
            return apply(eval(proc, env), args);
        }
    }

    std::shared_ptr<Object> Interpreter::apply(std::shared_ptr<Object> proc, std::shared_ptr<Object> args)
    {
        (void) args;

        if (proc->is_primitive_procedure())
        {
            return apply_dispatch(proc, args);
        }
        return std::make_shared<Scaler>();
    }

    std::shared_ptr<Object> Interpreter::apply_dispatch(std::shared_ptr<Object> proc, std::shared_ptr<Object> args)
    {
        (void) args;
        std::shared_ptr<PrimitiveProcedure> proc_obj = std::dynamic_pointer_cast<PrimitiveProcedure>(proc);

        switch (proc_obj->type())
        {
        case PrimitiveProcedure::Type::Add:
        {
            std::shared_ptr<Cons> cons_obj = std::dynamic_pointer_cast<Cons>(args);
            std::shared_ptr<Object> arg1 = cons_obj->as_car();
            std::shared_ptr<Object> arg2 = cons_obj->as_cdr();

            if (arg1->is_scaler() && arg2->is_scaler()) {
                std::shared_ptr<Scaler> arg1_s = std::dynamic_pointer_cast<Scaler>(arg1);
                std::shared_ptr<Scaler> arg2_s = std::dynamic_pointer_cast<Scaler>(arg2);
                return std::make_shared<Scaler>(arg1_s->as_integer() + arg2_s->as_integer());
            }
        }
        
        default:
            break;
        }
        return std::make_shared<Scaler>();
    }
}
