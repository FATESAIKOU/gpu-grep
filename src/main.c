#include "commonInc.h"
#include "libs.h"

Result *main(int argc, char *argv[])
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

    // Gen by matching
    MatchRes *match_res = (MatchRes*) matchRecords(match_opt, match_base);

    // Gen by threadCtl
    RankInfo *rank_info = (RankInfo*) genRankInfo(match_res, init_opt);

    // Gen by ranker
    PackInfo *pack_info = (PackInfo*) genPackInfo(rank_info, init_opt);

    // Gen by packer
    Result *result = (Result*) genPackResult(pack_info);

    printf("success!!\n");

    return result;
}
