#ifndef MTH_INCLUDED
#define MTH_INCLUDED

MatchRes *genMatchRes(MatchOpt *match_opt, MatchBase *match_base);
RecordInfo *matching(MatchOpt *match_opt, MatchBase *match_base);
char *loadFile(MatchOpt* match_opt, MatchBase *match_base);
RecordInfo *loadRecord(MatchBase *match_base);
int *getRecordScore(MatchOpt *match_opt, char *datas, RecordInfo *record_info, int rec_num);

#endif
