#include "esh_deps.h"
/*
 * Purpose: Splits string input to separate commands and arguments
 * Parameters: s, delimitter: String given and associated delimtter
 * Precondition: String passed is not empty
 * Postcondition: Returns a verctor of strings, separated at delimitter
 */
std::vector<std::string> split(const std::string &s, const char delimitter) {

    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> vector_values;
    while (getline(ss, item, delimitter)) {
        vector_values.push_back(item);
    }
    return vector_values;
}
