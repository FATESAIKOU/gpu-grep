extern "C" {

#include "../../cmncateStruct.h"
#include "../../libs.h"
#include <cuda.h>

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base);
ResultRec **matching(MatchOpt *match_opt, MatchBase *match_base);
int getScore(MatchOpt *match_opt, int **matching_counter, int word_num);

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base) {
    MatchRes *match_res = (MatchRes*) malloc(sizeof(MatchRes));

    // 1. get result_record by calling matching(match_opt, match_base)
    //  (i) match_res->result_record = matching(match_opt, match_base);
    // 2. get result_length from match_base
    //  (i) match_res->result_length = match_base->record_num
    // 3. return match_res

    return match_res;
}

ResultRec **matching(MatchOpt *match_opt, MatchBase *match_base) {
    ResultRec **result_records = (ResultRec**) malloc(sizeof(ResultRec*) * (match_base->record_num));

    // 1. get matching_counter by calling device_ matching. Ps matching_counter[record_id][attribute_id][word_id] = appear_time.
    //  (i)  matching_counters = gpuMatching<<<Block, Thread>>>(match_opt, match_base)  ::need cudaMemcpy(in & out)
    // 2. using matching_counter above, generate structure ResultRec
    //  for i in 0..match_base->record_num
    //  (i)  result_records[record_id]->score = getScore(match_opt, match_counters[record_id], record_num)
    //  (ii) result_records[record_id]->record = match_base->sample_records[record_id];
    // 3. return result_records

    return result_records;
}

int getScore(MatchOpt *match_opt, int **matching_counter, int word_num) {
    int score = 0;

    // 1. count out score
    // 2. return the score

    return score;
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
