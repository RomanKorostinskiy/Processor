#include <stdio.h>
#include <stdlib.h>
#include "../GeneralInclude/General.h"

int main()
{
    FILE* fp = nullptr;
    fp = fopen("../table.txt", "w");

    fprintf(fp, "CMD_PUSH dec:                  %d     CMD_PUSH hex:                  %x\n", CMD_PUSH, CMD_PUSH);
    fprintf(fp, "CMD_PUSH|ARG_CONS dec:         %d    CMD_PUSH|ARG_CONS hex:         %x\n", CMD_PUSH | ARG_CONS, CMD_PUSH | ARG_CONS);
    fprintf(fp, "CMD_PUSH|ARG_REG dec:          %d    CMD_PUSH|ARG_REG hex:          %x\n", CMD_PUSH | ARG_REG, CMD_PUSH | ARG_REG);
    fprintf(fp, "CMD_PUSH|ARG_REG|ARG_CONS dec: %d    CMD_PUSH|ARG_REG|ARG_CONS hex: %x\n", CMD_PUSH | ARG_REG | ARG_CONS, CMD_PUSH | ARG_REG | ARG_CONS);

    fprintf(fp, "\nCMD_POP|ARG_REG dec:           %d     CMD_POP|ARG_REG hex:          %x\n", CMD_POP | ARG_REG, CMD_POP | ARG_REG);

    fclose(fp);
}