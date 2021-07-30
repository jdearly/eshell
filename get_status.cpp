#include "esh_deps.h"
/*
 * Purpose: Gets the status of a particular block
 * Parameters: block_no: particular block number
 * Precondition: Block exists
 * Postcondition: Returns the status of a block
 */
int ESH::get_status(int block_no) const {

    if (block_no > kNumberOfBlocks - 1) {
        return NOT_FOUND;
    } else if (block_no < reserved_blocks) {
        return RESERVED;
    } else {
        int position = (block_no - reserved_blocks)*4;

        // block to read from binary file
        int block_offset = position / kBlockSize;

         // bytes to extract from given block at block offset
        int byte_in_block = position % kBlockSize;

        char buffer[kBlockSize];
        std::ifstream ifile;
        ifile.open(kDiskTitle, std::ios::binary | std::ios::in);
        ifile.seekg(block_offset * kBlockSize);
        ifile.read(buffer, kBlockSize);
        ifile.close();

        TypeCastInt cast;
        for (int i = 0; i < 4; ++i) {
            cast.str[i] = buffer[byte_in_block + i];
        }

        if (cast.num == 1) {
            return BUSY;
        } else if (cast.num == 0) {
            return free;
        } else {
            return cast.num;
        }
    }
}
