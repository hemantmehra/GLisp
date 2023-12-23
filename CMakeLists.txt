cmake_minimum_required(VERSION 3.25)

project(GLisp)

include_directories(. Interpreter)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(test test.cpp
                GLisp/Object.cpp
                GLisp/Scaler.cpp
                GLisp/Symbol.cpp
                GLisp/Cons.cpp
                GLisp/Environment.cpp
                GLisp/Interpreter.cpp
                GLisp/PrimitiveProcedure.cpp
                GLisp/Tokenizer.cpp
                GLisp/Parser.cpp
)

add_executable(glisp glisp.cpp
                GLisp/Object.cpp
                GLisp/Scaler.cpp
                GLisp/Symbol.cpp
                GLisp/Cons.cpp
                GLisp/Environment.cpp
                GLisp/Interpreter.cpp
                GLisp/PrimitiveProcedure.cpp
                GLisp/Tokenizer.cpp
                GLisp/Parser.cpp
)
