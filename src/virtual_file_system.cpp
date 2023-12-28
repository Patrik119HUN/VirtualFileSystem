#include "../include/virtual_file_system.h"

void VirtualFileSystem::mkdir(const std::string &t_path) {
    shos::Path path(t_path);
    shos::FolderNode* lastInstance = &m_root;
    while (!path.empty()) {
        auto folder = std::find_if(lastInstance->begin(), lastInstance->end(), [path](INode* node) {
            return node->get_name() == path.front() && node->get_type() == Type::FOLDER;
        });

        lastInstance = (folder == lastInstance->end()) ? new shos::FolderNode(path.front(), lastInstance)
                                                       : dynamic_cast<shos::FolderNode*>(*folder);
        path.pop_front();
    }
}

int VirtualFileSystem::rmdir(const std::string &t_path) {
    if (t_path.empty()) return ENOENT;
    if (t_path.size() > PATH_MAX) return ENAMETOOLONG;

    auto paths = tokenize(t_path, '/');
    shos::FolderNode* lastInstance = VirtualFileSystem::find(paths, &m_root);
    if (lastInstance == nullptr || !lastInstance->empty()) return -1;
    auto parent = dynamic_cast<shos::FolderNode*>(lastInstance->get_parent());
    parent->remove_entry(lastInstance->get_name(), Type::FOLDER);
}

int VirtualFileSystem::mount(const std::string &t_path, IFileSystem* fs, const std::string &name) {
    if (t_path.empty()) throw ENOENT;
    if (t_path.size() > PATH_MAX) throw ENAMETOOLONG;


    auto paths = tokenize(t_path, '/');
    shos::FolderNode* lastInstance = VirtualFileSystem::find(paths, &m_root);
    if (lastInstance == nullptr || !lastInstance->empty()) return -1;
    lastInstance->add_file(new shos::FileSystemNode(fs,name));
}

int VirtualFileSystem::mknod(const std::string &t_path, INode* node) {
    if (t_path.empty()) throw ENOENT;
    if (t_path.size() > PATH_MAX) throw ENAMETOOLONG;
    //VirtualFileSystem::find(t_path, &m_root)->add_file(node);
}

VirtualFileSystem vfs;