#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <GLisp/Object.h>
#include <GLisp/Environment.h>

namespace LISP {
    class Interpreter
    {
    public:
        std::shared_ptr<Object> eval(std::shared_ptr<Object>, std::shared_ptr<Environment>);
        std::shared_ptr<Object> apply(std::shared_ptr<Object>, std::shared_ptr<Object>);
    
    private:
        std::shared_ptr<Object> eval_list(std::shared_ptr<Object>, std::shared_ptr<Environment>);
        std::shared_ptr<Object> apply_dispatch(std::shared_ptr<Object>, std::shared_ptr<Object>);
    };
}

#endif
