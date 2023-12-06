#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <Object.h>

namespace LISP {
    class Environment
    {
    public:
        Object* get(const std::string);
        void set(const std::string, Object*);
        bool find(const std::string);

    private:
        std::unordered_map<std::string, Object*> m_env;
    };
}

#endif

