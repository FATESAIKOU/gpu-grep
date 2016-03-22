#include "../../cmncateStruct.h"
#include "../../commonInc.h"
#include "../../flex/fileParser.h"

// define

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);

MatchBase *genMatchBase(char *filename);

RankInfo *genRankInfo(MatchRes *match_result, InitOpt *init_opt);

// implement

MatchOpt *genMatchOpt(ThreadOpt *thread_opt) {
    MatchOpt *sample = (MatchOpt*) malloc(sizeof(MatchOpt));

    sample->match_strs = thread_opt->match_strs;
    sample->match_mode = thread_opt->match_mode;
    sample->error_rate = thread_opt->error_rate;
    sample->match_str_num = thread_opt->match_str_num;
    sample->insensitive = thread_opt->insensitive;

    sample->match_relations = thread_opt->match_relations;

    return sample;
}

MatchBase *genMatchBase(char *filename) {
    MatchBase *sample = (MatchBase*) malloc(sizeof(MatchBase));

    readFile(filename, sample);

    return sample;
}

RankInfo *genRankInfo(MatchRes *match_result, InitOpt *init_opt) {
    RankInfo *rank_info = (RankInfo*) malloc(sizeof(RankInfo));

    rank_info->rank_mode = init_opt->rank_mode;
    // code here

    return rank_info;
}

