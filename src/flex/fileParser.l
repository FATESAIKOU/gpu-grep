%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../cmncateStruct.h"

    char *content;

    int record_limit;
    int record_counter;

    int record_attr_num;
    int record_attr_counter;

    char ***records;

    void getAttribute(char *str, int changing);
%}

%%
^@id:.*            { getAttribute(yytext, 1);}
^@published:.*     { getAttribute(yytext, 0);}
^@updated:.*       { getAttribute(yytext, 0);}
^@title:.*         { getAttribute(yytext, 0);}
^@content:.*       { getAttribute(yytext, 0);}
^@author:.*        { getAttribute(yytext, 0);}
^@keyword:.*       { getAttribute(yytext, 0);}
^@favoriteCount:.* { getAttribute(yytext, 0);}
^@viewCount:.*     { getAttribute(yytext, 0);}
^@duration:.*      { getAttribute(yytext, 0);}
^@category:.*      { getAttribute(yytext, 0);}
^@src:.*           { getAttribute(yytext, 0);}

^@\n    {}
.*   {}

%%

void getAttribute(char *str, int changing) {
    if (changing) {
        record_attr_counter = 0;
        records[++ record_counter] = (char**) malloc(sizeof(char*) * record_attr_num);

        if (record_counter == record_limit) {
            record_limit += 1024;
            records = (char***) realloc(records, sizeof(char**) * record_limit);
        }
    }

    content = strchr(str, ':') + 1;
    records[record_counter][record_attr_counter ++] = strdup(content);
}

void readFile(char *filename, MatchBase *match_base) {
    record_limit = 1024;
    record_attr_num = 12;
    record_counter = -1;
    record_attr_counter = 12;
    records = (char***) malloc(sizeof(char**) * record_limit);

    yyin = fopen(filename, "r");

    yylex();

    records = (char***) realloc(records, sizeof(char**) * (record_counter + 1));
    match_base->sample_records = records;
    match_base->record_num = record_limit;
}
