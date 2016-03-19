#ifndef CMN_INCLUDED
#include "../../cmncateStruct.h"
#endif

typedef struct Matching_Str_Info {
    char *str_relations; // store the additional flags of matching(Ex ['|', '&'], ['-', '+'])
    int str_num; // number of contained strings
} StrInfo;

JobOpt *genJobOpt(InitOpt *init_opt);

int getStrNum(const char *str, const char *query_mode);

char **getStrs(const char *str, int str_num, const char *query_mode);

char *getStrRelations(const char *str, int str_num, const char *query_mode);

StrInfo *parseMatchStrs(char *str, const char *query_mode);

JobOpt *setupJobArgs(InitOpt *init_opt);

void printJobArgs(JobOpt *job_opt);
