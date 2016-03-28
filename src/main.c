#include "commonInc.h"
#include "libs.h"

Result *main(int argc, char *argv[])
{
    InitOpt *init_opt = (InitOpt*) parseArgs(argc, argv);
    printArgs((InitOpt*) init_opt);

    JobOpt *job_opt = (JobOpt*) setupJobArgs(init_opt);
    printJobArgs((JobOpt*) job_opt);

    ThreadOpt *thread_opt = (ThreadOpt*) genThreadOpt(job_opt);
    printThreadArgs(thread_opt);

    // Gen by threadCtl
    MatchOpt *match_opt = (MatchOpt*) genMatchOpt(thread_opt);
    MatchBase *match_base = (MatchBase*) genMatchBase(thread_opt, init_opt->filename);

    // Gen by matching
    MatchRes *match_result = (MatchRes*) genMatchRes(match_opt, match_base);

    // Gen by threadCtl
    // RankInfo *rank_info = (RankInfo*) genRankInfo(init_opt, match_base, match_result);

    // Gen by ranker
    // PackInfo *pack_info = (PackInfo*) genPackInfo(rank_info);

    // Gen by packer
    // Result *result = (Result*) genResult(pack_info);

    printf("success!!\n");

    return NULL;
}
