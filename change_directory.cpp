#include "esh_deps.h"
/*
 * Purpose: Change the current working directory
 * Parameters: title: name of the directory to change to
 * Precondition: Directory exists
 * Postcondition: Current directory is moved to the target directory
 */
int ESH::change_directory(const char *title) {

    TypeCastEntry entry;
    strncpy(entry.entry.name, title, 19);
    // move up one level in the directory path
    if (strcmp(entry.entry.name, "..") == 0) {
        if (current_dir == parent_dir) {
            return 0;
        }
        char buffer[kBlockSize];
        TypeCastEntry test;
        for (int i = 0; i < blocks_for_dir; ++i) {
            read_block(parent_dir + i, buffer);
            for (int j = 0; j < kBlockSize; j += 32) {
                for (int k = 0; k < 32; ++k) {
                    test.str[k] = buffer[j+k];
                }
                if (test.entry.starts_at == current_dir) {
                    current_dir = parent_dir;
                    parent_dir = test.entry.parent;
                    return 0;
                }
            }
        }
    } else if (strcmp(entry.entry.name, "\\") == 0) {
        // goes to root directory
        if (current_dir == parent_dir) {
            return 0;
        }
        current_dir = reserved_blocks;
        parent_dir = reserved_blocks;
        return 0;
    } else {
        char buffer[kBlockSize];
        TypeCastEntry test;
        for (int i = 0; i < blocks_for_dir; ++i) {
            read_block(current_dir + i, buffer);
            for (int j = 0; j < kBlockSize; j += 32) {
                for (int k = 0; k < 32; ++k) {
                    test.str[k] = buffer[j+k];
                }
                if (strcmp(test.entry.name, entry.entry.name) == 0) {
                    parent_dir = current_dir;
                    current_dir = test.entry.starts_at;
                    return 0;
                }
            }
        }
    }
    // Target directory does not exist
    std::cout << "Directory not found" << std::endl;
    return 1;
}
