#pragma once

#include <string>
#include <vector>
#include <sstream>

#define SYMLOOP_MAX 10
#define NAME_MAX 32

static std::vector<std::string> tokenize(const std::string &path, const char delim) {
    std::istringstream stream(path);
    std::vector<std::string> vec;
    std::string token;
    int i = 0;
    while (std::getline(stream, token, delim)) {
        if (i > SYMLOOP_MAX) throw ELOOP;
        if (token.size() > NAME_MAX) throw ENAMETOOLONG;
        vec.push_back(token);
        i++;
    }
    return vec;
}
