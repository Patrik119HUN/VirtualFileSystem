#pragma once

#include <string>
#include <variant>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

enum class Type {
    FOLDER, FILESYSTEM, DEVICE
};

class INode {
public:
    explicit INode(std::string_view t_name, Type t_type) : name(t_name), type(t_type), created_at(std::time(nullptr)) {
    }

    virtual ~INode() = default;

    INode(const INode &iNode) : created_at(0) {
        if (*this == iNode) { return; }
        this->type = iNode.type;
        this->name = iNode.name;
    }

    [[nodiscard]] const std::string &get_name() const {
        return name;
    }

    [[nodiscard]] Type get_type() const {
        return type;
    }

    bool operator==(const INode &rhs) const {
        return name == rhs.name &&
               type == rhs.type;
    }

    bool operator!=(const INode &rhs) const {
        return !(rhs == *this);
    }

protected:
    const std::time_t created_at;
    std::string name;
    Type type;
};
