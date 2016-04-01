#include "../../cmncateStruct.h"
#include "../../commonInc.h"

Result *genResult(PackInfo *pack_info) {
    Result *result = (Result*) malloc(sizeof(Result));

    result->datas = pack_info->datas;
    result->record_info = pack_info->record_info;
    result->res_entry = pack_info->rec_entry;

    return result;
}

void printResult(Result *result) {
    int i, j;

    for (i = 0; i < result->res_entry; i ++) {
        if (result->record_info[i].score == 0) break;
        printf("Record: %d\n", i);
        printf("Score: %d\n", result->record_info[i].score);
        printf("Attr:\n");
        for (j = 0; j < COLUMN_NUM; j ++) {
            printf("%s\n", result->datas + result->record_info[i].attr_offset[j]);
        }
    }
}
