// TRANSLATOR

#define LENOFCOMMANDLINE 100
#define LENOFREGARR 4
#define MAXPARAMLEN 15

// COMMANDLINE (CMD_)

#define DEF_CMD( name, num, ... ) \
    CMD_##name = num,

enum CMDS
{
    #include "easycommands.h"
    #include "complexcommands.h"

    RAX   = 1,
    RBX   = 2,
    RCX   = 3,
    RDX   = 4,

    CMD_NOCOMMAND = 0
};

#undef DEF_CMD

int determineCommand(char* command);
int paramDeterminator(char* param, FILE* source, FILE* distance,  int* translatorIp, int* commandLine, int numOfCommand);
void translator(FILE* source, FILE* distance, FILE* binarycode);

#include "translator.cpp"

