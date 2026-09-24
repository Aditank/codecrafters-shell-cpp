#include <iostream>
#include <unistd.h>

int main() {

    std::string path = "/usr/bin/ls";

    if (access(path.c_str(), X_OK) == 0) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}