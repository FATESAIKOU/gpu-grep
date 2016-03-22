extern "C" {

#include "../../cmncateStruct.h"
#include "../../libs.h"
#include <cuda.h>

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base);

MatchRes *matchRecords(MatchOpt *match_opt, MatchBase *match_base) {
    MatchRes *match_res = (MatchRes*) malloc(sizeof(MatchRes));

    return match_res;
}

}
