#ifndef CONS_H
#define CONS_H

#include <string>
#include <memory>
#include <GLisp/Object.h>

namespace LISP {
    class Cons : public Object
    {
    public:
        Cons();
        Cons(std::shared_ptr<Object>);
        Cons(std::shared_ptr<Object>, std::shared_ptr<Object>);
        std::shared_ptr<Object> as_car();
        std::shared_ptr<Object> as_cdr();
        void set_car(std::shared_ptr<Object>);
        void set_cdr(std::shared_ptr<Object>);
        virtual bool is_cons() const override { return true; }
        std::string to_string() override;

    private:
        std::shared_ptr<Object> m_car;
        std::shared_ptr<Object> m_cdr;
    };
}

#endif
