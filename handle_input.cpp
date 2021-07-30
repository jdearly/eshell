#include "esh_deps.h"
/*
 * Purpose: Creates command line interface for user interaction
 * Parameters: Reference to the binary file
 * Precondition: File exists
 * Postcondition: Loops until quit manually
 */
int handle_input(ESH &disk) {

    std::string command;
    std::cout << "EnterCommand> ";
    getline(std::cin, command);
    if (command.empty()) return 1;

    // separate command and the arguments
    std::vector<std::string> vector_values;
    vector_values = split(command, ' ');
    std::string fun = vector_values[0];
    std::string arg = "";
    if (vector_values.size() > 1) {
        arg = vector_values[1];
    }

    std::string arg2 = "";
    if (vector_values.size() > 2) {
        arg2 = vector_values[2];
    }

    // enumerated type to allow the following switch statement
    // couldn't switch on just string input
    enum Choice {
		    HELP,
        QUIT,
        NEW_FILE,
        CAT,
        MKDIR,
        CD,
        PWD,
        LS,
        START,
        RUN,
        STEP,
        END
    };
    std::string CHOICES[] = {
		    "help",
        "quit",
        "createTextFile",
        "cat",
        "mkdir",
        "cd",
        "pwd",
        "ls",
        "start",
        "run",
        "step",
        ""
    };

    Choice selected = END;
    for (int i = 0; i < END; ++i) {
        if (CHOICES[i] == fun) {
            selected = static_cast<Choice>(i);
            break;
        }
    }

    int block;

    // Switch statement to handle the user inputs
    switch (selected) {
		case HELP: {
            ifstream helpFile;
            helpFile.open("help.txt", ios::in | ios::ate);
            int helpFileSize = helpFile.tellg();
            char helpMsg[helpFileSize];
            helpFile.seekg(0);
            helpFile.read(helpMsg, helpFileSize);
            helpFile.close();
            cout << helpMsg << endl;
            break;
        }
		case NEW_FILE: {
            disk.create_file(arg.c_str(), arg2.c_str());
            break;
        }
        case CAT: {
            if (arg.empty()) {
                std::cout << "cat: missing operand" << std::endl;
                return 0;
            }
            else if (arg.find(".txt") != std::string::npos) {
              disk.read_file(arg.c_str());
            }
            else {
            std::cout << "Invalid file type" << std::endl;
          }
            break;
        }
        case MKDIR: {
            if (arg.empty()) {
                std::cout << "mkdir: missing operand" << std::endl;
                return 0;
            }
            disk.create_directory(arg.c_str());
            break;
        }
        case CD: {
            if (arg.empty()) {
                std::cout << "cd: missing operand" << std::endl;
                return 0;
            }
            std::vector<std::string> dir = split(arg, '/');
            for (int i = 0; i < dir.size(); ++i) {
                disk.change_directory(dir[i].c_str());
            }
            break;
        }
        case PWD:
            disk.print_working_directory();
            break;
        case LS:
            disk.list_dir_contents();
            break;
        case QUIT:
            return 1;
		    case START:
			      std::cout << "Starting program " << arg << std::endl;
			      break;
        case RUN:
    			  std::cout << "Running program " << arg << std::endl;
    			  break;
        case STEP:
        		std::cout << "Stepping in program " << arg << std::endl;
        		break;
        default:
            std::cout << "ESH: command not found: " << fun << std::endl;
            return 0;
    }
    return 0;
}
