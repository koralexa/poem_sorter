//
//  files_functions.cpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 22.09.2020.
//

#include "files_functions.hpp"
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>



//! Opens file with given parametrs
//!
//! @param [in] file_name file name to open
//! @param [in] access  access modifier for the file
//! @param [in] mode  create mode (in case O_CREATE was setted)
//!
//! @return file descriptor in case file was successfully opened, -1 otherwise
//!
//! @note In case of error prints eroor message in standart error stream
int OpenFile(const char * file_name, int access, unsigned mode) {
    int fd = open(file_name, access, mode);
    if (fd == -1) {
        switch (errno) {
            case ENOENT:
                std::cerr << "ERROR: File " << file_name << " doesn't exist." << std::endl;
                return -1;
            case EMFILE:
                std::cerr << "ERROR: You have too many opened files" << std::endl;
                return -1;
            default:
                std::cerr << "ERROR: can't open file " << file_name << std::endl;
                return -1;
        }
    }
    return fd;
}



//! Reads text from input file and writes all text to array of char
//!
//! @param [in] file file name to read from
//! @param [out] text  pointer to array of char to write the text
//!
//! @return number of lines in the text in case of successful reading, -1 otherwise
//!
//! @note All '\n' symbols will be replaced with '\0'
//! @note In case of error prints eroor message in standart error stream
long long ReadText(int file, char ** text) {
    if (file <= 0) {
        std::cerr << "ERROR: Wrong file descriptor for ReadText()." << std::endl;
        return -1;
    }
    if (*text != NULL) {
        std::cerr << "ERROR: Wrong pointer for ReadText()." << std::endl;
        return -1;
    }
    
    struct stat file_info;
    if (fstat(file, &file_info) != 0) {
        std::cerr << "ERROR: ReadText() can't get file info." << std::endl;
        return -1;
    }
    
    long long text_size = file_info.st_size + 2;
    *text = (char *)calloc(sizeof(char), text_size);
    if (*text == NULL) {
        std::cerr << "ERROR: ReadText() can't allocate memory for input text." << std::endl;
        return -1;
    }
    
    if (read(file, *text + 1, text_size) < 0) {
        std::cerr << "ERROR: ReadText() can't read input text." << std::endl;
        return -1;
    }
    
    long long i = 0;
    long long line_number = 0;
    for (i = 1; i < text_size; i++) {
        if ((*text)[i] == '\n') {
            (*text)[i] = '\0';
            line_number++;
        }
    }
    (*text)[text_size - 1] = '\0';
    (*text)[0] = '\0';
    
    if (line_number == 0) {
        std::cerr << "ERROR: Empty input file." << std::endl;
    }
    return line_number + 1;
}



//! Reads text from input file and writes all text to array of char
//!
//! @param [in] output_file file name to write to
//! @param [out] text array of pointers to char (strings for output)
//!
//! @return 0 in case of successful writing, -1 otherwise
//!
//! @note In case of error prints eroor message in standart error stream
int WriteText(int output_file, char ** text, long long lines_number) {
    if (output_file <= 0) {
        std::cerr << "ERROR: Wrong file descriptor for WriteText()." << std::endl;
        return -1;
    }
    if (text == NULL) {
        std::cerr << "ERROR: WriteText() got null pointer." << std::endl;
        return -1;
    }
    if (lines_number == 0) {
        std::cerr << "ERROR: WriteText() got zero lines number." << std::endl;
        return -1;
    }
    
    long long i = 0;
    char ret = '\n';
    for (i = 0; i < lines_number; i++) {
        if (write(output_file, text[i], strlen(text[i])) < 0) {
            std::cerr << "ERROR: WriteText() can't write to the file." << std::endl;
            return -1;
        }
        if (write(output_file, (char *)&ret, sizeof(char)) < 0) {
            std::cerr << "ERROR: WriteText() can't write to the file." << std::endl;
            return -1;
        }
    }
    return 0;
}
