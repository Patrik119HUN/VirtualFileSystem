#pragma once
#include <string_view>

class IFileSystem {
public:
    virtual FILE open(std::string_view, uint8_t mode) = 0;

    virtual bool mkdir(std::string_view) = 0;

    virtual bool remove(std::string_view) = 0;

    virtual bool rmdir(std::string_view) = 0;
};
