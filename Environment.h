#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <GObject.h>

namespace LISP {
    class Environment
    {
    public:
        GObject* get(const std::string);
        void set(const std::string, GObject*);
        bool find(const std::string);

    private:
        std::unordered_map<std::string, GObject*> m_env;
    };
}

#endif

