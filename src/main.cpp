#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

bool isBuiltin(const std::string& command) {
    return command == "exit" || command == "echo" || command == "type";
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";

        std::string input;
        std::getline(std::cin, input);

        if (std::cin.eof()) {
            break;
        }
        
        std::stringstream ss(input);

        std::string command;
        std::string argument;

        ss >> command;
        ss >> argument;

        // Empty input
        if (command.empty()) {
            continue;
        }

        // exit
        if (command == "exit") {
            break;
        }

        // echo
        else if (command == "echo") {
            std::string rest;

            std::getline(ss, rest);

            // Remove the leading space
            if (!rest.empty() && rest[0] == ' ') {
                rest.erase(0, 1);
            }

            std::cout << rest << std::endl;
        }

        // type
        else if (command == "type") {
            if (isBuiltin(argument)) {
                std::cout << argument << " is a shell builtin" << std::endl;
                continue;
            }

            // Get PATH
            const char* pathEnvironment = std::getenv("PATH");

            if (pathEnvironment == nullptr) {
                std::cout << argument << ": not found" << std::endl;
                continue;
            }

            std::string path(pathEnvironment);

            std::stringstream pathStream(path);

            std::string directory;
            bool found = false;

            while (std::getline(pathStream, directory, ':')) {

                // Handle empty PATH entry
                if (directory.empty()) {
                    directory = ".";
                }

                std::string fullPath =
                    directory + "/" + argument;

                // Check if executable
                if (access(fullPath.c_str(), X_OK) == 0) {
                    std::cout << argument<< " is "<< fullPath<< std::endl;

                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << argument << ": not found"<< std::endl;
            }
        }

        else {
            std::cout << input << ": command not found" << std::endl;
        }
    }

    return 0;
}