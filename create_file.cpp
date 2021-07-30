#include "esh_deps.h"
/*
 * Purpose: Create a new text file
 * Parameters: title, source_file: title of the file and source file to read
 * from
 * Precondition: File doesn't already exist
 * Postcondition: A new file is created and saved to binary filesystem
 */
int ESH::create_file(const char *title, const char *source_file) {

    TypeCastEntry entry;
    if (strlen(title) == 0) {
        std::cout << "Enter filename>";
        std::cin >> entry.entry.name;
        std::cin.ignore(32767, '\n');
    } else {
        strcpy(entry.entry.name, title);
    }

    // default parent is root
    entry.entry.parent = current_dir;

    // set the type to file
    entry.entry.type = 'F';

    // read in contents and set the size
    char file_content[MAX_FILE_SIZE];
    if (strlen(source_file) == 0) {
        std::cout << "Enter file contents>";
        std::cin.getline(file_content, sizeof(file_content));
        entry.entry.size = strlen(file_content);
    } else {
        std::ifstream fsrc;
        fsrc.open(source_file, std::ios::binary | std::ios::in);
        fsrc.read(file_content, MAX_FILE_SIZE);
        fsrc.close();
        fsrc.open(source_file, std::ios::binary | std::ios::in | std::ios::ate);
        entry.entry.size = fsrc.tellg();
        fsrc.close();
    }

    if (entry.entry.size < 0) {
        return 1;
    }


    // locate free blocks to write to
    int blocks_needed = (entry.entry.size - 1) / kBlockSize + 1;
    std::vector<int> blocks_free(blocks_needed);
    if (find_blocks(blocks_needed, blocks_free) == 1) {
        return 1;
    };

    entry.entry.starts_at = blocks_free[0];

    char buffer[kBlockSize];
    bool positionFound = false;
    int byteforEntry = 0;
    int blockForEntry = 0;
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
                std::cout << "File with same name already exists in directory."
                 << std::endl;
                 return 1;
            }
        }
        if (positionFound) break;
    }
    if (!positionFound) {
        std::cout << "Cannot contain more than "
                  << blocks_for_dir*16
                  << " entries"
                  << std::endl;
        return 1;
    }
    // update buffer
    for (int i = byteforEntry, j = 0; j < 32; ++i, ++j) {
        buffer[i] = entry.str[j];
    }
    // write the file entry
    write_block(current_dir + blockForEntry, buffer);
    update_status(current_dir + blockForEntry, dir_entry);

    // write data and update block status
    for (int i = 0; i < blocks_needed; ++i) {
        for (int j = 0; j < kBlockSize; ++j) {
            buffer[j] = file_content[kBlockSize*i + j];
        }
        write_block(blocks_free[i], buffer);
        update_status(blocks_free[i],
            (i != blocks_needed-1) ? blocks_free[i+1] : 1);
    }
    return 0;
}
