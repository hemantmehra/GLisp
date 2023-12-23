#ifndef COMPILER_H
#define COMPILER_H

#include <memory>
#include <vector>
#include <GLisp/Object.h>
#include <GLisp/Environment.h>

namespace LISP {
    class Compiler
    {
    public:
        void eval(std::shared_ptr<Object>, std::shared_ptr<Environment>);

        std::vector<std::shared_ptr<Object>> get_bytecode() { return m_bytecode; }
    private:
        void eval_list(std::shared_ptr<Object>, std::shared_ptr<Environment>);

        std::vector<std::shared_ptr<Object>> m_bytecode;
    };
}

#endif
