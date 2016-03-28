extern "C" {

#include "../../cmncateStruct.h"
#include "../../libs.h"
#include "../../commonInc.h"
#include <cuda.h>

#define ThreadNum 1024
#define BlockNum 32

MatchRes *genMatchRes(MatchOpt *match_opt, MatchBase *match_base);
RecordInfo *matching(MatchOpt *match_opt, MatchBase *match_base);
char *loadFile(MatchOpt* match_opt, MatchBase *match_base);
RecordInfo *loadRecord(MatchBase *match_base);
int *getRecordScore(MatchOpt *match_opt, char *datas, RecordInfo *record_info, int rec_num);
char **getMatchStrs(MatchOpt *match_opt);
__global__ void gpuMatching(char *datas, RecordInfo *rec_info, char **match_strs, int str_num, int rec_num, int attr_num, int base);
__device__ int d_strstr(char *a, char *b);
__device__ int d_strlen(char *s);


MatchRes *genMatchRes(MatchOpt *match_opt, MatchBase *match_base) {
    MatchRes *match_result = (MatchRes*) malloc(sizeof(MatchRes));

    match_result->record_info = matching(match_opt, match_base);
    match_result->rec_entry = match_base->rec_entry;

    return match_result;
}

RecordInfo *matching(MatchOpt *match_opt, MatchBase *match_base) {
    // 1. load matching base to Device
    RecordInfo *device_rec_info = loadRecord(match_base);
    char *device_datas = loadFile(match_opt, match_base);
    int rec_num = match_base->rec_entry;

    // 2. get each attr score
    getRecordScore(match_opt, device_datas, device_rec_info, rec_num);
    cudaDeviceSynchronize();

    // 4. return RecordInfo
    return device_rec_info;
}

char *loadFile(MatchOpt* match_opt, MatchBase *match_base) {
    char *device_datas;
    char *host_datas = match_base->datas;
    size_t data_size = sizeof(char) * match_base->data_len;

    cudaMalloc(&device_datas, data_size);
    cudaMemcpy(device_datas, host_datas, data_size, cudaMemcpyHostToDevice);

    return device_datas;
}

RecordInfo *loadRecord(MatchBase *match_base) {
    RecordInfo *host_rec_info = match_base->record_info;
    int rec_info_size = sizeof(RecordInfo) * match_base->rec_entry;

    RecordInfo *device_rec_info;
    cudaMallocManaged(&device_rec_info, rec_info_size);
    memcpy(device_rec_info, host_rec_info, rec_info_size);


    return device_rec_info;
}

int *getRecordScore(MatchOpt *match_opt, char *datas, RecordInfo *record_info, int rec_num) {
    // matching
    char **match_strs = getMatchStrs(match_opt);
    int match_str_num = match_opt->match_str_num;
    int base, round_limit = ceil(rec_num / (float) (BlockNum * ThreadNum));
    int i;
    for (i = 0; i < round_limit; i ++) {
        base = i * BlockNum * ThreadNum;
        gpuMatching<<<BlockNum, ThreadNum>>>(datas, record_info, match_strs, match_str_num, rec_num, COLUMN_NUM, base);
    }

    return NULL;
}

char **getMatchStrs(MatchOpt *match_opt) {
    int match_str_num = match_opt->match_str_num;
    char **device_match_strs;
    cudaMallocManaged(&device_match_strs, sizeof(char*) * match_str_num);

    int i, str_len;
    char *device_str;
    for (i = 0; i < match_str_num; i ++) {
        str_len = strlen(match_opt->match_strs[i]);
        cudaMalloc(&device_str, sizeof(char) * str_len);
        cudaMemcpy(device_str, match_opt->match_strs[i], sizeof(char) * str_len, cudaMemcpyHostToDevice);

        device_match_strs[i] = device_str;
    }

    return device_match_strs;
}

}

__global__ void gpuMatching(char *datas, RecordInfo *rec_info, char **match_strs, int str_num, int rec_num, int attr_num, int base) {
    int index = base + blockIdx.x * blockDim.x + threadIdx.x;

    int i, j = 0;
    int offset;

    RecordInfo *aim = rec_info + index;
    for (i = 0; i < attr_num; i ++) {
        for (j = 0; j < str_num; j ++) {
            offset = rec_info[index].attr_offset[i];
            while  ((offset = d_strstr(datas + offset, match_strs[j])) > 0) {
                aim->score ++;
            }
        }
    }
}

__device__ int d_strstr(char *a, char *b) {
    int i, j;
    int a_len = d_strlen(a);
    int b_len = d_strlen(b);
    int loop_limit = a_len - b_len + 1;

    for (i = 0; i < loop_limit; i ++) {
        for (j = 0; j < b_len && a[i + j] == b[j]; j ++) ;

        if (j == b_len) return i;
    }

    return NULL;
}

__device__ int d_strlen(char *s) {
    int i = 0;
    while (s[i] != '\0') i ++;

    return i;
}
