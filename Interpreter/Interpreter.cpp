#include <Interpreter/Cons.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Interpreter.h>

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
            return apply(proc, args);
        }
    }

    std::shared_ptr<Object> Interpreter::apply(std::shared_ptr<Object> proc, std::shared_ptr<Object> args)
    {
        (void) proc;
        (void) args;
        return std::make_shared<Scaler>();
    }
}
