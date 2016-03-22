#ifndef THRDCTL_INCLUDED
#define THRDCTL_INCLUDED

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);

MatchBase *genMatchBase(char *filename);

RankInfo *genRankInfo(MatchRes *match_result, InitOpt *init_opt);

#endif
