# vs-cpp

## Overview

This repository contains various C++ projects, including implementations of data structures, sorting algorithms, and other coding exercises.

## Projects

- **RBTree**: Red-Black Tree implementation.
- **OpenTable**: Open addressing hash table implementation.
- **vector**: C++14 conforming std::vector-like template.

### Static Array Allocator

The static array allocator used in this repository is particularly suited for mission-critical embedded systems. It provides dynamic memory allocation semantics with the safety and predictability of a statically allocated array. This approach minimizes the risks of fragmentation, memory leaks, and heap exhaustion, which are critical concerns in embedded environments where reliability is paramount.

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC, Clang, MSVC)
- CMake (optional, for building the projects)

### Building the Projects

1. Clone the repository:
    ```sh
    git clone https://github.com/stevemac321/vs-cpp.git
    cd vs-cpp
    ```

2. Build using your preferred method (e.g., using a CMake file, or directly with a compiler).

### Running the Projects
-Load in Visual Studio, open vs-cpp.sln or any of the project files
OR
- Each project contains its own makefile. Navigate to the project directory and run make.
    ```sh
    cd RBTree
    make
    ./RBTree
    ```

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.
