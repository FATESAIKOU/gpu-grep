extern "C" {

#include "../../cmncateStruct.h"
#include "../../libs.h"
#include "../../commonInc.h"
#include <cuda.h>

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base);
ResultRec **matching(MatchOpt *match_opt, MatchBase *match_base);
int getScore(MatchOpt *match_opt, int **matching_counter, int word_num);
int ***cpuMatching(MatchOpt *match_opt, MatchBase *match_base);

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base) {
    MatchRes *match_res = (MatchRes*) malloc(sizeof(MatchRes));

    match_res->result_records = matching(match_opt, match_base);
    match_res->result_length = match_base->record_num;
    // 1. get result_records by calling matching(match_opt, match_base)
    //  (i) match_res->result_records = matching(match_opt, match_base);
    // 2. get result_length from match_base
    //  (i) match_res->result_length = match_base->record_num
    // 3. return match_res

    return match_res;
}

ResultRec **matching(MatchOpt *match_opt, MatchBase *match_base) {
    ResultRec **result_records = (ResultRec**) malloc(sizeof(ResultRec*) * (match_base->record_num));

    int ***matching_counters = cpuMatching(match_opt, match_base);
    int i;
    for (i = 0; i < match_base->record_num; i ++) {
        result_records[i] = (ResultRec*) malloc(sizeof(ResultRec));
        result_records[i]->score = getScore(match_opt, matching_counters[i], match_base->record_num);
        result_records[i]->record = match_base->sample_records[i];
    }

    // 1. get matching_counter by calling device_ matching. Ps matching_counter[record_id][attribute_id][word_id] = appear_time.
    //  (i)  matching_counters = gpuMatching<<<Block, Thread>>>(match_opt, match_base)  ::need cudaMemcpy(in & out)
    // 2. using matching_counter above, generate structure ResultRec
    //  for i in 0..match_base->record_num
    //  (i)  result_records[record_id]->score = getScore(match_opt, matching_counters[record_id], record_num)
    //  (ii) result_records[record_id]->record = match_base->sample_records[record_id];
    // 3. return result_records

    return result_records;
}

int getScore(MatchOpt *match_opt, int **matching_counter, int word_num) {
    int score = 0;

    // 1. count out score
    int i, j;
    for (i = 0; i < COLUMN_NUM; i ++) {
        for (j = 0; j < word_num; j ++) {
            score += matching_counter[i][j];
        }
    }

    // 2. return the score

    return score;
}

int ***cpuMatching(MatchOpt *match_opt, MatchBase *match_base) {
    char *aim_word;
    int rec_id, attr_id, word_id;
    int *scores = (int*) malloc(sizeof(int) * (match_base->record_num));

    int ***match_counter = (int***) malloc(sizeof(int**) * match_base->record_num);
    for (rec_id = 0; rec_id < match_base->record_num; rec_id ++) {

        match_counter[rec_id] = (int**) malloc(sizeof(int*) * COLUMN_NUM);
        for (attr_id = 0; attr_id < COLUMN_NUM; attr_id ++) {

            match_counter[rec_id][attr_id] = (int*) malloc(sizeof(int) * match_opt->match_str_num);
            for (word_id = 0; word_id < match_opt->match_str_num; word_id ++) {
                aim_word = match_opt->match_strs[word_id];

                if (strstr(match_base->sample_records[rec_id][attr_id], aim_word) != NULL) {
                    match_counter[rec_id][attr_id][word_id] = 1;
                } else {
                    match_counter[rec_id][attr_id][word_id] = 0;
                }
            }
        }
    }

    return match_counter;
}

}

__global__ void gpuMatching(MatchOpt *match_opt, MatchBase *match) {
    // ThreadIdx == 0
    // 1. wait for all thread completing it's task
    // 2. merge all of the matching counter
    // 3. complete match_counter
    //
    // ThreadIdx == 1 - warpsize
    // 1. malloc a memory space to store the length is warpsize - 1 records' matching counter
    // 2. matching & record
    // 3. wait for somebody to merge all of these matching counter
}
