# C++ Unix Shell

A simple Unix-like command-line shell built in C++ as part of the [CodeCrafters Build Your Own Shell](https://codecrafters.io) challenge.

The project implements basic shell functionality, including built-in commands, executable lookup through `PATH`, and execution of external programs with arguments.

## Features

- **Built-in commands**
  - `echo` — Prints text to standard output.
  - `exit` — Exits the shell.
  - `pwd` — Prints the current working directory.
  - `type` — Identifies built-in commands and locates executables in `PATH`.
- **External command execution** — Runs programs such as `ls` and `cat`.
- **Command-line arguments** — Supports passing arguments to external programs.
- **PATH lookup** — Searches directories in the `PATH` environment variable for executables.
- **Process management** — Uses `fork()`, `execv()`, and `waitpid()` to execute and manage external processes.

## Tech Stack

- C++
- Linux
- POSIX system calls
- CMake

## Getting Started

### Prerequisites

- Linux or WSL (Ubuntu)
- GCC / G++
- CMake

### Build

Clone the repository:

```bash
git clone https://github.com/aditank/codecrafters-shell-cpp.git
cd codecrafters-shell-cpp
```

Compile the shell:

```bash
g++ -std=c++17 -Wall -Wextra src/main.cpp -o shell
```

### Run

```bash
./shell
```

## Usage

Once the shell starts, enter commands at the prompt.

```text
$ pwd
/home/user/codecrafters-shell-cpp

$ echo Hello World
Hello World

$ type ls
ls is /usr/bin/ls

$ ls -l
total  ...

$ exit
```

The output of commands such as `pwd` and `ls` depends on your environment.

## Project Structure

```text
codecrafters-shell-cpp/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Learning Objectives

This project provides practical experience with:

- C++ programming and standard library features
- Linux command-line environments
- Process creation and execution
- Environment variables and executable lookup
- Basic shell architecture

## Current Limitations

- Quoted arguments and advanced shell parsing are not yet supported.
- Pipes and input/output redirection are not yet implemented.
- Command history is not yet implemented.

## Future Improvements

- Support quoted arguments and escape sequences
- Implement pipes and I/O redirection
- Add command history
- Improve error handling and command parsing

## Acknowledgments

Built while following the [CodeCrafters Build Your Own Shell](https://codecrafters.io) challenge.
