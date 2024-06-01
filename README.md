# Enterpret_Assignment
# Cache Implementation with LIFO, FIFO, and LRU Eviction Policies

## Overview

This project implements a thread-safe cache with three eviction policies:
- **FIFO (First In First Out)**
- **LRU (Least Recently Used)**
- **LIFO (Last In First Out)**

The cache is designed to handle concurrent access and allows users to define custom eviction policies by extending the base `Cache` class.

## Features

- **Eviction Policies**: Supports LIFO, FIFO, and LRU eviction policies.
- **Thread Safety**: Uses shared mutexes to ensure safe concurrent access.
- **Custom Eviction Policies**: Easily extendable to add new eviction policies.

### Compiling

Ensure you have a C++ compiler installed. To compile the main program, use the following command:

```sh
g++ -o cache_main main.cpp -std=c++17 -pthread
