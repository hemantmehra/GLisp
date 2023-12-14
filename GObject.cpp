#include <string>
#include <cassert>
#include <GObject.h>
#include <iostream>

namespace LISP {    
    std::string GObject::to_string()
    {
        if (is_nil()) {
            return "NIL";
        }
        if (is_integer()) {
            return std::to_string(as_integer());
        }

        if (is_symbol()) {
            return *as_symbol();
        }

        if (is_string()) {
            return *as_string();
        }

        if (is_boolean()) {
            return as_bool() ? "true" : "false";
        }
        
        if (is_cons()) {
            return "(" + as_cons_car()->to_string() + " " + as_cons_cdr()->to_string()  +  ")";
        }

        if (is_primitive_proc()) {
            return "primitive";
        }
        assert(0);
        return "";
    }
}
