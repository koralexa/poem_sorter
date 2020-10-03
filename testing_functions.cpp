//
//  testing_functions.cpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 03.10.2020.
//

#include <iostream>
#include <cstdio>

#include "testing_functions.hpp"
#include "sorting_functions.hpp"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

void TestCompareLinesBeginnings(const char * line1, const char * line2, int answer) {
    int result = CompareLinesBeginnings(line1, line2);
    if (result == answer) {
        std::cout << GREEN << "[PASSED] " << WHITE << "CompareLinesBeginnings(" << line1 << ", " << line2
            << ") = " << answer << std::endl;
    } else {
        std::cout << RED << "[ERROR]  " << WHITE << "CompareLinesBeginnings(" << line1 << ", " << line2
            << ") = " << result << " != " << answer << std::endl;
    }
}

void TestCompareLinesEnds(const char * line1, const char * line2, int answer) {
    int result = CompareLinesEnds(line1, line2);
    if (result == answer) {
        std::cout << GREEN << "[PASSED] " << WHITE << "CompareLinesEnds(" << line1 << ", " << line2
            << ") = " << answer << std::endl;
    } else {
        std::cout << RED << "[ERROR]  " << WHITE << "CompareLinesEnds(" << line1 << ", " << line2
            << ") = " << result << " != " << answer << std::endl;
    }
}

void TestQuickSort(char ** sorted_text, long long left, long long right, const char * mode, char ** answer) {
    if (strcmp(mode, "begin") == 0) {
        QuickSort(sorted_text, left, right, CompareLinesBeginnings);
    } else {
        QuickSort(sorted_text, left, right, CompareLinesEnds);
    }
    long long i = 0;
    for (i = 0; i <= right; i++) {
        if (sorted_text[i] != answer[i]) {
            std::cout << RED << "[ERROR]  " << WHITE << "QuickSort() worked incorrectly." << std::endl;
            return;
        }
    }
    std::cout << GREEN << "[PASSED] " << WHITE << "QuickSort() worked correctly." << std::endl;
}
