#include <string>
#include <cassert>
#include <GObject.h>

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

        if (is_cons()) {
            return "(" + as_cons_car()->to_string() + " " + as_cons_cdr()->to_string()  +  ")";
        }

        assert(0);
        return "";
    }
}
