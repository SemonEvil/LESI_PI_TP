/**
 * @file openEscolhas.c
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

void openEscolhas() {
    // abrir o ficheiro
    char *escolhas_path = "escolhas.txt";
    FILE *f_escolhas = fopen(escolhas_path, "r");
    
    int index = 0;
    
    if (f_escolhas == NULL) {
        printf("Não existem informações sobre as escolhas!\n");
    } else {
        do
        {
            fscanf(f_escolhas,"%[^;];%d;%c\n",escolhas[index].diaSemana,&escolhas[index].numFuncionario,&escolhas[index].tipoPrato);
            index++;
            
        } while (!feof(f_escolhas));
    }

    countEsc = index;
    fclose(f_escolhas);
}