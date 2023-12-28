#pragma once

#include "../../include/inode.h"

namespace shos {
    class FolderNode : public INode {
        using inodes_t = std::list<INode*>;
    public:
        FolderNode() : INode("", Type::FOLDER) {}

        explicit FolderNode(std::string_view t_name) : INode(t_name, Type::FOLDER) {
        }

        explicit FolderNode(std::string_view t_name, FolderNode* t_parent) : INode(t_name, Type::FOLDER) {
            t_parent->files.push_back(this);
            this->prev_node = t_parent;
        }

        using iterator = inodes_t::iterator;
        using const_iterator = inodes_t::const_iterator;

        void add_file(INode* file) {
            files.push_back(file);
        }

        void remove_entry(std::string_view t_entry_name, Type t_type) {
            auto res = std::remove_if(files.begin(), files.end(), [t_entry_name, t_type](INode* node) {
                return node->get_name() == t_entry_name && node->get_type() == t_type;
            });
            if (res == files.end()) throw std::runtime_error("No Files found");
            files.erase(res);
            delete *res;
        }

        [[nodiscard]] INode* get_parent() const {
            return this->prev_node;
        }

        iterator begin() {
            return files.begin();
        }

        [[nodiscard]] bool empty() const {
            return files.empty();
        }

        iterator end() {
            return files.end();
        }

        const_iterator cbegin() {
            return files.cbegin();
        }

        const_iterator cend() {
            return files.cend();
        }

    private:
        INode* prev_node = nullptr;
        std::list<INode*> files;
    };
}
