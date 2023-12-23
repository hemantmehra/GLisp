#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <GLisp/Object.h>

namespace LISP {
    class Symbol : public Object
    {
    public:
        Symbol(std::string x) : m_name(x) {}
        std::string name() const;
        virtual bool is_symbol() const override { return true; }
        std::string to_string() override;

    private:
        std::string m_name;
    };
}

#endif
