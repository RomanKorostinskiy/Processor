cmake_minimum_required(VERSION 3.20)
project(Disassembler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include
        ../GeneralInclude)

add_executable(Disassembler
        include/Disasm.h
        src/Disasm.cpp
        src/DisasmFunc.cpp
        ../GeneralInclude/General.h)
