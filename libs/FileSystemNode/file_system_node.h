#pragma once

#include "../../include/inode.h"
#include "../../include/file_system_interface.h"

namespace shos {
    class FileSystemNode : public INode {
    public:
        FileSystemNode(IFileSystem* fileSystem, std::string_view t_name) : INode(t_name, Type::FILESYSTEM),
                                                                           fileSystem(fileSystem) {

        }

    private:
        IFileSystem* fileSystem;
    };
}