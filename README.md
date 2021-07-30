This is a shell simulation application written in C++.

Instructions:

To compile the application:
$ make

To run:
$ ./ESH BINARY_FILE_NAME

If the file does not exist, the file is created.  

A test file ("sample.bin") is provided in the application files.

Available commands:

pwd - Print the current working directory

ls - List the files and directories within the current working directory

cd <dirname> - Changes to the specified directory

cd .. - Change to the parent directory. Does nothing if current is root

mkdir <name> - Creates a directory with the specified name

cat <filename> - Prints the contents of the specified text file. Prints invalid if not a text file

createTextFile <filename>.<txt or p> - Creates a text file with the given name, and prompts for file contents

run <program> - Prints out "Running program <program>

start <program> - Prints out "Starting program <program>

step <program> - Prints out "Stepping in program <program>

