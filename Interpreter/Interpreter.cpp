#include <Interpreter/Scaler.h>
#include <Interpreter/Interpreter.h>

namespace LISP {
    std::shared_ptr<Object> Interpreter::eval(std::shared_ptr<Object> obj, std::shared_ptr<Environment> env)
    {
        (void) env;

        if (obj->is_scaler()) {
            return obj;
        }
        return std::make_shared<Scaler>();
    }

    std::shared_ptr<Object> Interpreter::apply(std::shared_ptr<Object> proc, std::shared_ptr<Object> args)
    {
        (void) proc;
        (void) args;
        return std::make_shared<Scaler>();
    }
}
