//
//  main.cpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 22.09.2020.
//

#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef DEBUG
#include "testing_functions.hpp"
#endif

#include "files_functions.hpp"
#include "sorting_functions.hpp"

int main(int argc, const char * argv[]) {
    
#ifdef DEBUG
    TestCompareLinesBeginnings("aaa", "bbb", 1);
    TestCompareLinesBeginnings("a,aa", "aaa", 0);
    TestCompareLinesBeginnings("Abc", "abc", 0);
    TestCompareLinesBeginnings("bbbb", "bbbb", 0);
    TestCompareLinesBeginnings("b", "A", -1);
    
    TestCompareLinesEnds("aaa", "bbb", 1);
    TestCompareLinesEnds("ksjlfwemla", "lsjjbwke", 1);
    TestCompareLinesEnds("sjdlsB", "aa", -1);
    TestCompareLinesEnds("bbb", "bb,b", 0);
    TestCompareLinesEnds("BBB", "bbb", 0);
    
    char ** input = (char**)calloc(sizeof(char*), 5);
    input[0] = (char *)&"ccaa";
    input[1] = (char *)&"bbbbbb";
    input[2] = (char *)&"dddzzz";
    input[3] = (char *)&"hhhhmmm";
    input[4] = (char *)&"aaalll";
    
    char ** answer1 = (char**)calloc(sizeof(char*), 5);
    char ** answer2 = (char**)calloc(sizeof(char*), 5);
    
    answer1[0] = input[4];
    answer1[1] = input[1];
    answer1[2] = input[0];
    answer1[3] = input[2];
    answer1[4] = input[3];
    
    answer2[0] = input[0];
    answer2[1] = input[1];
    answer2[2] = input[4];
    answer2[3] = input[3];
    answer2[4] = input[2];
    
    TestQuickSort(input, 0, 4, "begin", answer1);
    TestQuickSort(input, 0, 4, "end", answer2);
    
    free(input);
    free(answer1);
    free(answer2);
    
    return 0;
#endif
    
    if (argc != 4) {
        std::cout << "Wrong number of arguments! Please, try again:" << std::endl;
        std::cout << "1st parametr: input file name" << std::endl;
        std::cout << "2nd parametr: output file name for soting by beginnings of lines" << std::endl;
        std::cout << "3rd parametr: output file name for soting by ends of lines" << std::endl;
        return 1;
    }
    
    int input_file = OpenFile(argv[1], O_RDONLY, 0);
    if (input_file < 0) {
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    int output_file_beginnings = OpenFile(argv[2], O_WRONLY|O_TRUNC|O_CREAT, S_IWRITE|S_IREAD);
    if (output_file_beginnings < 0) {
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    int output_file_ends = OpenFile(argv[3], O_WRONLY|O_TRUNC|O_CREAT, S_IWRITE|S_IREAD);
    if (output_file_ends < 0) {
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    char * original_text = NULL;
    long long lines_number = ReadText(input_file, &original_text);
    close(input_file);
    if (lines_number <= 0) {
        close(output_file_beginnings);
        close(output_file_ends);
        if (original_text != NULL) {
            free(original_text);
        }
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    char ** sorted_text_beginnings = NULL;
    char ** sorted_text_ends = NULL;
    if (InitializeSortedArrays(&sorted_text_beginnings, &sorted_text_ends,
                               original_text, lines_number) != 0) {
        close(output_file_beginnings);
        close(output_file_ends);
        free(original_text);
        if (sorted_text_beginnings != NULL) {
            free(sorted_text_beginnings);
        }
        if (sorted_text_beginnings != NULL) {
            free(sorted_text_beginnings);
        }
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    if (SortText(original_text, sorted_text_beginnings, lines_number, CompareLinesBeginnings) != 0) {
        close(output_file_beginnings);
        close(output_file_ends);
        free(original_text);
        free(sorted_text_beginnings);
        free(sorted_text_ends);
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    if (SortText(original_text, sorted_text_ends, lines_number, CompareLinesEnds) != 0) {
        close(output_file_ends);
        close(output_file_beginnings);
        free(original_text);
        free(sorted_text_ends);
        free(sorted_text_beginnings);
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    
    if (WriteText(output_file_beginnings, sorted_text_beginnings, lines_number) != 0) {
        close(output_file_beginnings);
        close(output_file_ends);
        free(original_text);
        free(sorted_text_beginnings);
        free(sorted_text_ends);
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    free(sorted_text_beginnings);
    close(output_file_beginnings);
    
    if (WriteText(output_file_ends, sorted_text_ends, lines_number) != 0) {
        close(output_file_ends);
        free(original_text);
        free(sorted_text_ends);
        std::cout << "Unsuccessful sorting." << std::endl;
        return 1;
    }
    free(sorted_text_ends);
    close(output_file_ends);
    
    free(original_text);
    std::cout << "Successful sorting." << std::endl;
    return 0;
}
