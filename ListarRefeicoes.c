/**
 * @file ListarRefeicoes.c
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

int compararPorDataR(const void *a, const void *b)
{
    struct tm dataA = {0}, dataB = {0};
    struct Refeicao *refA = (struct Refeicao *)a;
    struct Refeicao *refB = (struct Refeicao *)b;

    strptime(refA->data, "%d/%m/%Y", &dataA);
    strptime(refB->data, "%d/%m/%Y", &dataB);

    time_t timeA = mktime(&dataA);
    time_t timeB = mktime(&dataB);

    return (timeA - timeB);
}

void ListarRefeicoes(int numFuncionario)
{
    printf("Refeições do Funcionário nº %d:\n", numFuncionario);
    printf("-------------------------------------------------------------------------\n");
    printf("| Data       | Dia da Semana | Tipo de Prato     | Calorias             |\n");
    printf("-------------------------------------------------------------------------\n");


    struct Refeicao *refeicoes = NULL;
    int refeicoesCount = 0;


    for (int i = 0; i < countEsc; i++) {
        // Verificar se o registro pertence ao funcionário
        if (escolhas[i].numFuncionario == numFuncionario) {
            for (int j = 0; j < countEmenta; j++) {
                if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0) {

                    // Determinar o prato e calorias
                    char *prato;
                    int calorias = 0;

                    if (escolhas[i].tipoPrato == 'C') {
                        prato = "Carne";
                        calorias = ementa[j].caloriasCarne;
                    } else if (escolhas[i].tipoPrato == 'P') {
                        prato = "Peixe";
                        calorias = ementa[j].caloriasPeixe;
                    } else if (escolhas[i].tipoPrato == 'D') {
                        prato = "Dieta";
                        calorias = ementa[j].caloriasDieta;
                    } else if (escolhas[i].tipoPrato == 'V') {
                        prato = "Vegetariano";
                        calorias = ementa[j].caloriasVegetariano;
                    }

                    // Armazenar as informações da refeição na estrutura dinâmica
                    refeicoes = realloc(refeicoes, (refeicoesCount + 1) * sizeof(struct Refeicao));

                    strftime(refeicoes[refeicoesCount].data, 11, "%d/%m/%Y", &ementa[j].data);
                    strcpy(refeicoes[refeicoesCount].diaSemana, ementa[j].diaSemana);
                    strcpy(refeicoes[refeicoesCount].tipoPrato, prato);
                    refeicoes[refeicoesCount].calorias = calorias;

                    refeicoesCount++;
                }
            }
        }
    }

    // Ordenar as refeições pela data
    if (refeicoesCount > 0) {
        qsort(refeicoes, refeicoesCount, sizeof(struct Refeicao), compararPorDataR);
    }

    // Exibir os resultados
    if (refeicoesCount == 0) {
        printf("Nenhuma refeição encontrada para o funcionário nº %d.\n", numFuncionario);
    } else {
        for (int i = 0; i < refeicoesCount; i++) {
            printf("| %-10s | %-13s | %-17s | %-20d |\n",
                   refeicoes[i].data,
                   refeicoes[i].diaSemana,
                   refeicoes[i].tipoPrato,
                   refeicoes[i].calorias);
        }
    }

    printf("-------------------------------------------------------------------------\n");
    free(refeicoes);

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}