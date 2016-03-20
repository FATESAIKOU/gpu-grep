#include "../../cmncateStruct.h"
#include "../../commonInc.h"

// define

extern "C" MatchOpt *genMatchOpt(ThreadOpt *thread_opt);

extern "C" MatchBase *genMatchBase(char *filename);

__host__ char *ungets(char *str, FILE *fptr);

__host__ char *getAttribute(FILE *fptr, char *end_str);

__host__ char **getRecord(FILE *fptr);

extern "C" void readFile(char *filename, MatchBase *match_base);

// implement

extern "C" MatchOpt *genMatchOpt(ThreadOpt *thread_opt) {
    MatchOpt *sample = (MatchOpt*) malloc(sizeof(MatchOpt));

    sample->match_strs = thread_opt->match_strs;
    sample->match_mode = thread_opt->match_mode;
    sample->error_rate = thread_opt->error_rate;
    sample->match_str_num = thread_opt->match_str_num;
    sample->insensitive = thread_opt->insensitive;

    sample->match_relations = thread_opt->match_relations;

    return sample;
}

extern "C" MatchBase *genMatchBase(char *filename) {
    MatchBase *sample = (MatchBase*) malloc(sizeof(MatchBase));

    readFile(filename, sample);

    return sample;
}

__host__ char *ungets(char *str, FILE *fptr) {
    char *end_of_str = strchr(str, '\0');

    while (str <= --end_of_str) {
        ungetc(*end_of_str, fptr);
    }

    return str;
}

__host__ char *getAttribute(FILE *fptr, const char *end_str) {
    int now_len = 1024000;
    char *attribute = (char *) malloc(sizeof(char) * now_len);
    char *end_of_attribute = attribute;

    while (fgets(end_of_attribute, 1023, fptr) != NULL) {
        if ((end_of_attribute = strstr(end_of_attribute, end_str)) != NULL) {
            *( ungets(end_of_attribute, fptr) ) = '\0';
            break;
        } else {
            end_of_attribute = strchr(attribute, '\0');
        }
    }

    if ( !sscanf(attribute, "%*[^:]:%[^\n]\n", attribute) ) attribute[0] = '\0';
    attribute = (char*) realloc(attribute, sizeof(char) * (end_of_attribute - attribute) + 3);

    return attribute;
}

__host__ char **getRecord(FILE *fptr) {
    char **record = (char**) malloc(sizeof(char*) * 12);

    getAttribute(fptr, "@id");
    record[0] = getAttribute(fptr, "@published");
    record[1] = getAttribute(fptr, "@updated");
    record[2] = getAttribute(fptr, "@title");
    record[3] = getAttribute(fptr, "@content");
    record[4] = getAttribute(fptr, "@author");
    record[5] = getAttribute(fptr, "@keyword");
    record[6] = getAttribute(fptr, "@favorite");
    record[7] = getAttribute(fptr, "@viewCount");
    record[8] = getAttribute(fptr, "@duration");
    record[9] = getAttribute(fptr, "@category");
    record[10] = getAttribute(fptr, "@src");
    record[11] = getAttribute(fptr, "@\n");

    return record;
}

extern "C" void readFile(char *filename, MatchBase *match_base) {
    FILE *fptr = fopen(filename, "r");

    int limit = 1024;
    char tmp[1024];
    char ***records = (char***) malloc(sizeof(char**) * limit);
    int i = 0;

    while ( (fgets(tmp, 1024, fptr)) != NULL ) {
        if (limit == i) {
            limit *= 2;
            records = (char***) realloc(records, sizeof(char**) * limit);
        }

        records[i] = getRecord(fptr);

        i ++;
    }

    match_base->sample_records = records;
    match_base->record_num = i;
}

