#include "esh_deps.h"
/*
 * Purpose: Creates a new directory within current working directory
 * Parameters: title: title of the new directory
 * Precondition: Directory does not already exist
 * Postcondition: A new directory is created and saved in memory
 */
int ESH::create_directory(const char *title) {
    // to ensure another root is not created
    if (strcmp(title, "/root") == 0) {
        return 1;
    }
    TypeCastEntry entry;
    strcpy(entry.entry.name, title);
    entry.entry.type = 'D';
    entry.entry.parent = parent_dir;
    entry.entry.size = 0;


    // look for free space and reserve space for this directory's entries
    std::vector<int> blocks_free;
    int sec = reserved_blocks + blocks_for_dir;
    while (blocks_free.size() != blocks_for_dir) {
        int status = get_status(sec);
        if (status == free) {
            blocks_free.push_back(sec);
        } else {
            blocks_free.clear();
        }
        if (status == NOT_FOUND) {
            std::cout << "Not enough space" << std::endl;
            return 1;
        }
        ++sec;
    }

    entry.entry.starts_at = blocks_free[0];
    // reserve space for the new directory
    for (int i = 0; i < blocks_for_dir; ++i) {
        update_status(blocks_free[i], dir_entry);
    }

    // locate position for the file entry
    bool positionFound = false;
    int byteforEntry = 0;
    int blockForEntry = 0;
    char buffer[kBlockSize];
    for (int s = 0; s < blocks_for_dir; ++s) {
        read_block(current_dir + s, buffer);
        for (int b = 0; b < kBlockSize; b += 32) {
            TypeCastEntry test;
            for (int k = 0; k < 32; ++k) {
                test.str[k] = buffer[b+k];
            }
            if (strlen(test.entry.name) == 0) {
                positionFound = true;
                blockForEntry = s;
                byteforEntry = b;
                break;
            } else if (strcmp(test.entry.name, entry.entry.name) == 0) {
                std::cout << "Directory '" << entry.entry.name
                 << "' already exists."
                 << std::endl;
                 return 1;
            }
        }
        if (positionFound) break;
    }

    // update the buffer
    for (int i = byteforEntry, j = 0; j < 32; ++i, ++j) {
        buffer[i] = entry.str[j];
    }

    write_block(current_dir + blockForEntry, buffer);
    update_status(current_dir + blockForEntry, dir_entry);

    return 0;
}
