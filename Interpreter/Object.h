#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace LISP {
    class Object
    {
    public:
        virtual std::string to_string() = 0;
    };
}

#endif
