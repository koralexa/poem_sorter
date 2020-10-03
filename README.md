# Shakespeare's poem "Hamlet" sorter

This projects provides ability to sort all strings in Shakespeare's poem "Hamlet" alphabetically by beginning of lines and by ends of lines.

## Description

There are two modes: release mode and debug mode.
In release mode you will must provide 3 additional command line arguments to the program: input file name, file for "begin sorting" name and file for "end sorting" name. If your input is incorrect you will see a warning and prompt to try to enter arguments again.
In debug mode you don't need to provide command line arguments.

## Getting Started

### Installing

* Download the project from GitHub or clone it by
```
 git clone https://github.com/koralexa/poem_sorter.git
```

### Executing program

* Go to the project folder through your terminal.
* For release mode run
```
make
```
* Then run
```
./poem_sorter <input file> <output file 1> <output file 2>
```
* For debug mode run
```
make debug
```
* Then run
```
./poem_sorter_debug
```
