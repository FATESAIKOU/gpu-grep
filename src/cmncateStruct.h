#ifndef CMN_INCLUDED
#define CMN_INCLUDED
#include <stdio.h>

// some var defination
#define COLUMN_NUM 11
#define COLUMNS (char*[11]) { "@id", "@title", "@published", "@content", "@category", "@duration", "@favoriteCount", "@$viewCount", "@author", "@keyword", "@_uid"}

// parser -> init
typedef struct Init_Struct {
    char *filename;
    char *match_str;       // Data of matching string. Pattern: A or A|B|C or +A,-B,+C
    char *query_mode;      // Define the query mode('single_word', 'boolean' or 'multiterm').
    char *rank_mode;       // Define the ranking mode('asc' or 'desc').
    char *match_mode;      // Define the match mode(prefix or word).
    char *begin_at;        // The column that each record begins at.
    char **output_column;  // Define the output column.
    int output_column_num; // Number of the output column.
    float error_rate;      // Define the lower bound of tolerable error rate.
    int insensitive;       // Is insensitive to alpha case?
    int output_size;       // Define the output size.
    int output_length;     // The length of output record.
} InitOpt;

// init -> jobControl
typedef struct Job_Ctl_Struct {
    char **match_strs;     // 2-Dim array of string.
    char *match_relations; // store the additional flags of matching(Ex ['|', '&'], ['-', '+'])
    char *match_mode;
    char *begin_at;
    float error_rate;
    int insensitive;
    int match_str_num;    // number of contained strings
} JobOpt;

// jobControl -> threadCtl
typedef struct Thread_Ctl_Struct {
    char **match_strs;
    char *match_relations;
    char *match_mode;
    char *begin_at;
    float error_rate;
    int match_str_num;
    int insensitive;
} ThreadOpt;

// threadCtl -> matching
// 0. Single Record Info
typedef struct Record_Info {
    long int record_offset;           // the offset of single record
    long int attr_offset[COLUMN_NUM]; // the offset of the record's attributes
    int attr_num;                     // attribute num
    int score;                        // score
} RecordInfo;
// 1. Control flags
typedef struct Matching_Opt {
    // for matching
    char **match_strs;
    char *match_mode;
    float error_rate;
    int match_str_num;
    int insensitive;

    // for scoring
    char *match_relations;
} MatchOpt;
// 2. Data
typedef struct Matching_Base {
    char *datas; // all the data base
    RecordInfo *record_info;
    int rec_entry;
    size_t data_len;
} MatchBase;

// matching -> threadCtl
typedef struct Matching_Result {
    RecordInfo *record_info; // to caculate all of them score, 2 loop for kernel & attr_score was need
    int rec_entry;
} MatchRes;

// threadCtl -> ranker(scorer)
typedef struct Ranking_info {
    char *datas;
    RecordInfo *record_info;
    int rec_entry;

    char *rank_mode;
} RankInfo;

// ranker -> packer
typedef struct Packing_Info {
    char *datas;
    RecordInfo *record_info;
    int rec_entry;
} PackInfo;

// packer -> return
typedef struct Result {
    char *datas;
    RecordInfo *record_info;
    int res_entry; // only change this!!
} Result;

#endif
