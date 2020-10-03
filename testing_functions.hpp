//
//  testing_functions.hpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 03.10.2020.
//

#ifndef testing_functions_hpp
#define testing_functions_hpp

void TestCompareLinesBeginnings(const char * line1, const char * line2, int answer);

void TestCompareLinesEnds(const char * line1, const char * line2, int answer);

void TestQuickSort(char ** sorted_text, long long left, long long right, const char * mode, char ** answer);

#endif /* testing_functions_hpp */
