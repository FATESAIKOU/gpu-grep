#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED
#include "../../cmncateStruct.h"

InitOpt *genInitOpt();

char **parseStrings(char *strs, int *str_num, const char *delim);

InitOpt *parseArgs(int argc, char *argv[]);

int checkOpt(InitOpt *init_opt);

void printArgs(InitOpt *init_opt);

#endif
