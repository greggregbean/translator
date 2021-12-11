#define DEF_CMD(strCommand, numCommand) \
    if (stricmp(command, #strCommand) == 0) return numCommand; \
    else

int determineCommand(char* command)
{
    #include "commands.h"
    /*else*/ printf("You are all zasrantsy. \n");
}

#undef DEF_CMD


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

        char spaceOrEnter = getc(source);

        int typeOfCommand = determineCommand(command);

        if (typeOfCommand == CMD_PUSH)
        {
                char param [MAXPARAMLEN] = {'\0'};

                fscanf(source, "%s", &param);

                if (strcmp(param, "rax") == 0)
                {
                    fprintf(distance, "101 1\n");
                    commandLine[translatorIp++] = 101;
                    commandLine[translatorIp++] = 1;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rbx") == 0)
                {
                    fprintf(distance, "101 2\n");
                    commandLine[translatorIp++] = 101;
                    commandLine[translatorIp++] = 2;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rcx") == 0)
                {
                    fprintf(distance, "101 3\n");
                    commandLine[translatorIp++] = 101;
                    commandLine[translatorIp++] = 3;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rdx") == 0)
                {
                    fprintf(distance, "101 4\n");
                    commandLine[translatorIp++] = 101;
                    commandLine[translatorIp++] = 4;
                    getc(source);
                    continue;
                }

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

                if (strcmp(param, "rax") == 0)
                {
                    fprintf(distance, "102 1\n");
                    commandLine[translatorIp++] = 102;
                    commandLine[translatorIp++] = 1;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rbx") == 0)
                {
                    fprintf(distance, "102 2\n");
                    commandLine[translatorIp++] = 102;
                    commandLine[translatorIp++] = 2;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rcx") == 0)
                {
                    fprintf(distance, "102 3\n");
                    commandLine[translatorIp++] = 102;
                    commandLine[translatorIp++] = 3;
                    getc(source);
                    continue;
                }

                else if (strcmp(param, "rdx") == 0)
                {
                    fprintf(distance, "102 4\n");
                    commandLine[translatorIp++] = 102;
                    commandLine[translatorIp++] = 4;
                    getc(source);
                    continue;
                }

            }

            else if (typeOfCommand == CMD_OUT)
            {
                fprintf(distance, "3\n");
                commandLine[translatorIp++] = 3;
                continue;
            }

            else if (typeOfCommand == CMD_ADD)
            {
                fprintf(distance, "4\n");
                commandLine[translatorIp++] = 4;
                continue;
            }

            else if (typeOfCommand == CMD_SUB)
            {
                fprintf(distance, "5\n");
                commandLine[translatorIp++] = 5;
                continue;
            }

            else if (typeOfCommand == CMD_MUL)
            {
                fprintf(distance, "6\n");
                commandLine[translatorIp++] = 6;
                continue;
            }

            else if (typeOfCommand == CMD_DIV)
            {
                fprintf(distance, "7\n");
                commandLine[translatorIp++] = 7;
                continue;
            }

            else if (typeOfCommand == CMD_SQRT)
            {
                fprintf(distance, "8\n");
                commandLine[translatorIp++] = 8;
                continue;
            }

            else if (typeOfCommand == CMD_IN)
            {
                fprintf(distance, "9\n");
                commandLine[translatorIp++] = 9;
                continue;
            }

            else if (typeOfCommand == CMD_HLT)
            {
                fprintf(distance, "-1\n");
                commandLine[translatorIp++] = -1;
            }

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

