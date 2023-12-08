#include <eval_apply.h>
#include <GObject.h>
#include <cassert>

namespace LISP {
    GObject* Interpreter::eval(GObject* exp, Environment* env)
    {
        if (exp->is_self_eval()) return exp;
        else if (exp->is_symbol()) {
            return env->get(exp);
        }
        else {
            assert(exp->is_cons());
            return apply(eval(exp->as_cons_car(), env), exp->as_cons_cdr());
        }
    }

    GObject* Interpreter::apply(GObject* proc, GObject* args)
    {
        if (proc->is_primitive_proc()) {
            return apply_primitive_proc(proc, args);
        }
        else {
            assert(0);
            return proc;
        }
    }

    GObject* Interpreter::apply_primitive_proc(GObject* proc, GObject* args)
    {
        if (proc->as_primitive_proc() == GObject::Primitive_Proc::ADD) {
            assert(args->is_cons());
            GObject* operand1 = args->as_cons_car();
            GObject* operand2 = args->as_cons_cdr();
            GObject* result = new GObject(operand1->as_integer() + operand2->as_integer());
            return result;
        }

        if (proc->as_primitive_proc() == GObject::Primitive_Proc::MUL) {
            assert(args->is_cons());
            GObject* operand1 = args->as_cons_car();
            GObject* operand2 = args->as_cons_cdr();
            GObject* result = new GObject(operand1->as_integer() * operand2->as_integer());
            return result;
        }

        assert(0);
        return proc;
    }
}
