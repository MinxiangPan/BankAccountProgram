cmake_minimum_required(VERSION 3.1)
project(A3)

set(CMAKE_CXX_STANDARD 11)

# Do not modify these flags other than switching between from the line with -ggdb to -O2 and back.
#set(CMAKE_CXX_FLAGS "-ggdb -std=c++11 -Werror -pedantic -Wall -Wuninitialized -Winit-self -Wredundant-decls -Wshadow  -Wno-unused -Wno-sign-compare -Wno-unused-variable")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Werror -pedantic -Wall -Wuninitialized -Winit-self -Wredundant-decls -Wshadow  -Wno-unused -Wno-sign-compare -Wno-unused-variable")

add_library(BankDatalog-obj OBJECT BankData.cpp)
add_library(Customer-obj OBJECT Customer.hpp)
add_library(Transaction-obj OBJECT Transaction.hpp)
# Set your working directory to the folder containing your project or this main will not function correctly.
add_executable(A3 main-tests.cpp $<TARGET_OBJECTS:Customer-obj> $<TARGET_OBJECTS:Transaction-obj> $<TARGET_OBJECTS:BankDatalog-obj>)