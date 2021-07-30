#include "esh_deps.h"

/*
 * Purpose: Writes data into blocks of memory
 * Parameters: block_no: the block to write data to
               buffer: buffer to write from
 * Precondition: None.
 * Postcondition: Data is written to the block if the block is
 * empty (free)
 */
void ESH::write_block(int block_no, char* buffer) {

    int status = get_status(block_no);
    if (status == RESERVED) {
        std::cout << "It is a reserved block" << std::endl;
        return;
    } else if (status == NOT_FOUND) {
        std::cout << "Block does not exist." << std::endl;
        return;
    } else {
        std::ofstream fp;
        fp.open(kDiskTitle, std::ios::binary | std::ios::in | std::ios::out);
        fp.seekp(block_no*kBlockSize);
        fp.write(buffer, kBlockSize);
        fp.close();
    }
}
