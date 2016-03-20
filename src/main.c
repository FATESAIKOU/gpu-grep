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

    // Gen by threadCtl
    // RankInfo *rank_info = (RankInfo*) matchRecords(match_opt, match_base);

    // Gen by ranker
    // PackInfo *pack_Info = (PackInfo*) rankResult(rank_info);

    // Gen by packer
    // Result *result = (Result*) packResult(pack_info);
    //
    // return result

    printf("success!!\n");

    return 0;
}
