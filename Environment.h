#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <GObject.h>

namespace LISP {
    class Environment
    {
    public:
        GObject* get(GObject*);
        void set(GObject*, GObject*);
        bool find(GObject*);

    private:
        std::unordered_map<std::string*, GObject*> m_env;
    };
}

#endif

