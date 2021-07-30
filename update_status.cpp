#include "esh_deps.h"
/*
 * Purpose: Updates the status of a block of memory
 * Parameters: block_no, x: the block number to update, and the status
 * Precondition: None
 * Postcondition: The block is marked with a status
 */
int ESH::update_status(int block_no, int x) {

    int status = get_status(block_no);
    if (status != RESERVED && status != NOT_FOUND) {
        TypeCastInt cast;
        int position = (block_no - reserved_blocks)*4;

        // particular block to read
        int block_offset = position / kBlockSize;

         // size of block at offset position
        int byte_in_block = position % kBlockSize;

        char buffer[kBlockSize];
        cast.num = x;
        std::fstream fp;
        fp.open(kDiskTitle, std::ios::binary | std::ios::in | std::ios::out);
        fp.seekg(block_offset * kBlockSize);
        fp.read(buffer, kBlockSize);

        // edit buffer
        for (int i = 0, j = 0; j < 4; ++i, ++j) {
            buffer[byte_in_block + i] = cast.str[j];
        }
        
        fp.seekp(block_offset * kBlockSize);
        fp.write(buffer, kBlockSize);
        fp.close();
        return x;
    } else {
        return -1;
    }
}
