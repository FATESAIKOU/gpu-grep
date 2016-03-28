#ifndef THRDCTL_INCLUDED
#define THRDCTL_INCLUDED

MatchOpt *genMatchOpt(ThreadOpt *thread_opt);
MatchBase *genMatchBase(ThreadOpt *thread_opt, char *filename);
RecordInfo *readRecordsInfo(char *file_content, char *begin, int *entry);
char *readFile(char *filename);
size_t getFileSize(char *filename);
int getAttrId(char *str);
void checkBase(MatchBase *match_base, int attr_num);

#endif
