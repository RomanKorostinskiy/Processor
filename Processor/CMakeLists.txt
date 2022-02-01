cmake_minimum_required(VERSION 3.10)
project(Processor)

set(CMAKE_CXX_STANDARD 11)

include_directories(../GeneralInclude
        include)

add_executable(Processor
        src/Processor.cpp
        src/ProcessorFunc.cpp
        ../RequiredPrograms/StackFunc.cpp
        ../GeneralInclude/Proc_General.h
        include/Processor.h)