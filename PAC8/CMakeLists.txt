cmake_minimum_required(VERSION 3.15)
project(PAC8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(PAC8)
include_directories(PAC8/include)
include_directories(PAC8/source)

add_executable(PAC8
        PAC8/Debug/PAC8
        PAC8/Debug/source_fairgroundRide.c.o
        PAC8/Debug/source_fairgroundRide.c.o.d
        PAC8/Debug/source_main.c.o
        PAC8/Debug/source_main.c.o.d
        PAC8/include/fairgroundRide.h
        PAC8/source/fairgroundRide.c
        PAC8/source/main.c
        PAC8/compile_flags.txt
        PAC8/data.txt
        PAC8/fRide1.txt
        PAC8/PAC8.mk
        PAC8/PAC8.project
        PAC8/PAC8.txt
        Makefile
        PAC8.workspace)
