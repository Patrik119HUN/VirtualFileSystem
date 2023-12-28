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
class Tokenizer {
public:
    static const std::string DELIMITERS;

    explicit Tokenizer(std::string_view str);

    Tokenizer(std::string_view str, std::string_view delimiters);

    bool NextToken();

    bool NextToken(const std::string &delimiters);

    [[nodiscard]] std::string GetToken() const {
        return m_token;
    }

    void Reset();

protected:
    size_t m_offset;
    const std::string m_string;
    std::string m_token;
    std::string m_delimiters;
};