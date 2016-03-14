

// parser -> init
typedef struct Init_Struct {
    ;
} InitOpt;

// init -> jobControl
typedef struct Job_Ctl_Struct {
    ;
} JobOpt;

// jobControl -> threadCtl
typedef struct thread_Ctl_Struct {
    ;
} ThreadOpt;

// threadCtl -> matching
// 1. Control flags
typedef struct Matching_Opt {
    ;
} MatchOpt;
// 2. Data
typedef struct Matching_Base {
    ;
} MatchBase;

// matching -> threadCtl (callback)
typedef struct Matching_Result {
    ;
} MatchRes;

// threadCtl -> ranker(scorer)
typedef struct Ranking_info {
    ;
} RankInfo;

// ranker -> packer
typedef struct Packing_Opt {
    ;
} PackOpt;
