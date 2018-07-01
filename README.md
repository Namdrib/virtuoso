# Virtuoso

## Requirements
- c++11
- make (optional)

## About the program
The program (virtuoso.cpp) takes in two files: a list of words (default virtuoso.txt) and a dictionary (default enable1.txt).

In the list of words, it tries to find single-step modifications (such as a removals or additions) to create a new word. An example is "CANNON" -> "CANON" by removing a letter, or "NOT" -> "NOTE" by adding a letter. For each word it can create by performing such modifications, it will list the word and all of its potential modifications. For each initial word, the output format is in the form:
```
word
	(new_word_1, (letter, position))
	...
	(new_word_n, (letter, position))
```

The help message shown when compiled and run with the `-h` flag
```
Usage:
./a [options]

Options:
  -d  : dictionary (of words) to use
  -q  : list of words to test
  -h  : show this help and exit
```
