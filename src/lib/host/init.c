#include "../../cmncateStruct.h"
#include "../../commonInc.h"

typedef struct Matching_Str_Info {
    char **strs;        // 2-Dim array of string.
    char *str_relations; // store the additional flags of matching(Ex ['|', '&'], ['-', '+'])
    int str_num; // number of contained strings
} StrInfo;

JobOpt *genJobOpt(InitOpt *init_opt) {
    JobOpt *sample = (JobOpt*) malloc(sizeof(JobOpt));

    sample->match_mode  = strdup(init_opt->match_mode);
    sample->begin_at    = strdup(init_opt->begin_at);
    sample->error_rate  = init_opt->error_rate;
    sample->insensitive = init_opt->insensitive;

    return sample;
}

int getStrNum(const char *str, const char *query_mode) {
    int len = strlen(str);
    int boolean = 0;

    if (!strcmp(query_mode, "single_word")) {
        return 1;
    } else if (!strcmp(query_mode, "boolean")) {
        while (--len) {
            if (str[len] == '|' || str[len] == '&') boolean ++;
        }
    } else if (!strcmp(query_mode, "multiterm")) {
        while (--len) {
            if (str[len] == ',') boolean ++;
        }
    }

    return (boolean + 1);
}

char **getStrs(const char *str, int str_num, const char *query_mode) {
    char **strs;
    char *tmp_str = strdup(str);

    strs = (char**) malloc(sizeof(char*) * str_num);

    int i;
    char *token;
    char *delim;
    if (!strcmp(query_mode, "single_word")) {
        strs[0] = strdup(tmp_str);
    } else if (!strcmp(query_mode, "boolean")) {
        delim = strdup("|&");
    } else if (!strcmp(query_mode, "multiterm")) {
        delim = strdup(",");
    } else {
        exit(2);
    }

    token = strtok(tmp_str, delim);
    for (i = 0; token != NULL && i < str_num; i++, token = strtok(NULL, delim)) {
        strs[i] = strdup(token);
    }

    free(tmp_str);

    return strs;
}

char *getStrRelations(const char *str, int str_num, const char *query_mode) {
    int len = strlen(str);

    char *relations = (char*) malloc(sizeof(char) * str_num);

    int i, j;
    if (!strcmp(query_mode, "single_word")) {
        *relations = '+';
    } else if (!strcmp(query_mode, "boolean")) {
        for (i = 0, j = 0; i < len; i ++) {
            if (str[i] == '|' || str[i] == '&')
                relations[j++] = str[i];
        }
    } else if (!strcmp(query_mode, "multiterm")) {
        for (i = 0, j = 0; i < len; i++) {
            if ((str[i] == '+' || str[i] == '-') && (i == 0 || str[i-1] == ','))
                relations[j++] = str[i];
        }
    } else {
        exit(2);
    }

    return relations;
}

StrInfo *parseMatchStrs(char *str, const char *query_mode) {
    StrInfo *str_info = (StrInfo*) malloc(sizeof(StrInfo));

    str_info->str_num = getStrNum(str, query_mode);
    str_info->strs = getStrs(str, str_info->str_num, query_mode);
    str_info->str_relations = getStrRelations(str, str_info->str_num, query_mode);

    return str_info;
}

JobOpt *setupJobArgs(InitOpt *init_opt) {
    JobOpt *job_opt = genJobOpt(init_opt);

    StrInfo *str_info = parseMatchStrs(init_opt->match_str, init_opt->query_mode);

    job_opt->match_strs = str_info->strs;
    job_opt->match_relations = str_info->str_relations;
    job_opt->match_str_num = str_info->str_num;

    free(str_info);

    return job_opt;
}

void printJobArgs(JobOpt *job_opt) {
    printf("----JobOpt----\n");
    printf("\tmatch_str_num: %d\n", job_opt->match_str_num);
    printf("\tmatch_mode: %s\n", job_opt->match_mode);
    printf("\tbegin_at: %s\n", job_opt->begin_at);
    printf("\terror_rate: %f\n", job_opt->error_rate);
    printf("\tinsensitive: %d\n", job_opt->insensitive);
    printf("\trelations | match_strs:\n");
    int i;
    for (i = 0; i < job_opt->match_str_num; i ++) {
        printf("\t%c\t| %s\n", job_opt->match_relations[i], job_opt->match_strs[i]);
    }
    printf("--------------\n");
}
