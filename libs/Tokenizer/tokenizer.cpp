#include "tokenizer.h"

const std::string shos::Tokenizer::DELIMITERS(" \t\n\r");

shos::Tokenizer::Tokenizer(std::string_view str) :
        m_string(str),
        m_offset(0),
        m_delimiters(DELIMITERS) {}

shos::Tokenizer::Tokenizer(std::string_view str, std::string_view delimiters) :
        m_string(str),
        m_offset(0),
        m_delimiters(delimiters) {}

bool shos::Tokenizer::next_token() {
    return next_token(m_delimiters);
}

bool shos::Tokenizer::next_token(const std::string &delimiters) {
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
