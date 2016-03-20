#include "commonInc.h"
#include "libs.h"

int main(int argc, char *argv[])
{
    char *filename = argv[1];

    InitOpt *init_opt = (InitOpt*) parseArgs(argc, argv);
    printArgs((InitOpt*) init_opt);

    JobOpt *job_opt = (JobOpt*) setupJobArgs(init_opt);
    printJobArgs((JobOpt*) job_opt);

    ThreadOpt *thread_opt = (ThreadOpt*) genThreadOpt(job_opt);
    printThreadArgs(thread_opt);

    MatchOpt *match_opt = (MatchOpt*) genMatchOpt(thread_opt);
    MatchBase *match_base = (MatchBase*) genMatchBase(filename);

    printf("success!!\n");

    return 0;
}
