//
//  sorting_functions.hpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 22.09.2020.
//

#ifndef sorting_functions_hpp
#define sorting_functions_hpp

int CompareLinesBeginnings(const char * line1, const char * line2);

int CompareLinesEnds(const char * line1, const char * line2);

int QuickSort(char ** sorted_text, long long left, long long right,
              int (*Comparator)(const char *, const char *));

int SortText(char * original_text, char ** sorted_text, long long lines_number,
             int (*Comparator)(const char *, const char *));

int InitializeSortedArrays(char *** sorted_text_beginnings, char *** sorted_text_ends,
                           char * text, long long lines_number);

#endif /* sorting_functions_hpp */
