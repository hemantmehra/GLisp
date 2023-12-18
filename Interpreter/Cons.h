#ifndef CONS_H
#define CONS_H

#include <string>
#include <memory>
#include <Interpreter/Object.h>

namespace LISP {
    class Cons : public Object
    {
    public:
        Cons(std::shared_ptr<Object>&);
        Cons(std::shared_ptr<Object>&, std::shared_ptr<Object>&);
        std::string to_string() override;

    private:
        std::shared_ptr<Object> m_car;
        std::shared_ptr<Object> m_cdr;
    };
}

#endif
