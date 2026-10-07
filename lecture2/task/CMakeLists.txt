cmake_minimum_required(VERSION 4.3)
project(task)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(task
        include/BinaryTree.tpp
        include/BinaryTree.h
        include/linked_queue.h
        include/helpers.h
        src/helpers.cpp
        main.cpp
)
