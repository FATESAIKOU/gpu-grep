#ifndef THRDCTL_INCLUDED
#define THRDCTL_INCLUDED

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);

MatchBase *genMatchBase(char *filename);

void readRecord(char *filename, MatchBase *match_base);

RankInfo *matchRecords(MatchOpt *match_opt, MatchBase *match_base);

#endif
