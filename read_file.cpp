#include "esh_deps.h"
/*
 * Purpose: Reads a particular text file
 * Parameters: title: Title of the file to read
 * Precondition: File exists.
 * Postcondition: Returns the files contents.
 */
int ESH::read_file(const char *title) {

    TypeCastEntry entry;
    strcpy(entry.entry.name, title);

    entry.entry.starts_at = 0;

    char buffer[kBlockSize];
    TypeCastEntry test;
    for (int i = 0; i < blocks_for_dir; ++i) {
        read_block(current_dir + i, buffer);
        for (int j = 0; j < kBlockSize; j += 32) {
            for (int k = 0; k < 32; ++k) {
                test.str[k] = buffer[j+k];
            }
            if (strcmp(test.entry.name, entry.entry.name) == 0) {
                entry.entry.starts_at = test.entry.starts_at;
                entry.entry.size = test.entry.size;
                entry.entry.parent = test.entry.parent;
                if (test.entry.type != 'F') return 1;
                break;
            }
        }
        if (entry.entry.starts_at != 0) break;
    }
    if (entry.entry.starts_at == 0) {
        std::cout << "file not found" << std::endl;
        return 1;
    } else {
        // read file content
        std::cout << "Text file contents:" << std::endl;

        int sec = entry.entry.starts_at;
        while (sec != 1) {
            read_block(sec, buffer);
            for (int i = 0; i < kBlockSize; ++i) {
                std::cout << buffer[i];
            }
            sec = get_status(sec);
        }
        std::cout << std::endl;
    }
    return 0;
}
