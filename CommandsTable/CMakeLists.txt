cmake_minimum_required(VERSION 3.20)
project(CommandsTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(CommandsTable
        table.cpp
        ../GeneralInclude/General.h)
