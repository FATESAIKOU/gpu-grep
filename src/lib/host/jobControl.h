#ifndef JOBCTL_INCLUDED
#define JOBCTL_INCLUDED
#include "../../cmncateStruct.h"

ThreadOpt *genThreadOpt(JobOpt *job_opt);

void printThreadArgs(ThreadOpt *thread_opt);

#endif
