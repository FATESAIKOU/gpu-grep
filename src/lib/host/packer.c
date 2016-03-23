#include "../../cmncateStruct.h"
#include "../../commonInc.h"

Result *genPackResult(PackInfo *pack_info) {
    Result *result = (Result*) malloc(sizeof(Result));

    result->result_records = pack_info->result_records;
    result->result_column = pack_info->output_column;
    result->result_length = pack_info->output_length;
    result->result_column_num = pack_info->output_column_num;

    return result;
}
