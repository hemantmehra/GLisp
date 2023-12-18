#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <Interpreter/Object.h>

namespace LISP {
    class Symbol : public Object
    {
    public:
        Symbol(std::string x) : m_name(x) {}
        std::string name() const;
        std::string to_string() override;

    private:
        std::string m_name;
    };
}

#endif
