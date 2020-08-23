cmake_minimum_required(VERSION 3.4.1)
project(Project_tohna C)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic-errors")

set(CMAKE_C_STANDARD 90)

add_executable(Project_tohna main.c fileHandler.c fileHandler.h Algo2.c Algo2.h Modularity.c Modularity.h Group_handler.c Group_handler.h structures.h Power_iter.c Power_iter.h)