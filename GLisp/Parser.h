#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include <GLisp/Tokenizer.h>
#include <GLisp/Object.h>

namespace LISP {
    class Parser
    {
    public:
        std::shared_ptr<Object> parse(std::vector<Token>);
    };
}

#endif
