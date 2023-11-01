#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../types.h"
#include "../util.h"
#include "io.h"

// Define a constant for the size of data chunks to be read from the file.
#define IO_READ_CHUNK_SIZE 2097152

// Define error messages for file input/output errors.
#define IO_REEAD_ERROR_GENERAL "Error reading file: %s. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read file: %s\n"

// Define a function to read a file and return its contents as a 'File' struct.
File io_file_read(const char *path)
{
    // Initialize a 'File' struct with a default 'is_valid' value of 'false'.
    File file = { .is_valid = false };

    // Attempt to open the file for reading in binary mode.
    FILE *fp = fopen(path, "rb");

    // Check for errors while opening the file.
    if (!fp || ferror(fp))
    {
        // If there was an error, set 'file.is_valid' to 'false' and return an error message.
        ERROR_RETURN(file, IO_REEAD_ERROR_GENERAL, path, errno);
    }

    // Initialize variables for file reading and memory allocation.
    char *data = NULL;
    char *tmp;
    size_t used = 0;
    size_t size = 0;
    size_t n;

    // Continue reading the file in chunks until the end of the file is reached.
    while (true)
    {
        // Check if there is enough space in the buffer for the next chunk of data.
        if (used + IO_READ_CHUNK_SIZE + 1 > size)
        {
            // Calculate the new size required and handle potential memory allocation errors.
            size = used + IO_READ_CHUNK_SIZE + 1;
            if (size <= used)
            {
                free(data);
                ERROR_RETURN(file, "Input file too large: %s\n", path);
            }

            tmp = realloc(data, size);
            if (!tmp)
            {
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
            }

            data = tmp;
        }

        // Read a chunk of data from the file into the buffer.
        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);

        // Break the loop when the end of the file is reached.
        if (n == 0)
            break;

        // Update the 'used' counter to keep track of the amount of data read.
        used += n;
    }

    // Check for errors during the file read operation.
    if (ferror(fp))
    {
        free(data);
        ERROR_RETURN(file, IO_REEAD_ERROR_GENERAL, path, errno);
    }

    // Attempt to resize the data buffer to its final size.
    tmp = realloc(data, used + 1);
    if (!tmp)
    {
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
    }

    // Update the 'data' pointer and set the last character to null-terminate the string.
    data = tmp;
    data[used] = 0;

    // Fill in the 'File' struct with the read data and mark it as valid.
    file.data = data;
    file.len = used;
    file.is_valid = true;

    // Return the 'File' struct containing the file data.
    return file;
}

int io_file_write(void *buffer, size_t size, const char *path)
{
    FILE *fp = fopen(path, "wb");
    if (!fp || ferror(fp))
    {
        ERROR_RETURN(1, "Cannot write file: %s,\n", path);
    }
    
    size_t chunks_written = fwrite(buffer, size, 1, fp);

    fclose(fp);

    if (chunks_written != 1) 
    {
        ERROR_RETURN(1, "Write error. " "Expected 1 chunk, got %zu. \n", chunks_written);
    }

    return 0;
}
