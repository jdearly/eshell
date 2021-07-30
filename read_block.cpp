#include "esh_deps.h"

/*
 * Purpose: Reads a block from the file
 * Parameters: block_no, buffer: block number to read and character buffer
 * Precondition: None
 * Postcondition: Prints block data if it exists and is not reserved
 */
void ESH::read_block(int block_no, char *buffer) const {

    int status = get_status(block_no);
    if (status == RESERVED) {
        std::cout << "Reserved block." << std::endl;
    }
    std::ifstream ifile;
    ifile.open(kDiskTitle, std::ios::binary | std::ios::in);
    int byte_offset = block_no*kBlockSize;
    ifile.seekg(byte_offset);
    ifile.read(buffer, kBlockSize);
    ifile.close();

}
