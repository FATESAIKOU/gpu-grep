#include "../../cmncateStruct.h"
#include "../../commonInc.h"

PackInfo *genPackInfo(RankInfo *rank_info, InitOpt *init_opt);

ResultRec **ranking(RankInfo *rank_info);

int cmp_asc(const void *a, const void *b);

int cmp_desc(const void *a, const void *b);

PackInfo *genPackInfo(RankInfo *rank_info, InitOpt *init_opt) {
    PackInfo *pack_info = (PackInfo*) malloc(sizeof(PackInfo));

    pack_info->result_records = ranking(rank_info);
    pack_info->output_column_num = init_opt->output_column_num;
    pack_info->output_size = init_opt->output_size;
    pack_info->output_length = init_opt->output_length;

    return pack_info;
}

int cmp_asc(const void *a, const void *b) {
    return (((ResultRec*) a)->score) - (((ResultRec*) b)->score);
}

int cmp_desc(const void *a, const void *b) {
    return (((ResultRec*) b)->score) - (((ResultRec*) a)->score);
}

ResultRec **ranking(RankInfo *rank_info) {
    int (*cmp)(const void*, const void*);

    if (strcmp(rank_info->rank_mode, "asc")) {
        cmp = cmp_asc;
    } else if (strcmp(rank_info->rank_mode, "desc")) {
        cmp = cmp_desc;
    }

    qsort(rank_info->result_records, rank_info->result_length, sizeof(ResultRec), cmp);

    return rank_info->result_records;
}
