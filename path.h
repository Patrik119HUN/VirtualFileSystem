#pragma once

#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ostream>

//Header file
class Tokenizer {
public:
    static const std::string DELIMITERS;

    Tokenizer(const std::string &str);

    Tokenizer(const std::string &str, const std::string &delimiters);

    bool NextToken();

    bool NextToken(const std::string &delimiters);

    const std::string GetToken() const {
        return m_token;
    }

    void Reset();

protected:
    size_t m_offset;
    const std::string m_string;
    std::string m_token;
    std::string m_delimiters;
};

//CPP file
const std::string Tokenizer::DELIMITERS(" \t\n\r");

Tokenizer::Tokenizer(const std::string &s) :
        m_string(s),
        m_offset(0),
        m_delimiters(DELIMITERS) {}

Tokenizer::Tokenizer(const std::string &s, const std::string &delimiters) :
        m_string(s),
        m_offset(0),
        m_delimiters(delimiters) {}

bool Tokenizer::NextToken() {
    return NextToken(m_delimiters);
}

bool Tokenizer::NextToken(const std::string &delimiters) {
    size_t i = m_string.find_first_not_of(delimiters, m_offset);
    if (std::string::npos == i) {
        m_offset = m_string.length();
        return false;
    }

    size_t j = m_string.find_first_of(delimiters, i);
    if (std::string::npos == j) {
        m_token = m_string.substr(i);
        m_offset = m_string.length();
        return true;
    }

    m_token = m_string.substr(i, j - i);
    m_offset = j;
    return true;
}

namespace shos {
    class Path {
    public:
        explicit Path(const std::string &path) {
            if (path.empty()) throw ENOENT;
            if (path.size() > PATH_MAX) throw ENAMETOOLONG;
            Tokenizer s(path, "/");
            while (s.NextToken()) {
                paths.push_back(s.GetToken());
            }
        }

        using deque_t = std::deque<std::string>;
        using iterator = deque_t::iterator;
        using const_iterator = deque_t::const_iterator;

        inline void pop_front() { paths.pop_front(); }

        [[nodiscard]] inline bool empty() const { return paths.empty(); }

        inline iterator begin() { return paths.begin(); }

        inline iterator end() { return paths.end(); }

        inline const_iterator cbegin() { return paths.cbegin(); }

        inline const_iterator cend() { return paths.cend(); }

        [[nodiscard]] inline std::string front() const { return paths.front(); }

        friend std::ostream &operator<<(std::ostream &os, shos::Path &path) {
            std::for_each(path.cbegin(), path.cend(), [&os](const std::string &s) { os << "/" << s; });
            return os;
        }

    private:
        deque_t paths;
    };
}