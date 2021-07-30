#include "esh_deps.h"
/*
 * Purpose: Reserve blocks for the binary file
 * Parameters: already_exists: true/false if binary file already exists
 * Precondition: None.
 * Postcondition: File is created and space reserved
 */
void ESH::create(bool already_exists) {
\
    if (!already_exists) {
        TypeCastInt cast;
        cast.num = 0;
        char buffer[kBlockSize];
        std::ofstream ofile;
        ofile.open(kDiskTitle, std::ios::binary | std::ios::out);
        for(int i = 0; i< kBlockSize; ++i) {
            buffer[i] = cast.str[i%4];
        }
        // fill space on the file with 0s
        for(int i = 0; i < kNumberOfBlocks; ++i) {
            ofile.write(buffer, kBlockSize);
        }
        ofile.close();

        // root space
        for (int i = 0; i < blocks_for_dir; ++i) {
            update_status(reserved_blocks + i, dir_entry);
        }
    }
}
