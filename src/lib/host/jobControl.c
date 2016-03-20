#include "../../cmncateStruct.h"
#include "../../commonInc.h"

ThreadOpt *genThreadOpt(JobOpt *job_opt){
    ThreadOpt *sample = (ThreadOpt*) malloc(sizeof(ThreadOpt));

    sample->match_strs = job_opt->match_strs;
    sample->match_relations = job_opt->match_relations;
    sample->match_mode = job_opt->match_mode;
    sample->begin_at = job_opt->begin_at;
    sample->error_rate = job_opt->error_rate;
    sample->insensitive = job_opt->insensitive;
    sample->match_str_num = job_opt->match_str_num;

    return sample;
}

void printThreadArgs(ThreadOpt *thread_opt) {
    printf("----ThreadOpt----\n");
    printf("\tmatch_str_num: %d\n", thread_opt->match_str_num);
    printf("\tmatch_mode: %s\n", thread_opt->match_mode);
    printf("\tbegin_at: %s\n", thread_opt->begin_at);
    printf("\terror_rate: %f\n", thread_opt->error_rate);
    printf("\tinsensitive: %d\n", thread_opt->insensitive);
    printf("\trelations | match_strs:\n");
    int i;
    for (i = 0; i < thread_opt->match_str_num; i ++) {
        printf("\t%c\t| %s\n", thread_opt->match_relations[i], thread_opt->match_strs[i]);
    }
    printf("--------------\n");
}
