/**
 * @brief File I/O Utility Library
 *
 * This code defines a simple utility library for file input and output (I/O).
 * It provides two key functions:
 * 1. io_file_read(const char *path) reads the contents of a file specified by its path and returns a File structure.
 * 2. io_file_write(void *buffer, size_t size, const char *path) writes data from a buffer to a file.
 * The library enables easy file read and write operations with error checking.
 */
#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct file 
{
    char *data;
    size_t len;
    bool is_valid;
} File;

File io_file_read(const char *path);
int io_file_write(void *buffer, size_t size, const char *path);