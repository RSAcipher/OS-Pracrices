cmake_minimum_required(VERSION 3.27)
project(Task1 C)

set(CMAKE_C_STANDARD 17)

add_executable(Task1 sender.c
        "reciever.c"
        sender.h
        reciever.h
)
