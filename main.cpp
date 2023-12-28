#include "virtual_file_system.h"
#include "fat_file_system.h"
#include "path.h"

int main() {
    vfs.mkdir("alma/béka");
    vfs.mkdir("alma/kaka");
    vfs.rmdir("alma/kaka");
    vfs.mkdir("kaka/kaka");
    FatFileSystem fat;
    vfs.mount("kaka/kaka", new FatFileSystemAdapter(fat), "C");
    //vfs.mkdir("/C/alma");
    shos::Path path("/alma/béka");
    path.pop_front();
    for (const auto &i: path) {
        std::cout << "a: " << i << std::endl;
    }
    std::cout << path << std::endl;
    return 0;
}