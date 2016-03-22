#ifndef MTH_INCLUDED
#define MTH_INCLUDED

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base);
ResultRec **matching(MatchOpt *match_opt, MatchBase *match_base);
int getScore(MatchOpt *match_opt, int **matching_counter, int word_num);

#endif
