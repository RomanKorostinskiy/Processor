cmake_minimum_required(VERSION 3.10)
project(Assembler)

set(CMAKE_CXX_STANDARD 11)

include_directories(../GeneralInclude
        include)

add_executable(Assembler
        src/Assembler.cpp
        src/AssemblerFunc.cpp
        ../RequiredPrograms/MakeStringFunc.cpp
        ../GeneralInclude/Processor.h
        include/Assembler.h)
