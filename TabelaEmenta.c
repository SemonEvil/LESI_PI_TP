/**
 * @file TabelaEmenta.c
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

void TabelaEmenta(int numeroFuncionario) 
{
    printf("Ementa Semanal para o Utente #%d\n", numeroFuncionario);
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
    printf("| Dia       | Prato Peixe       | Calorias | Prato Carne       | Calorias | Prato Dieta       | Calorias | Prato Vegetariano       | Calorias |\n");
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");

    for (int j = 0; j < countEsc; j++) {
        if (escolhas[j].numFuncionario == numeroFuncionario) {
            // Encontrar a ementa correspondente ao dia da escolha
            for (int i = 0; i < countEmenta; i++) {
                if (strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) {
                    // Imprimir os dados do dia com base na escolha
                    printf("| %-10s", ementa[i].diaSemana);

                    // Preencher as colunas com base na escolha
                    if (escolhas[j].tipoPrato == 'P') 
                    {
                        printf("| %-18s| %-8d| %-18s| %-8s| %-18s| %-8s| %-23s| %-8s|\n",
                            ementa[i].pratoPeixe, ementa[i].caloriasPeixe, "-", "-", "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'C') 
                    {
                        printf("| %-18s| %-8s| %-18s| %-8d| %-18s| %-8s| %-23s| %-8s|\n",
                            "-", "-", ementa[i].pratoCarne, ementa[i].caloriasCarne, "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'D')
                    {
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8d| %-23s| %-8s|\n",
                            "-", "-", "-", "-", ementa[i].pratoDieta, ementa[i].caloriasDieta, "-", "-");
                    } else if (escolhas[j].tipoPrato == 'V') 
                    {
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8s| %-23s| %-8d|\n",
                            "-", "-", "-", "-", "-", "-", ementa[i].pratoVegetariano, ementa[i].caloriasVegetariano);
                    }

                    break; // Encontrou o dia correspondente, pode sair do loop da ementa
                }
            }
            printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
        }
    }

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}