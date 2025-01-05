/**
 * @file openEmenta.c
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

void openEmenta() {
    // abrir o ficheiro
    char *ementa_path = "ementa.txt";
    FILE *f_ementa = fopen(ementa_path, "r");

    // verificar se existe ementa e guardar dados
    char text[255];
    int index = 0;
    
    if (f_ementa == NULL) 
    {
        printf("Não existem informações sobre a ementa!\n");
    } 
    else 
    {
        char dataStr[11];
        do 
        {
            fscanf(f_ementa, "%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d;%[^;];%d\n", 
            ementa[index].diaSemana, dataStr, ementa[index].pratoPeixe, &ementa[index].caloriasPeixe,
            ementa[index].pratoCarne, &ementa[index].caloriasCarne, ementa[index].pratoDieta, &ementa[index].caloriasDieta,
            ementa[index].pratoVegetariano, &ementa[index].caloriasVegetariano);

            memset(&ementa[index].data, 0, sizeof(struct tm)); // Limpar a estrutura antes de usar
            strptime(dataStr, "%d.%m.%Y", &ementa[index].data);

            index++;
        } while(!feof(f_ementa));   
    }

    countEmenta = index;
    fclose(f_ementa);
}