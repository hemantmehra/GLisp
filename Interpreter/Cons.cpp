#include <memory>
#include <Interpreter/Scaler.h>
#include <Interpreter/Cons.h>

namespace LISP {
    Cons::Cons()
    {
        m_car = std::static_pointer_cast<Object>(std::make_shared<Scaler>());
        m_cdr = std::static_pointer_cast<Object>(std::make_shared<Scaler>());
    }

    Cons::Cons(std::shared_ptr<Object> a)
    {
        m_car = a;
        m_cdr = std::static_pointer_cast<Object>(std::make_shared<Scaler>());
    }

    Cons::Cons(std::shared_ptr<Object> a, std::shared_ptr<Object> b)
    {
        m_car = a;
        m_cdr = b;
    }

    std::shared_ptr<Object> Cons::as_car()
    {
        return m_car;
    }
    
    std::shared_ptr<Object> Cons::as_cdr()
    {
        return m_cdr;
    }

    void Cons::set_car(std::shared_ptr<Object> x)
    {
        m_car = x;
    }

    void Cons::set_cdr(std::shared_ptr<Object> x)
    {
        m_cdr = x;
    }

    std::string Cons::to_string()
    {
        return "(" + m_car->to_string() + ", " + m_cdr->to_string() + ")";
    }
}
