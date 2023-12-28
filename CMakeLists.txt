cmake_minimum_required(VERSION 3.22)
project(virtual_file_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(virtual_file_system main.cpp
        include/inode.h
        include/file_system_interface.h
        include/virtual_file_system.h
        libs/Tokenizer/tokenizer.h
        include/fat_file_system.h
        libs/FolderNode/folder_node.h
        src/virtual_file_system.cpp
        libs/FileSystemNode/file_system_node.h
        libs/Path/path.h
        libs/Tokenizer/tokenizer.cpp
)
