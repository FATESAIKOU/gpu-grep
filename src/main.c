#include "commonInc.h"
#include "libs.h"

int main(int argc, char *argv[])
{
    InitOpt *init_opt = (InitOpt*) parseArgs(argc, argv);
    printArgs((InitOpt*) init_opt);

    JobOpt *job_opt = (JobOpt*) setupJobArgs(init_opt);
    printJobArgs((JobOpt*) job_opt);

    ThreadOpt *thread_opt = (ThreadOpt*) genThreadOpt(job_opt);
    printThreadArgs(thread_opt);

    return 0;
}
