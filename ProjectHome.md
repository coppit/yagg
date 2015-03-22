Given YACC-like and LEX-like input files, yagg generates a C++ program that generates all strings of a user-specified length.  The YACC-like language grammar file provides the grammar productions for string generation, along with optional action blocks that can perform context-sensitive checks in order to limit the generated strings.  The LEX-like terminal generator file provides specifications that instruct the program how to generate strings for terminals in the grammar.