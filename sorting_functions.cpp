//
//  sorting_functions.cpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 22.09.2020.
//

#include "sorting_functions.hpp"
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



//! Compares two strings alphabetically  by beginning of lines
//!
//! @param [in] line1 first line to compare
//! @param [in] line2 second line to compare
//!
//! @return 0 if strings are same alphabetically, 1 in case the first string is earlier alphabetically,
//! -1 in case the second string is earlier alphabetically, -2 in case of bad parametrs
//!
//! @note Only letters take part in comparison
//! @note In case of error prints eroor message in standart error stream
int CompareLinesBeginnings(const char * line1, const char * line2) {
    if ((line1 == NULL) || (line2 == NULL)) {
        std::cerr << "ERROR: CompareLinesBegginings() got null pointer." << std::endl;
        return -2;
    }
    
    if ((line1[0] == '\0') && (line2[0] == '\0')) {
        return 0;
    }
    if (line1[0] == '\0') {
        return 1;
    }
    if (line2[0] == '\0') {
        return -1;
    }
    if (strcmp(line1, line2) == 0) {
        return 0;
    }
    
    long long sym1 = 0;
    long long sym2 = 0;
    char tmp1 = 0;
    char tmp2 = 0;
    
    while ((line1[sym1] != '\0') && (line2[sym2] != '\0')) {
        while ((line1[sym1] != '\0') && (!std::isalpha(line1[sym1]))) {
            sym1++;
        }
        if (line1[sym1] == '\0') {
            return 1;
        }
        
        while ((line2[sym2] != '\0') && (!std::isalpha(line2[sym2]))) {
            sym2++;
        }
        if (line2[sym2] == '\0') {
            return -1;
        }
        
        if (line1[sym1] > 'Z') {
            tmp1 = line1[sym1] - ('a' - 'A');
        } else {
            tmp1 = line1[sym1];
        }
        if (line2[sym2] > 'Z') {
            tmp2 = line2[sym2] - ('a' - 'A');
        } else {
            tmp2 = line2[sym2];
        }
        
        if (tmp1 > tmp2) {
            return -1;
        }
        if (tmp1 < tmp2) {
            return 1;
        }
        sym1++;
        sym2++;
    }
    
    if ((line1[sym1] == '\0') && (line2[sym2] == '\0')) {
        return 0;
    }
    if (line1[sym1] == '\0') {
        return 1;
    } else {
        return -1;
    }
}



//! Compares two strings alphabetically  by ends of lines
//!
//! @param [in] line1 first line to compare
//! @param [in] line2 second line to compare
//!
//! @return 0 if strings are same alphabetically, 1 in case the first string is earlier alphabetically,
//! -1 in case the second string is earlier alphabetically, -2 in case of bad parametrs
//!
//! @note Only letters take part in comparison
//! @note In case of error prints eroor message in standart error stream
int CompareLinesEnds(const char * line1, const char * line2) {
    if ((line1 == NULL) || (line2 == NULL)) {
        std::cerr << "ERROR: CompareLinesBegginings() got null pointer." << std::endl;
        return -2;
    }
    
    long long len1 = strlen(line1);
    long long len2 = strlen(line2);
    
    if ((line1[len1 - 1] == '\0') && (line2[len2 - 1] == '\0')) {
        return 0;
    }
    if (line1[len1 - 1] == '\0') {
        return 1;
    }
    if (line2[len2 - 1] == '\0') {
        return -1;
    }
    if (strcmp(line1, line2) == 0) {
        return 0;
    }
    
    long long sym1 = len1 - 1;
    long long sym2 = len2 - 1;
    char tmp1 = 0;
    char tmp2 = 0;
    
    while ((line1[sym1] != '\0') && (line2[sym2] != '\0')) {
        while ((line1[sym1] != '\0') && (!std::isalpha(line1[sym1]))) {
            sym1--;
        }
        if (line1[sym1] == '\0') {
            return 1;
        }
        
        while ((line2[sym2] != '\0') && (!std::isalpha(line2[sym2]))) {
            sym2--;
        }
        if (line2[sym2] == '\0') {
            return -1;
        }
        
        if (line1[sym1] > 'Z') {
            tmp1 = line1[sym1] - ('a' - 'A');
        } else {
            tmp1 = line1[sym1];
        }
        if (line2[sym2] > 'Z') {
            tmp2 = line2[sym2] - ('a' - 'A');
        } else {
            tmp2 = line2[sym2];
        }
        
        if (tmp1 > tmp2) {
            return -1;
        }
        if (tmp1 < tmp2) {
            return 1;
        }
        sym1--;
        sym2--;
    }
    
    if ((line1[sym1] == '\0') && (line2[sym2] == '\0')) {
        return 0;
    }
    if (line1[sym1] == '\0') {
        return 1;
    } else {
        return -1;
    }
}



//! Sorts array of strings alphabetically
//!
//! @param [in] sorted_text  input array
//! @param [in] left  index of first element to make sort
//! @param [in] right  index of first element to make sort
//! @param [in] Comparator pointer to a function for lines comparison
//!
//! @return 0 in case sorting finished successfuly, -1 otherwise
//!
//! @note In case of error prints eroor message in standart error stream
int QuickSort(char ** sorted_text, long long left, long long right,
              int (*Comparator)(const char *, const char *)) {
    if (sorted_text == NULL) {
        std::cerr << "ERROR: QuickSort() got null pointer." << std::endl;
        return -1;
    }
    
    char * buf = NULL;
    int cmp = 0;
    if (right - left == 0) {
        return 0;
    }
    if (right - left == 1) {
        cmp = Comparator(sorted_text[left], sorted_text[right]);
        if (cmp == -2) {
            return -1;
        }
        if (cmp < 0) {
            buf = sorted_text[left];
            sorted_text[left] = sorted_text[right];
            sorted_text[right] = buf;
        }
        return 0;
    }
    
    char * mid = sorted_text[(right + left) / 2];
    long long right_tmp = right;
    long long left_tmp = left;
    
    do {
        cmp = Comparator(sorted_text[left_tmp], mid);
        if (cmp == -2) {
            return -1;
        }
        while (cmp > 0) {
            left_tmp++;
            cmp = Comparator(sorted_text[left_tmp], mid);
            if (cmp == -2) {
                return -1;
            }
        }
        cmp = Comparator(sorted_text[right_tmp], mid);
        if (cmp == -2) {
            return -1;
        }
        while (cmp < 0) {
            right_tmp--;
            cmp = Comparator(sorted_text[right_tmp], mid);
            if (cmp == -2) {
                return -1;
            }
        }
        if (left_tmp <= right_tmp) {
            buf = sorted_text[right_tmp];
            sorted_text[right_tmp] = sorted_text[left_tmp];
            sorted_text[left_tmp] = buf;
            left_tmp++;
            right_tmp--;
        }
    } while (left_tmp <= right_tmp);

    if (QuickSort(sorted_text, left, right_tmp, Comparator) != 0) {
        return -1;
    }
    if (QuickSort(sorted_text, left_tmp, right, Comparator) != 0) {
        return -1;
    }
    return 0;
}



//! Sorts array of strings alphabetically
//!
//! @param [in] original_text  input text
//! @param [in] sorted_text  array of pointers to sort
//! @param [in] lines_number  number of lines in original text
//! @param [in] Comparator pointer to a function for lines comparison
//!
//! @return 0 in case sorting finished successfuly, -1 otherwise
//!
//! @note In case of error prints eroor message in standart error stream
int SortText(char * original_text, char ** sorted_text, long long lines_number,
             int (*Comparator)(const char *, const char *)) {
    if (original_text == NULL) {
        std::cerr << "ERROR: SortText() got null pointer." << std::endl;
        return -1;
    }
    if (lines_number == 0) {
        std::cerr << "ERROR: SortText() got zero lines number." << std::endl;
        return -1;
    }
    
    if (QuickSort(sorted_text, 0, lines_number - 1, Comparator) != 0) {
        return -1;
    }
    return 0;
}



//! Initializes two arrays of pointers with pointers to strings of original text
//!
//! @param [in] sorted_text_beginnings  array of pointers for sorting by beginnings of lines
//! @param [in] sorted_text_ends  array of pointers for sorting by ends of lines
//! @param [in] text  input text
//! @param [in] lines_number  number of lines in original text
//!
//! @return 0 in case sorting finished successfuly, -1 otherwise
//!
//! @note In case of error prints eroor message in standart error stream
int InitializeSortedArrays(char *** sorted_text_beginnings, char *** sorted_text_ends,
                           char * text, long long lines_number) {
    if (text == NULL) {
        std::cerr << "ERROR: InitialiseSortedArrays() got null pointer." << std::endl;
        return -1;
    }
    
    *sorted_text_beginnings = (char **)calloc(sizeof(char*), lines_number);
    if (sorted_text_beginnings == NULL) {
        std::cerr << "ERROR: InitialiseSortedArrays() can't allocate memory." << std::endl;
        return -1;
    }
    *sorted_text_ends = (char **)calloc(sizeof(char*), lines_number);
    if (sorted_text_ends == NULL) {
        std::cerr << "ERROR: InitialiseSortedArrays() can't allocate memory." << std::endl;
        return -1;
    }
    
    long long i = 0;
    char * current_line = text + 1;
    for (i = 0; i < lines_number; i++) {
        (*sorted_text_ends)[i] = current_line;
        (*sorted_text_beginnings)[i] = current_line;
        while (*current_line != '\0') {
            current_line++;
        }
        current_line++;
    }
    return 0;
}
