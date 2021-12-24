void DumpCommandLine (int* CommandLine, int translatorIp)
{
    printf ("--------------------------------------------\n");

    for (int i = 0; i < translatorIp; i++)
    {
        printf("%03d ", i);
    }

    printf("\n");

    for (int i = 0; i < translatorIp; i++)
    {
        printf("%03d ", CommandLine[i]);
    }

    printf("\n");

    printf ("--------------------------------------------\n");
}

int determineCommand(char* command)
{
    #define DEF_CMD(strCommand, numCommand)                       \
        if (stricmp(command, #strCommand) == 0) return numCommand; \
        else

    #include "easycommands.h"
    #include "jumps.h"
    #include "pushpop.h"

    #undef DEF_CMD

    /*else*/
    {
        if (command[0] != '\0')
            printf("WRONG COMMAND: \"%s\" \n", command);
        return 0;
    }

}

int labelDeterminator(FILE* source,
                      char* nameOfLabel, int labelAdress,
                      label* labelBuffer, int* labelsSize)
{
        if (nameOfLabel[0] == ':')
        {
            nameOfLabel++;
        }

        int i = 0;

        for (i = 0; i < (*labelsSize); i++)
        {
            if (strcmp(nameOfLabel, labelBuffer[i].name) == 0)
            {
                return labelBuffer[i].num;
            }
        }

        strcpy(labelBuffer[*labelsSize].name, nameOfLabel);

        labelBuffer[*labelsSize].num = labelAdress;

        printf("New label: \"%s\" (%d) \n", labelBuffer[*labelsSize].name, labelBuffer[*labelsSize].num);

        (*labelsSize)++;

        return -1;
}


void jumpDeterminator(FILE* source, FILE* distance,  int* translatorIp, int* commandLine, label* labelBuffer, int* labelsSize)
{
        fprintf(distance, "%d ", CMD_JMP);

        commandLine[(*translatorIp)++] = CMD_JMP;

        char nameOfLabel [MAXLABELNAME] = {'\0'};

        fscanf(source, "%s", nameOfLabel);

        printf("Name of label: \"%s\" \n", nameOfLabel);

        int addr = labelDeterminator(source,
                                     nameOfLabel, -1,
                                     labelBuffer, labelsSize);

        commandLine[(*translatorIp)++] = addr;

        fprintf(distance, "%d\n", addr);

}

int paramDeterminator(char* param, FILE* source, FILE* distance,  int* translatorIp, int* commandLine, int numOfCommand)
{
        #define DEF_REG(name, num)                            \
            if(stricmp(param, #name) == 0)                     \
            {                                                   \
                fprintf(distance, "%d %d \n", numOfCommand, num);\
                commandLine[(*translatorIp)++] = numOfCommand;    \
                commandLine[(*translatorIp)++] = num;              \
                getc(source);                                       \
                return 1;                                            \
            }                                                         \
            else

        #include "registers.h"

        #undef DEF_REG

        /*else*/
            return 0;
}

void translator(FILE* source, FILE* distance, FILE* binarycode, label* labelBuffer)
{
    int labelsSize = 0;

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

    for (int lineNum = 0; lineNum < numoflines-1; DumpCommandLine (commandLine, translatorIp), lineNum++)
    {
        printf("\nTranslatorIP: %d \n", translatorIp);

        char command[MAXCOMMANDLEN] = {'\0'};

        fscanf(source, "%s", command);



        if (command[0] == ':')
        {
            printf("There is a label: \"%s\" \n", command);

            labelDeterminator(source,
                              command, translatorIp,
                              labelBuffer, &labelsSize);



            continue;
        }

        printf("Current command: \"%s\" \n", command);

        char spaceOrEnter = getc(source);

        int typeOfCommand = determineCommand(command);

        printf("Type of command: %d \n", typeOfCommand);

        if (typeOfCommand == CMD_PUSH)
        {
                char param [MAXPARAMLEN] = {'\0'};

                fscanf(source, "%s", param);

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
                    fprintf(distance, "%d\n", CMD_POP);
                    commandLine[translatorIp++] = CMD_POP;
                    continue;
                }

                char param [MAXPARAMLEN] = {'\0'};

                fscanf(source, "%s", param);

                printf("Current param: \"%s\" \n", param);

                int result = paramDeterminator(param, source, distance,  &translatorIp, commandLine, CMD_POPR);

                printf("paramDeterminator() returned: %d \n", result);

                continue;

            }

            #define DEF_CMD(strCommand, numCommand)         \
                else if (typeOfCommand == numCommand)        \
                {                                             \
                    fprintf(distance, "%d\n", numCommand);     \
                    commandLine[translatorIp++] = numCommand;   \
                    continue;                                    \
                }                                                 \

            #include "easycommands.h"

            #undef DEF_CMD

            else if (typeOfCommand == CMD_JMP)
            {
                jumpDeterminator(source, distance, &translatorIp, commandLine, labelBuffer, &labelsSize);

                continue;
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
