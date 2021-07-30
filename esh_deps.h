#ifndef DISK
#define DISK

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;
// int to char[4] typecast
typedef struct {
    union {
        int num;
        char str[4];
    };
} TypeCastInt;

// directory entry
typedef struct {
    int  starts_at;
    int  size;
    char type;
    int  parent;
    char name[19];
} directory_entry;

typedef struct {
    union {
        directory_entry entry;
        char str[32];
    };
} TypeCastEntry;

const int kBlockSize_g = pow(2, 9);
const int kOneMiB_g = pow(2, 20);
const int MAX_FILE_SIZE = pow(2, 19);

class ESH {
 private:
    const int kBlockSize = kBlockSize_g;
    std::string kDiskTitle;
    int kDiskSize;
    int kNumberOfBlocks;
    int reserved_blocks;
    int current_dir;
    int parent_dir;
    const int blocks_for_dir = 2;
    void create(bool already_exists = false);
    int find_blocks(int blocks_needed, std::vector<int> &blocks_free);

 public:
    ESH(std::string title = "Disk.bin", int disk_size = kOneMiB_g, bool already_exists = false);
    enum Status {free = 0, BUSY, RESERVED, NOT_FOUND, dir_entry, END};
    const std::vector<std::string> statusMsg {
        "free", "BUSY", "RESERVED", "NOT_FOUND", "dir_entry", "END"
    };
    // prototypes
    int get_status(int block_no) const;
    int update_status(int block_no, int x);
    void read_block(int block_no, char *buffer) const;
    void write_block(int block_no, char *buffer);
    int create_file(const char *title, const char *source_file);
    int read_file(const char *title);
    int create_directory(const char *title);
    int change_directory(const char *title);
    int print_working_directory();
    void list_dir_contents();
};

std::vector<std::string> split(const std::string &s, const char delimitter);


int handle_input(ESH &disk);

#endif
