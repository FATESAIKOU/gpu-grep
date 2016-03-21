#include "../../cmncateStruct.h"
#include "../../commonInc.h"
#include "../device/matching.h"
#include "../../flex/fileParser.h"

// define

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);

MatchBase *genMatchBase(char *filename);

void readFile(char *filename, MatchBase *match_base);

RankInfo *matchRecords(MatchOpt *match_opt, MatchBase *match_base);

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

RankInfo *matchRecords(MatchOpt *match_opt, MatchBase *match_base) {
    return NULL;
}

