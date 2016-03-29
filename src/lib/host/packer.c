#include "../../cmncateStruct.h"
#include "../../commonInc.h"

Result *genResult(PackInfo *pack_info) {
    Result *result = (Result*) malloc(sizeof(Result));

    result->datas = pack_info->datas;
    result->record_info = pack_info->record_info;
    result->res_entry = pack_info->output_length;

    return result;
}
