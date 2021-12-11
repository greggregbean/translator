#define DEF_CMD(strCommand, numCommand)                       \
    if (stricmp(command, #strCommand) == 0) return numCommand; \
    else

int determineCommand(char* command)
{
    #include "easycommands.h"
    #include "complexcommands.h"
    /*else*/
    {
        if(command[0] != '\0')
            printf("You are all zasrantsy: \"%s\" \n", command);
    }
}

#undef DEF_CMD

int paramDeterminator(char* param, FILE* source, FILE* distance,  int* translatorIp, int* commandLine, int numOfCommand)
{
        if (strcmp(param, "rax") == 0)
        {
            fprintf(distance, "%d 1\n", numOfCommand);
            commandLine[(*translatorIp)++] = numOfCommand;
            commandLine[(*translatorIp)++] = 1;
            getc(source);
            return 1;
        }

        else if (strcmp(param, "rbx") == 0)
        {
            fprintf(distance, "%d 2\n", numOfCommand);
            commandLine[(*translatorIp)++] = numOfCommand;
            commandLine[(*translatorIp)++] = 2;
            getc(source);
            return 1;
        }

        else if (strcmp(param, "rcx") == 0)
        {
            fprintf(distance, "%d 3\n", numOfCommand);
            commandLine[(*translatorIp)++] = numOfCommand;
            commandLine[(*translatorIp)++] = 3;
            getc(source);
            return 1;
        }

        else if (strcmp(param, "rdx") == 0)
        {
            fprintf(distance, "%d 4\n", numOfCommand);
            commandLine[(*translatorIp)++] = numOfCommand;
            commandLine[(*translatorIp)++] = 4;
            getc(source);
            return 1;
        }

        return 0;
}

void translator(FILE* source, FILE* distance, FILE* binarycode)
{
    int commandLine [LENOFCOMMANDLINE] = {'\0'};
    int translatorIp = 0;

    char symbol = '\0';
    int numoflines = 0;

    while ((symbol = getc(source)) != EOF)
    {
        if (symbol == '\n')
        {
            numoflines ++;
        }
    }

    fseek(source, 0, SEEK_SET);

    for (int i = 0; i < numoflines-1; i++)
    {
        char command[5] = {'\0'};

        int k = 0;

        fscanf(source, "%s", &command);

        printf("Current command: \"%s\" \n", command);

        char spaceOrEnter = getc(source);

        int typeOfCommand = determineCommand(command);

        printf("Type of command: %d \n", typeOfCommand);

        if (typeOfCommand == CMD_PUSH)
        {
                char param [MAXPARAMLEN] = {'\0'};

                fscanf(source, "%s", &param);

                printf("Current param: \"%s\" \n", param);

                int result = paramDeterminator(param, source, distance,  &translatorIp, commandLine, CMD_PUSHR);

                printf("paramDeterminator() returned: %d \n", result);

                if (result)
                    continue;

                else
                {
                    fprintf(distance, "1 ");
                    commandLine[translatorIp++] = 1;

                    int paramlen = 0;
                    while (param[paramlen] != '\0')
                    {
                        paramlen++;
                    }

                    fseek(source, -paramlen, SEEK_CUR);

                    int num = 0;
                    fscanf(source, "%d", &num);
                    fprintf(distance, "%d\n", num);
                    commandLine[translatorIp++] = num;

                    getc(source);
                    continue;
                }

            }

            else if (typeOfCommand == CMD_POP)
            {

                if (spaceOrEnter == '\n')
                {
                    fprintf(distance, "2\n");
                    commandLine[translatorIp++] = 2;
                    continue;
                }

                char param [MAXPARAMLEN] = {'\0'};

                fscanf(source, "%s", &param);

                paramDeterminator(param, source, distance,  &translatorIp, commandLine, CMD_POPR);

                continue;

            }

            #define DEF_CMD(strCommand, numCommand)     \
            else if (typeOfCommand == numCommand)        \
            {                                             \
                fprintf(distance, "%d\n", numCommand);     \
                commandLine[translatorIp++] = numCommand;   \
                continue;                                    \
            }                                                 \

            #include "easycommands.h"

            #undef DEF_CMD

            else if (typeOfCommand == CMD_NOCOMMAND)
            {
                continue;
            }
    }

    fprintf(distance, "TRANSLATOR IP: %d \n", translatorIp);
    fprintf(distance, "COMMANDLINE: ");

    int i = 0;
    while (commandLine[i] != '\0')
    {
        fprintf(distance, "%d ", commandLine[i]);
        i++;
    }

    fprintf(distance, "\n");

    fwrite(commandLine, sizeof(int), translatorIp, binarycode);

    printf("TRANSLATION HAS BEEN COMPLETED:\n"
           "Numerical code is in numericalcode.txt\n"
           "Binary code is in binarycode.bin\n");
}

