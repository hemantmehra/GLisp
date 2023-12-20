#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <memory>
#include <unordered_map>
#include <Interpreter/Object.h>

namespace LISP {
    class Environment
    {
    public:
        std::shared_ptr<Object> get(std::shared_ptr<Object>);
        void set(std::shared_ptr<Object>, std::shared_ptr<Object>);
        void set_using_string(std::string, std::shared_ptr<Object>);
        bool find(std::shared_ptr<Object>);

    private:
        std::unordered_map<std::string, std::shared_ptr<Object>> m_env;
    };
}

#endif
