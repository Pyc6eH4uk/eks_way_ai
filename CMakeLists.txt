cmake_minimum_required(VERSION 3.8.2)
project(eks_way_ai)

set(CMAKE_CXX_STANDARD 11)

add_executable(eks_way_ai
        source/abstract_simplex_task_t.cpp
        source/abstract_simplex_task_t.h
        source/linear_cut_task_t.cpp
        source/linear_cut_task_t.h
        source/simplex_definitions.h
        source/simplex_method_equality_t.cpp
        source/simplex_method_equality_t.h
        source/simplex_method_t.cpp
        source/simplex_method_t.h
        source/simplex_method_unequality_t.cpp
        source/simplex_method_unequality_t.h
        source/simplex_task_t.cpp
        source/simplex_task_t.h
        main.cpp source/abstract_debuger_t.cpp source/abstract_debuger_t.h source/linear_cut_debuger_t.cpp source/linear_cut_debuger_t.h)
