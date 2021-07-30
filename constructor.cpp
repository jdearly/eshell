#include "esh_deps.h"
/*
 * Purpose: Constructor for main
 */
ESH::ESH(
    std::string title,
        int disk_size,
        bool already_exists) :
        kDiskTitle(title),
        kDiskSize(disk_size) {
    kNumberOfBlocks = kDiskSize/kBlockSize;
    reserved_blocks = kNumberOfBlocks/128;
    current_dir = reserved_blocks;  // root
    parent_dir = reserved_blocks;
    create(already_exists);
}
