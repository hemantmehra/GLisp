cmake_minimum_required(VERSION 3.25)

project(GLisp)

include_directories(. Interpreter)
add_compile_options(-Wall -Wextra -Wpedantic)

# add_executable(glisp glisp.cpp)

add_executable(test test.cpp
                Interpreter/Object.cpp
                Interpreter/Scaler.cpp
                Interpreter/Symbol.cpp
                Interpreter/Cons.cpp
                Interpreter/Environment.cpp
                Interpreter/Interpreter.cpp
                Interpreter/PrimitiveProcedure.cpp
                Interpreter/Tokenizer.cpp
                Interpreter/Parser.cpp
)
