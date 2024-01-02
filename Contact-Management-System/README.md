# Contact Management System

The Contact Management System is a C++ project that implements a contact management application using various data structures such as lists, binary search trees, and vectors. This system allows users to manage their contacts efficiently, providing functionalities such as adding, editing, removing, searching, marking favorites, and exporting/importing contacts.

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Data Structures](#data-structures)
- [Classes and Methods](#classes-and-methods)
- [Contributing](#contributing)


## Overview

The Contact Management System is designed to help users organize and manage their contacts effectively. It provides a command-line interface with a set of commands to perform various operations on contacts, including adding, editing, removing, and searching for contacts. The application uses lists, binary search trees, and vectors to efficiently store and manipulate contact data.

## Installation

To use the Contact Management System, follow these steps:

1. Clone the repository to your local machine.
2. Compile the C++ source code using your preferred compiler.
3. Run the executable file.

## Usage

The Contact Management System provides a set of commands that users can use to interact with the application. The following commands are available:

```cpp
void listCommands()
{
    "import <path>      :Import contacts from a CSV file"
    "export <path>      :Export contacts to a CSV file"
    "add                :Add a new contact"
    "edit <key>         :Update a contact's details"
    "remove <key>       :Delete a contact"
    "searchFor <key>    :Search for a contact"
    "markFav <key>      :Mark as favourite"
    "unmarkFav <key>    :Unmark as favourite"
    "printASC           :Print contacts in ascending order"
    "printDES           :Print contacts in descending order"
    "printFav           :Print all favourite contacts"
    "help               :Display the available commands"
    "exit               :Exit the program"
}
```

# Features

- Add, edit, and remove contacts.
- Search for contacts by key.
- Mark or unmark contacts as favorites.
- Print contacts in ascending or descending order.
- Print all favorite contacts.
- Import and export contacts to/from a CSV file.

## Data Structures

The Contact Management System utilizes the following data structures:

- **Binary Search Tree (BST):** Used for efficiently storing and managing contacts in a hierarchical structure.
- **Vector:** Employed to store a dynamic array of contacts, providing flexibility and efficient access.
- **List:** Implemented for managing and manipulating the command history in a sequential manner.

## Classes and Methods

### `ContactBST`

The `ContactBST` class represents a Binary Search Tree for storing contacts. It provides methods for adding, updating, removing, searching, marking favorites, and printing contacts in different orders. The class also includes methods for importing and exporting contacts to/from a CSV file.

### `MyVector`

The `MyVector` class implements a dynamic array for storing contacts. It includes methods for adding, inserting, erasing, and accessing elements, as well as utility methods such as resizing and displaying the vector.

### `Contact`

The `Contact` class represents a single contact, storing information such as first name, last name, email, phone number, city, country, and favorite status. It is used by the `ContactBST` class to create and manage contacts within the binary search tree.

## Contributing

Contributions to the Contact Management System are welcome. Feel free to open issues, submit feature requests, or contribute directly by creating pull requests.

