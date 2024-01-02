# Flight Ticket Management System

Welcome to the Flight Ticket Management System repository! This C++ project focuses on efficient flight ticket management using data structures and provides a command-line interface for various operations. The system reads and stores data from a CSV file, uses a hash table for efficient retrieval, and offers functionality to manage flight tickets.

## Table of Contents

- [Features](#features)
  - [Data Storage and Retrieval](#1-data-storage-and-retrieval)
  - [Command-Line Interface](#2-command-line-interface)
  - [Flight Ticket Operations](#3-flight-ticket-operations)
  - [Comprehensive Data Structure](#4-comprehensive-data-structure)
  - [File Handling](#5-file-handling)
  - [Error Handling](#6-error-handling)
  - [Professional Documentation](#7-professional-documentation)
- [Usage](#usage)

## Features

### 1. Data Storage and Retrieval

- **CSV Import and Export:** Import flight tickets from a CSV file and export them back in ascending order.
  
- **Hash Table:** Utilizes a hash table to efficiently store and retrieve flight ticket details.

### 2. Command-Line Interface

- **User-Friendly Commands:** A user-friendly command-line interface with commands like `add`, `delete`, `find`, and more.

- **Collision Tracking:** Provides the ability to count and display the number of collisions in the hash table.

### 3. Flight Ticket Operations

- **Add and Delete:** Add new flight tickets to the system and delete existing ones.

- **Find and Display:** Find and display flight tickets based on the flight number and company name.

- **All-in-Day Display:** Display all flight tickets for a given date.

### 4. Comprehensive Data Structure

- **Custom List Class:** Implements a custom list class to handle data efficiently.

- **Node Class:** Manages individual nodes with functionalities like add, remove, and display.

### 5. File Handling

- **CSV Import/Export:** Load flight tickets from and export them to CSV files, maintaining data integrity.

### 6. Error Handling

- **Input Validation:** Includes input validation to ensure correct data entry.

### 7. Professional Documentation

- **Comments and Documentation:** Well-commented code for better understanding and easy maintenance.

## Usage

To get started, clone the repository and compile the code using a C++ compiler. Execute the compiled binary and use the provided commands to interact with the Flight Ticket Management System.

```bash
$ g++ main.cpp -o FlightTicketSystem
$ ./FlightTicketSystem
```