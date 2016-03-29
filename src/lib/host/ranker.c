#include "../../cmncateStruct.h"
#include "../../commonInc.h"

PackInfo *genPackInfo(InitOpt *init_opt, RankInfo *rank_info);
RecordInfo *ranking(RecordInfo *record_info, int rec_num, char *rank_mode);
int cmpAsc(const void *a, const void *b);
int cmpDesc(const void *a, const void *b);

PackInfo *genPackInfo(InitOpt *init_opt, RankInfo *rank_info) {
    PackInfo *pack_info = (PackInfo*) malloc(sizeof(PackInfo));

    pack_info->datas = rank_info->datas;
    pack_info->rec_entry = rank_info->rec_entry;
    pack_info->record_info = ranking(rank_info->record_info, rank_info->rec_entry, rank_info->rank_mode);
    pack_info->output_length = init_opt->output_length;

    return pack_info;
}

RecordInfo *ranking(RecordInfo *record_info, int rec_num, char *rank_mode) {
    if (strcmp(rank_mode, "asc") == 0) {
        qsort(record_info, rec_num, sizeof(RecordInfo), cmpAsc);
    } else {
        qsort(record_info, rec_num, sizeof(RecordInfo), cmpDesc);
    }

    return record_info;
}

int cmpDesc(const void *a, const void *b) {
    return (((RecordInfo*) b)->score) - (((RecordInfo*) a)->score);
}

int cmpAsc(const void *a, const void *b) {
    return (((RecordInfo*) a)->score) - (((RecordInfo*) b)->score);
}
