#include "esh_deps.h"
/*
 * Purpose:
 * Parameters:
 * Precondition:
 * Postcondition:
 */
int ESH::find_blocks(int blocks_needed, std::vector<int> &blocks_free) {
    int blocksFound = 0;
    int block = reserved_blocks + blocks_for_dir;
    while (blocksFound < blocks_needed) {
        int status = get_status(block);
        if (status == free) {
            // add block to usable list
            blocks_free[blocksFound++] = block;
        } else if (status == NOT_FOUND) {
            // look in deleted blocks now
            std::cout << "No more free blocks." << std::endl;
            break;
        }
        ++block;
    }
    // look for available blocks that are marked deleted
    block = reserved_blocks + blocks_for_dir;
    while (blocksFound < blocks_needed) {
        int status = get_status(block);
        if (status < 0) {
            blocks_free[blocksFound++] = block;
        } else if (status == NOT_FOUND) {
            std::cout << "Not enough space in disk!" << std::endl;
            return 1;
        }
        ++block;
    }
    return 0;
}
