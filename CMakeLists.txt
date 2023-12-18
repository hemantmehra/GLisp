cmake_minimum_required(VERSION 3.25)

project(GLisp)

include_directories(. Interpreter)
add_compile_options(-Wall -Wextra -Wpedantic)

# add_executable(main main.cpp Integer.cpp Cons.cpp Environment.cpp eval_apply.cpp Parser.cpp GObject.cpp Tokenizer.cpp)

# add_executable(glisp glisp.cpp)

add_executable(test test.cpp
                Interpreter/Scaler.cpp
                Interpreter/Symbol.cpp
                Interpreter/Cons.cpp
                Interpreter/Environment.cpp
)

