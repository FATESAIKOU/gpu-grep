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

    // 1. get result_records from match_result
    rank_info->result_records = match_result->result_records;

    // 2. get result_length from match_result
    rank_info->result_length = match_result->result_length;

    // 3. get rank_mode from init_opt
    rank_info->rank_mode = init_opt->rank_mode;

    // 4. return rank_info
    return rank_info;
}

