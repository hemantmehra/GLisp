#ifndef EVAL_APPLY_H
#define EVAL_APPLY_H

#include <Environment.h>
#include <GObject.h>

namespace LISP {
    class Interpreter
    {
    public:
        GObject* eval(GObject*, Environment*);
        GObject* apply(GObject*, GObject*);

    private:
        GObject* apply_primitive_proc(GObject*, GObject*);
    };
}

#endif
