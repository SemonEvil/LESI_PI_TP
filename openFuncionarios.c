/**
 * @file openFuncionarios.c
 * @author Simão & Vitor
 * @brief 
 * @version 0.1
 * @date 2024-12-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "juntar.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void openFuncionarios() {
    FILE *f_funcionarios = fopen("funcionarios.txt", "r");
    if (!f_funcionarios) {
        perror("Não existem informações sobre as escolhas!\n");
    }

    int index = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), f_funcionarios)) {
        if (sscanf(linha, "%d;%[^;];%d;%d", &funcionarios[index].numFuncionario, funcionarios[index].nome, &funcionarios[index].NIF, &funcionarios[index].telefone) == 4)
        {
            index++;
        }
    }

    countFunc = index;
    fclose(f_funcionarios);
}