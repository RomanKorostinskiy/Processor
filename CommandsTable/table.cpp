#include <stdio.h>
#include <stdlib.h>
#include "../GeneralInclude/General.h"

int main()
{
    FILE* fp = nullptr;
    fp = fopen("../table.txt", "w");

    fprintf(fp, "CMD_PUSH dec:                          %d      CMD_PUSH hex:                            %x\n", CMD_PUSH, CMD_PUSH);
    fprintf(fp, "CMD_PUSH|ARG_CONS dec:                 %d     CMD_PUSH|ARG_CONS hex:                  %x\n", CMD_PUSH | ARG_CONS, CMD_PUSH | ARG_CONS);
    fprintf(fp, "CMD_PUSH|ARG_CONS|ARG_RAM dec:         %d    CMD_PUSH|ARG_CONS|ARG_RAM hex:          %x\n", CMD_PUSH | ARG_CONS | ARG_RAM, CMD_PUSH | ARG_CONS | ARG_RAM);
    fprintf(fp, "CMD_PUSH|ARG_REG dec:                  %d     CMD_PUSH|ARG_REG hex:                   %x\n", CMD_PUSH | ARG_REG, CMD_PUSH | ARG_REG);
    fprintf(fp, "CMD_PUSH|ARG_REG|ARG_RAM dec:          %d    CMD_PUSH|ARG_REG|ARG_RAM hex:           %x\n", CMD_PUSH | ARG_REG | ARG_RAM, CMD_PUSH | ARG_REG | ARG_RAM);
    fprintf(fp, "CMD_PUSH|ARG_REG|ARG_CONS dec:         %d     CMD_PUSH|ARG_REG|ARG_CONS hex:          %x\n", CMD_PUSH | ARG_REG | ARG_CONS, CMD_PUSH | ARG_REG | ARG_CONS);
    fprintf(fp, "CMD_PUSH|ARG_REG|ARG_CONS|ARG_RAM dec: %d    CMD_PUSH|ARG_REG|ARG_CONS|ARG_RAM  hex: %x\n", CMD_PUSH | ARG_REG | ARG_CONS | ARG_RAM, CMD_PUSH | ARG_REG | ARG_CONS | ARG_RAM);

    fprintf(fp, "\nCMD_POP dec:                          %d      CMD_POP hex:                           %x\n", CMD_POP, CMD_POP);
    fprintf(fp, "CMD_POP|ARG_CONS|ARG_RAM dec:         %d    CMD_POP|ARG_CONS|ARG_RAM hex:          %x\n", CMD_POP | ARG_CONS | ARG_RAM, CMD_POP | ARG_CONS | ARG_RAM);
    fprintf(fp, "CMD_POP|ARG_REG dec:                  %d     CMD_POP|ARG_REG hex:                   %x\n", CMD_POP | ARG_REG, CMD_POP | ARG_REG);
    fprintf(fp, "CMD_POP|ARG_REG|ARG_RAM dec:          %d    CMD_POP|ARG_REG|ARG_RAM hex:           %x\n", CMD_POP | ARG_REG | ARG_RAM, CMD_POP | ARG_REG | ARG_RAM);
    fprintf(fp, "CMD_POP|ARG_REG|ARG_CONS|ARG_RAM dec: %d    CMD_POP|ARG_REG|ARG_CONS|ARG_RAM  hex: %x\n", CMD_POP | ARG_REG | ARG_CONS | ARG_RAM, CMD_POP | ARG_REG | ARG_CONS | ARG_RAM);

    fprintf(fp, "\nCMD_JMP dec:  %d      CMD_JMP hex:  %x\n", CMD_JMP, CMD_JMP);
    fprintf(fp, "CMD_JA dec:   %d     CMD_JA hex:   %x\n", CMD_JA, CMD_JA);
    fprintf(fp, "CMD_JAE dec:  %d     CMD_JAE hex:  %x\n", CMD_JAE, CMD_JAE);
    fprintf(fp, "CMD_JB dec:   %d     CMD_JB hex:   %x\n", CMD_JB, CMD_JB);
    fprintf(fp, "CMD_JBE dec:  %d     CMD_JBE hex:  %x\n", CMD_JBE, CMD_JBE);
    fprintf(fp, "CMD_JE dec:   %d     CMD_JE hex:   %x\n", CMD_JE, CMD_JE);
    fprintf(fp, "CMD_JNE dec:  %d     CMD_JNE hex:  %x\n", CMD_JNE, CMD_JNE);
    fprintf(fp, "CMD_CALL dec: %d     CMD_CALL hex: %x\n", CMD_CALL, CMD_CALL);
    fprintf(fp, "CMD_RET dec:  %d     CMD_RET hex:  %x\n", CMD_RET, CMD_RET);

    fclose(fp);
}