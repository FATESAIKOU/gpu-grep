#include "commonInc.h"
#include "libs.h"

int main(int argc, char *argv[])
{
    InitOpt *init_opt = (InitOpt*)parseArgs(argc, argv);

    printArgs((InitOpt*)init_opt);

    return 0;
}
