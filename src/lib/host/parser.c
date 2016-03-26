#include "../../cmncateStruct.h"
#include "../../commonInc.h"

InitOpt *genInitOpt() {
    InitOpt *sample = (InitOpt*) malloc(sizeof(InitOpt));

    sample->filename          = NULL;
    sample->match_str         = NULL;
    sample->query_mode        = "single_word";
    sample->rank_mode         = "desc";
    sample->match_mode        = "prefix";
    sample->begin_at          = "id";
    sample->output_column     = NULL;
    sample->output_column_num = COLUMN_NUM;
    sample->error_rate        = 0.0;
    sample->insensitive       = 0;
    sample->output_size       = 800;
    sample->output_length     = 10;

    return sample;
}

char **parseStrings(char *strs, int *str_num, const char *delim) {
    char *token;

    char **parsed_strs = (char**) malloc( sizeof(char*) * (*str_num) );
    int i;

    token = strtok(strs, delim);
    for (i = 0; i < COLUMN_NUM && token != NULL; i ++) {
        parsed_strs[i] = strdup(token);

        token = strtok(NULL, delim);
    }

    parsed_strs = (char**)realloc(parsed_strs, sizeof(char*) * i);
    (*str_num) = i;

    return parsed_strs;
}

InitOpt *parseArgs(int argc, char *argv[]) {
    InitOpt *init_opt = genInitOpt();

    int cmd_opt = 0;
    while ( (cmd_opt = getopt(argc, argv, "f:b:q:d:iL:r:O:S:wp")) != -1 ) {
        switch (cmd_opt) {
            case 'f': init_opt->filename = strdup(optarg); break;
            case 'b': init_opt->begin_at = strdup(optarg); break;
            case 'q': init_opt->query_mode = strdup(optarg); break;
            case 'd': init_opt->error_rate = atof(optarg); break;
            case 'i': init_opt->insensitive = 1; break;
            case 'L': init_opt->output_length = atoi(optarg); break;
            case 'r': init_opt->rank_mode = strdup(optarg); break;
            case 'S': init_opt->output_size = atoi(optarg); break;
            case 'O': init_opt->output_column = parseStrings(optarg, &(init_opt->output_column_num), ",");
                    break;
            case 'w': init_opt->match_mode = "word"; break;
            case 'p': // just like the default 'prefix', so do nothing
            default:
                break;
        }
    }

    init_opt->match_str = strdup(argv[optind]);

    if ( !checkOpt(init_opt) ) {
        exit(2);
    }

    return init_opt;
}

int checkOpt(InitOpt *init_opt) {
    // I'm tired...
    return 1;
}

void printArgs(InitOpt *init_opt) {
    printf("----InitOpt----\n");
    printf("\tfilename: %s\n", init_opt->filename);
    printf("\tmatch_str: %s\n", init_opt->match_str);
    printf("\tquery_mode: %s\n", init_opt->query_mode);
    printf("\trank_mode: %s\n", init_opt->rank_mode);
    printf("\tmatch_mode: %s\n", init_opt->match_mode);
    printf("\tbegin_at: %s\n", init_opt->begin_at);
    printf("\toutput_column:\n");
    int i;
    for (i = 0; i < init_opt->output_column_num && init_opt->output_column != NULL; i++) {
        printf("\t\t%s\n", init_opt->output_column[i]);
    }
    printf("\terror_rate: %f\n", init_opt->error_rate);
    printf("\tinsensitive: %d\n", init_opt->insensitive);
    printf("\toutput_size: %d(byte)\n", init_opt->output_size);
    printf("\toutput_length: %d\n", init_opt->output_length);
    printf("---------------\n");
}
