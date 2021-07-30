#include "esh_deps.h"
/*
 * Purpose: Main driver for the application.
 * Parameters: Command line arguments
 * Precondition: None
 * Postcondition: Binary file is opened/created and starts user input
 */
int main(int argc, char const *argv[]) {
    std::string file_system_name;
    int disk_size_bytes;

    // get the name of the binary file to be used
    if (argc > 1 && argv[1]) {
        file_system_name = argv[1];
    }

    // check if the binary file exists and get its size
    bool already_exists = false;
    std::fstream ifile;
    ifile.open(file_system_name, std::ios::binary | std::ios::in | std::ios::ate);
    disk_size_bytes = ifile.tellg();
    ifile.close();
    already_exists = (disk_size_bytes > -1);

    // set the file size if it doesn't already exist
    // note: using a set file size rather than dynamic to practice using
    // a limited amount of space in to program.
    if (!already_exists) {
        int disk_size_mb = 2;
        disk_size_bytes = kOneMiB_g*disk_size_mb;
    }

    // initialize disk
    ESH disk(file_system_name, disk_size_bytes, already_exists);
    std::cout << "Welcome to ESH. Type 'help' to view available commands." << std::endl;
    // starting taking in input from the user
    int response = handle_input(disk);
    while (response != 1) {
        response = handle_input(disk);
    }
    return 0;
}
