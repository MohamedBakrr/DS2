cmake_minimum_required(VERSION 4.3)
project(task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(avl_demo src/avl_demo.cpp)
target_include_directories(avl_demo PRIVATE include)

add_executable(avl_tests tests/avl_tests.cpp)
target_include_directories(avl_tests PRIVATE include)

enable_testing()
add_test(NAME avl_tests COMMAND avl_tests)

add_executable(task
        include/BinaryTree.tpp
        include/BinaryTree.h
        include/linked_queue.h
        include/helpers.h
        src/helpers.cpp
        main.cpp
        include/AVLTree.h
        include/AVLTree.tpp
        src/avl_demo.cpp
        tests/avl_tests.cpp
)
