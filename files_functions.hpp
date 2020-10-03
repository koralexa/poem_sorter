//
//  files_functions.hpp
//  poem_sorter
//
//  Created by Alexandra Korabulina on 22.09.2020.
//

#ifndef files_functions_hpp
#define files_functions_hpp

int OpenFile(const char * file_name, int access, unsigned mode);

long long ReadText(int file, char ** text);

int WriteText(int file, char ** text, long long lines_number);

#endif /* files_functions_hpp */
