#ifndef RANKER_INCLUDED
#define RANKER_INCLUDED

PackInfo *genPackInfo(InitOpt *init_opt, RankInfo *rank_info);
RecordInfo *ranking(RecordInfo *record_info, int rec_num, char *rank_mode);
int cmpAsc(const void *a, const void *b);
int cmpDesc(const void *a, const void *b);

#endif
