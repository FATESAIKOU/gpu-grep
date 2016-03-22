#ifndef RANKER_INCLUDED
#define RANKER_INCLUDED

PackInfo *genPackInfo(RankInfo *rank_info, InitOpt *init_opt);

ResultRec **ranking(ResultRec **result_record, int result_length, char *rank_mode);

int cmp_asc(const void *a, const void *b);

int cmp_desc(const void *a, const void *b);

#endif
