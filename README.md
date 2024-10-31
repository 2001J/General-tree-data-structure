# General Tree Data Structure Implementation

This project implements a general tree data structure in C, including nodes and leaves, with various functionalities such as insertion, deletion, search, and traversal. The project also includes a Makefile for building and testing the code.

## Files

- `tree.h`: Header file containing type definitions, macros, and function prototypes.
- `tree.c`: Source file implementing the tree data structure and its functionalities.
- `Makefile`: Makefile for building and testing the project.
- `.gitignore`: Git ignore file to exclude unnecessary files from version control.

## Features

- **Node and Leaf Creation**: Functions to create nodes and leaves.
- **Insertion**: Function to insert values based on keys.
- **Deletion**: Function to delete nodes/leaves.
- **Search**: Function to search through the tree.
- **Traversal**: In-order, pre-order, and post-order traversal functions.
- **Debugging**: Function to display the current state of the tree.
- **Memory Management**: Functions to free all dynamically allocated memory.

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- Make

### Cloning the Repository

To clone the repository, run the following command:

```sh
git clone <repository-url>
cd <repository-directory>
```

## Usage

### Building the Project

To build the project, run the following command:

```sh
make
```

### Running the Tests

To run the tests, use the following command:

```sh
make test
```

## Expected Output

When you run the tests, you should see the following output:

```
abc123
jane
<address1> <address2> //eg. 0x7f8b1b402010 0x7f8b1b402030
Found key 'alice' with value: password123
Key 'alice' not found after deletion
In-Order Traversal:
Node Path: /Users/login
Node Path: /Users
Node Path: /
Pre-Order Traversal:
Node Path: /
Node Path: /Users
Node Path: /Users/login
Post-Order Traversal:
Node Path: /Users/login
Node Path: /Users
Node Path: /
Debug Tree:
Node Path: /, Tag: 3
Node Path: /Users, Tag: 2
Node Path: /Users/login, Tag: 2
```

### Cleaning Up

To clean up the build files, use the following command:

```sh
make clean
```

## License

This project is licensed under the MIT License.

## Author

Joseph Paul Koyi
