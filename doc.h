// TRANSLATOR

#define LENOFCOMMANDLINE 100
#define LENOFREGARR 4
#define MAXPARAMLEN 15

// COMMANDLINE (CMD_)

#define DEF_CMD( name, num, ... ) \
    CMD_##name = num,

enum CMDS
{
    #include "commands.h"

    RAX   = 1,
    RBX   = 2,
    RCX   = 3,
    RDX   = 4
};

#undef DEF_CMD

int determineCommand(char* command);
void translator(FILE* source, FILE* distance, FILE* binarycode);

#include "translator.cpp"

