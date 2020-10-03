all: main.cpp files sorting
	g++ -Wall -Wextra -o poem_sorter main.cpp files_functions.cpp sorting_functions.cpp

debug: main.cpp files sorting testing
	g++ -DDEBUG -Wall -Wextra -o poem_sorter_debug main.cpp files_functions.cpp sorting_functions.cpp testing_functions.cpp

files: files_functions.hpp files_functions.cpp

sorting: sorting_functions.hpp sorting_functions.cpp

testing: testing_functions.hpp testing_functions.cpp

clean: 
	rm -rf *.o all


