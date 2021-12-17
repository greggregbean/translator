// TRANSLATOR

#define YES 1
#define NO 0

#define LENOFCOMMANDLINE 100
#define MAXCOMMANDLEN 10
#define MAXPARAMLEN 15

#define LENOFLABELBUFFER 100
#define MAXLABELNAME 5

typedef struct
{
    char name [MAXLABELNAME];
    int num;

} label;

// COMMANDLINE

#define DEF_CMD( name, num, ... ) \
    CMD_##name = num,

enum CMDS
{
    #include "easycommands.h"
    #include "pushpop.h"
    #include "jumps.h"

    RAX   = 1,
    RBX   = 2,
    RCX   = 3,
    RDX   = 4,

    CMD_NOCOMMAND = 0
};

#undef DEF_CMD

int determineCommand(char* command);
int paramDeterminator(char* param, FILE* source, FILE* distance,  int* translatorIp, int* commandLine, int numOfCommand);
void translator(FILE* source, FILE* distance, FILE* binarycode, label* labelBuffer);

#include "translator.cpp"

