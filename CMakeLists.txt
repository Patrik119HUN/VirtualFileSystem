cmake_minimum_required(VERSION 3.22)
project(virtual_file_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(virtual_file_system main.cpp
        inode.h
        file_system_interface.h
        virtual_file_system.h
        tokenizer.h
        fat_file_system.h
        folder_node.h
        virtual_file_system.cpp
        file_system_node.h
        path.h)
