
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

bool isBuiltin(const std::string& command) {
    return command == "exit" ||
           command == "echo" ||
           command == "type";
}

// Search PATH and return the executable's full path.
// Return an empty string if it isn't found.
std::string findExecutable(const std::string& command) {
    const char* env = std::getenv("PATH");

    if (env == nullptr) {
        return "";
    }

    std::stringstream paths(env);
    std::string directory;

    while (std::getline(paths, directory, ':')) {
        if (directory.empty()) {
            directory = ".";
        }

        std::string fullPath = directory + "/" + command;

        if (access(fullPath.c_str(), X_OK) == 0) {
            return fullPath;
        }
    }

    return "";
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";

        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }

        // Split input into words.
        std::stringstream ss(input);
        std::vector<std::string> args;
        std::string word;

        while (ss >> word) {
            args.push_back(word);
        }

        if (args.empty()) {
            continue;
        }

        std::string command = args[0];

        // Builtin: exit
        if (command == "exit") {
            break;
        }

        // Builtin: echo
        else if (command == "echo") {
            for (size_t i = 1; i < args.size(); i++) {
                if (i > 1) {
                    std::cout << " ";
                }
                std::cout << args[i];
            }
            std::cout << std::endl;
        }

        // Builtin: type
        else if (command == "type") {
            if (args.size() < 2) {
                continue;
            }

            std::string name = args[1];

            if (isBuiltin(name)) {
                std::cout << name
                          << " is a shell builtin"
                          << std::endl;
            } else {
                std::string path = findExecutable(name);

                if (!path.empty()) {
                    std::cout << name << " is " << path
                              << std::endl;
                } else {
                    std::cout << name << ": not found"
                              << std::endl;
                }
            }
        }

        // External command
        else {
            std::string path = findExecutable(command);

            if (path.empty()) {
                std::cout << command
                          << ": command not found"
                          << std::endl;
                continue;
            }

            pid_t pid = fork();

            if (pid == -1) {
                std::cerr << "fork failed" << std::endl;
                continue;
            }

            if (pid == 0) {
                // Child process
                std::vector<char*> argv;

                for (auto& arg : args) {
                    argv.push_back(arg.data());
                }

                argv.push_back(nullptr);

                execv(path.c_str(), argv.data());

                // Only reached if execv fails.
                std::cerr << "Execution failed" << std::endl;
                _exit(1);
            } else {
                // Parent process
                waitpid(pid, nullptr, 0);
            }
        }
    }

    return 0;
}
