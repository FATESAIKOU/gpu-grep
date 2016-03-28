extern "C" {

#include "../../cmncateStruct.h"
#include "../../commonInc.h"
#include <cuda.h>

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);
MatchBase *genMatchBase(ThreadOpt *thread_opt, char *filename);
RecordInfo *readRecordsInfo(char *file_content, char *begin, int *entry);
char *readFile(char *filename, size_t *file_len);
size_t getFileSize(char *filename);
int getAttrId(char *str);
void checkBase(MatchBase *match_base, int attr_num);


MatchOpt *genMatchOpt(ThreadOpt *thread_opt) {
    MatchOpt *match_opt = (MatchOpt*) malloc(sizeof(MatchOpt));

    match_opt->match_strs = thread_opt->match_strs;
    match_opt->match_mode = thread_opt->match_mode;
    match_opt->error_rate = thread_opt->error_rate;
    match_opt->match_str_num = thread_opt->match_str_num;
    match_opt->insensitive = thread_opt->insensitive;

    match_opt->match_relations = thread_opt->match_relations;

    return match_opt;
}

MatchBase *genMatchBase(ThreadOpt *thread_opt, char *filename) {
    MatchBase *match_base = (MatchBase*) malloc(sizeof(MatchBase));
    size_t file_len;
    char *file_content = readFile(filename, &file_len);
    int record_num;

    match_base->datas = file_content;
    match_base->record_info = readRecordsInfo(file_content, thread_opt->begin_at, &record_num);
    match_base->rec_entry = record_num;
    match_base->data_len = file_len;

    return match_base;
}

RecordInfo *readRecordsInfo(char *file_content, char *begin, int *entry) {
    int limit = 1024;
    int begin_id = getAttrId(begin);

    // initialize all of the record_info
    RecordInfo *records_info = (RecordInfo*) malloc(sizeof(RecordInfo) * limit);
    memset(records_info, 0, sizeof(RecordInfo) * limit);

    char *attr = strtok(file_content, "\n");
    int record_id = 0;
    int attr_id;
    while(attr != NULL) {
        attr_id = getAttrId(attr);
        if (attr_id == begin_id) {
            record_id ++;
            if (record_id == limit) {
                limit += 1024;
                records_info = (RecordInfo*) realloc(records_info, sizeof(RecordInfo) * limit);
            }
            memset(records_info + record_id, 0, sizeof(RecordInfo));
            records_info[record_id].record_offset = attr - file_content;
        } else if (attr_id != -1) {
            records_info[record_id].attr_offset[attr_id] = attr - file_content;
        }

        attr = strtok(NULL, "\n");
    }

    records_info = (RecordInfo*) realloc(records_info, sizeof(RecordInfo) * record_id);
    *entry = record_id + 1;

    return records_info;
}

char *readFile(char *filename, size_t *file_len) {
    int fd = open(filename, O_RDONLY, 0644);
    *file_len = getFileSize(filename) + 1;

    char *file_content = (char*) mmap(NULL, *file_len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    file_content[*file_len] = '\0';

    return file_content;
}

size_t getFileSize(char *filename) {
    struct stat st;
    stat(filename, &st);

    return (st.st_size);
}

int getAttrId(char *str) {
    if (str[0] != '@') return -1;

    switch (str[1]) {
        case 'i': return 0;
        case 't': return 1;
        case 'p': return 2;
        case 'c': return 3;
        case 'd': return 4;
        case 'f': return 5;
        case '$': return 6;
        case 'a': return 7;
        case 'k': return 8;
        case '_': return 9;
    }

    return -1;
}

void checkBase(MatchBase *match_base, int attr_num) {
    char *base = match_base->datas;
    RecordInfo *rec_info = match_base->record_info;
    int rec_num = match_base->rec_entry;
    int i, j;

    int offset;
    for (i = 0; i < rec_num; i ++) {
        printf("Record %d---\n", i);
        for (j = 0; j < attr_num; j ++) {
            offset = rec_info[i].attr_offset[j];
            if (offset != 0) {
                printf("%s\n", base + offset);
            }
        }
    }
}

}
