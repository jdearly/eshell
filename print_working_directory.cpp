#include "esh_deps.h"
/*
 * Purpose: Prints the current working directory
 * Parameters: None.
 * Precondition: None.
 * Postcondition: Prints the current working directory
 */
int ESH::print_working_directory() {

    if (current_dir == reserved_blocks) {
        std::cout << "Current directory is root" << std::endl;
    } else {
        int par = parent_dir;
        int current = current_dir;
        std::string directory_path = "";
        do {
            char buffer[kBlockSize];
            read_block(par, buffer);
            for (int j = 0; j < kBlockSize; j += 32) {
                TypeCastEntry entry;
                for (int k = 0; k < 32; ++k) {
                    entry.str[k] = buffer[j+k];
                }
                if (entry.entry.starts_at == current) {
                    current = par;
                    par = entry.entry.parent;
                    std::string temp = entry.entry.name;
                    directory_path = "/" + temp + directory_path;
                    break;
                }
            }
        } while (current != reserved_blocks);
        std::cout << "Current directory is root" + directory_path << std::endl;
    }
    return 0;
}
