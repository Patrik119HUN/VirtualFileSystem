#pragma once

#include "file_system_interface.h"
#include <iostream>

class FatFileSystem {
public:
    FILE open(std::string_view path, uint8_t mode) {
        std::cout << "OPEN FAT FILE" << std::endl;
    }

    bool make_dir(std::string_view path) {
        std::cout << "MAKE DIRECTORY FAT FILE" << std::endl;
        return true;
    };

    bool remove(std::string_view path) {
        std::cout << "REMOVE FAT FILE" << std::endl;
        return true;
    }

    bool remove_dir(std::string_view path) {
        std::cout << "REMOVE DIR FAT FILE" << std::endl;
        return true;
    }

};

class FatFileSystemAdapter : public IFileSystem {
public:
    explicit FatFileSystemAdapter(FatFileSystem &fileSystem) : fatFileSystem(fileSystem) {}

    FILE open(std::string_view t_path, uint8_t mode) {
        return fatFileSystem.open(t_path, mode);
    };

    bool mkdir(std::string_view t_path) {
        return fatFileSystem.make_dir(t_path);
    }

    bool remove(std::string_view t_path) {
        return fatFileSystem.remove(t_path);
    }

    bool rmdir(std::string_view t_path) {
        return fatFileSystem.remove_dir(t_path);
    }

private:
    FatFileSystem fatFileSystem;
};