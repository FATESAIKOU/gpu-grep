#define CMN_INCLUDED

// some var defination
#define COLUMN_NUM 12
#define COLUMNS (char*[12]) { "id", "published", "updated", "title", "content", "author", "keyword", "favoriate", "view", "duration", "category", "src" }

// parser -> init
typedef struct Init_Struct {
    char *match_str;       // Data of matching string
    char *query_mode;      // Define the query mode('single word', 'boolean' or 'multiterm').
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
    int match_strs_num;    // number of matching strings
} JobOpt;

// jobControl -> threadCtl
typedef struct Thread_Ctl_Struct {
    char **match_strs;
    char *match_relations;
    char *match_mode;
    char *begin_at;
    float error_rate;
    int match_strs_num;
    int insensitive;
} ThreadOpt;

// threadCtl -> matching
// Ps: matching: threadId = 1~255, scoring: threadId = 0.
// 1. Control flags
typedef struct Matching_Opt {
    // for matching
    char **match_strs;
    char *match_mode;
    float error_rate;
    int match_strs_num;
    int insensitive;

    // for scoring
    char *match_relations;
} MatchOpt;
// 2. Data
typedef struct Matching_Base {
    char ***sample_records;    // All of the sample records.
    char **sample_column_name; // All of sample column name.
    int sample_length;
    int sample_col_num;        // number of sample columns.
} MatchBase;

// ThreadId = 1~255 -> ThreadId = 0
typedef struct Matching_Counter {
    int **matched_count; // x = matched_count[i][j] stand for a word(id = i) appeared in column(id = j) x times.
} MatchCount;

// matching -> threadCtl (callback)
typedef struct Matching_Result {
    char ***result_records; // All of the result records
    int *scores;
    int result_length;
    int result_col_num;
} MatchRes;

// threadCtl -> ranker(scorer)
typedef struct Ranking_info {
    char ***result_records;
    int *scores;
    int result_length;
    int result_col_num;
} RankInfo;

// ranker -> packer
typedef struct Packing_Opt {
    char ***result_records;
    char **output_column; // passthrough gpu?
    int output_column_num;
    int output_size;
    int output_length;
} PackOpt;
