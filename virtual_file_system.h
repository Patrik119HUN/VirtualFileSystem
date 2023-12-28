#pragma once

#include <string_view>
#include <map>
#include <optional>

#include "file_system_interface.h"
#include "tokenizer.h"
#include "folder_node.h"
#include "file_system_node.h"
#define PATH_MAX 4096
#include "path.h"
class VirtualFileSystem {
public:
    void mkdir(const std::string &t_path);

    int mknod(const std::string &t_path, INode* node);

    int mount(const std::string& t_path, IFileSystem* fs, const std::string &name);

    int rmdir(const std::string &t_path);

    static shos::FolderNode* find(std::vector<std::string> &paths, shos::FolderNode* from) {
        shos::FolderNode* lastInstance = from;
        while (!paths.empty()) {
            auto entry = std::find_if(lastInstance->begin(), lastInstance->end(), [paths](INode* node) {
                return node->get_name() == paths.front() && node->get_type() == Type::FOLDER;
            });

            //if (entry == lastInstance->end()) throw std::runtime_error("Not found!");
            if (entry == lastInstance->end()) return nullptr;
            lastInstance = dynamic_cast<shos::FolderNode*>(*entry);
            paths.erase(paths.begin());
        }
        return lastInstance;
    }

private:

    std::map<std::string, IFileSystem*> fileSystems;
    shos::FolderNode m_root;
};

extern VirtualFileSystem vfs;
