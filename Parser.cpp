#include <vector>
#include <cassert>
#include <Tokenizer.h>
#include <Parser.h>
#include <GObject.h>

namespace LISP {
    GObject* Parser::parse(std::vector<Token>* stream)
    {
        GObject *start, *curr, *obj;
        auto it = stream->begin();
        curr = new GObject();
        start = NULL;

        while(it != stream->end())
        {
            if (it->is_open()) {
                obj = new GObject(new GObject(), new GObject());
                curr = obj;

                if (!start) {
                    start = obj;
                }
            }

            else if (it->is_close()) {
                return start->as_cons_cdr();
            }

            else if (it->is_integer()) {
                GObject *t = new GObject(it->as_integer());
                obj = new GObject(t, new GObject());
                curr->set_cons_cdr(obj);
                curr = obj;
            }

            else if (it->is_symbol()) {
                GObject *t = new GObject(it->as_symbol());
                obj = new GObject(t, new GObject());
                curr->set_cons_cdr(obj);
                curr = obj;
            }

            else {
                assert(0);
            }
            
            it++;
        }

        return curr;
    }
}
