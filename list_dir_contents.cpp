#include "esh_deps.h"
/*
 * Purpose: Prints all the files and directories contained in the current dir
 * Parameters: None.
 * Precondition: None.
 * Postcondition: Prints all directories and files in the order they were
 * created
 */
void ESH::list_dir_contents() {

    char buffer[kBlockSize];
    TypeCastEntry entry;
//	std::cout << "Directory Name: " << current_dir << endl;
    for (int i = 0; i < blocks_for_dir; ++i) {
        read_block(current_dir + i, buffer);
        for (int j = 0; j < kBlockSize; j += 32) {
            for (int k = 0; k < 32; ++k) {
                entry.str[k] = buffer[j+k];
            }
                if (entry.entry.type == 'F') {
                    std::cout << "Filename: " << std::left <<
                    entry.entry.name << std::right << " Type: Text file"<< std::endl;
                } else if ((entry.entry.type == 'D')) {
                    std::cout << std::left <<
                    "Filename: " << entry.entry.name << 
					" Type: Directory" << std::endl;
                }
        }
    }
}
