// STACK

#define RESIZECOF 1.5
#define STCANARY 0xDEADDEAD
#define DATACANARY 0xFEED

typedef long int datatype;

typedef struct
{
    long long int stcan1;
    datatype* data;
    size_t size;
    size_t capacity;
    void (*printElem) (datatype data);
    void (*printElemInLogfile) (datatype data);
    long long int stcan2;
} stack;

// CPU

#define LENOFCOMMANDLINE 100
#define LENOFREGARR 4

typedef struct
{
    stack* stk;
    int regarr[LENOFREGARR];
    int* commandline;
    int translatorIP;

} cpu;

// TRANSLATOR

#define MAXPARAMLEN 15
#define MAXLENOFSPACE 10

// COMMANDLINE
/*  PUSH = 1
    POP = 2
    OUT = 3
    ADD = 4
    SUB = 5
    MUL = 6
    DIV = 7
    SQRT = 8
    IN = 9
    HLT = -1
    PUSHR = 101
    POPR = 102
    RAX = 1
    RBX = 2
    RCX = 3
    RDX = 4
*/

// VERIFICATION

enum typesOfErrors
{
        NULL_POINTER_OF_STACK = -1,
        NULL_POINTER_OF_DATA = -2,
        WRONG_C1 = 1,
        WRONG_C2 = 2,
        WRONG_DC1 = 3,
        WRONG_DC2 = 4,
        WRONG_HASH = 5,
        WRONG_SIZE = 6
};

// ALL FUNCTIONS

int verificator(stack* stk, FILE* logfile);
void stkconstructor(stack* stk, int capacity, void (*printFunc) (datatype data), void (*printFuncInLogfile) (datatype data));
void stkpush(stack* stk, datatype val);
void stkresize(stack* stk, double val);
void stkpop(stack* stk);
void stackdump(int statusOfVerification, stack* stk);
void translator(FILE* source, FILE* distance, FILE* binarycode);
void printstk(stack* stk);
void PrintLongInt (long int val);
void PrintLongIntLogfile (long int val);
void PrintInt (int val);
void PrintIntLogfile (int val);
void PrintDouble (double val);
void PrintDoubleLogfile (double val);
void PrintChar (char val);
void PrintCharLogfile (char val);

// INCLUDING FILES

#include "verification.cpp"
#include "stconstructor.cpp"
#include "pushpop.cpp"
#include "translator.cpp"






