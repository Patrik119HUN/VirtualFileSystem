#pragma once

#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ostream>

//Header file

namespace shos {
    class Path {
    public:
        explicit Path(const std::string &path) {
            if (path.empty()) throw ENOENT;
            if (path.size() > PATH_MAX) throw ENAMETOOLONG;
            shos::Tokenizer s(path, "/");
            while (s.next_token()) {
                paths.push_back(s.get_token());
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