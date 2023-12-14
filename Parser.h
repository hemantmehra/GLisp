#ifndef PARSER_H
#define PARSER_H

#include <cassert>
#include <string>
#include <vector>
#include <Tokenizer.h>
#include <GObject.h>

namespace LISP {
    class Parser
    {
    public:
        GObject* parse(std::vector<Token>*);
        
    private:

    };
}

#endif
