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

//Compara duas refeições pela data para ordenação.
int compararPorDataR(const void *a, const void *b) {
    struct tm dataA = {0}, dataB = {0};
    struct Refeicao *refA = (struct Refeicao *)a;
    struct Refeicao *refB = (struct Refeicao *)b;

    // Converte as strings de data em estruturas `tm`.
    strptime(refA->data, "%d/%m/%Y", &dataA);
    strptime(refB->data, "%d/%m/%Y", &dataB);

    // Converte `tm` em time_t para facilitar a comparação.
    time_t timeA = mktime(&dataA);
    time_t timeB = mktime(&dataB);

    // Retorna a diferença entre os tempos (ordem crescente).
    return (timeA - timeB);
}

//Lista as refeições de um funcionário específico, ordenadas por data.
void ListarRefeicoes(int numFuncionario) {
    printf("Refeições do Funcionário nº %d:\n", numFuncionario);
    printf("-------------------------------------------------------------------------\n");
    printf("| Data       | Dia da Semana | Tipo de Prato     | Calorias             |\n");
    printf("-------------------------------------------------------------------------\n");

    struct Refeicao *refeicoes = NULL; // Ponteiro para armazenar as refeições dinamicamente.
    int refeicoesCount = 0;           // Contador para o número de refeições armazenadas.

    // Percorre todas as escolhas de refeições.
    for (int i = 0; i < countEsc; i++) {
        if (escolhas[i].numFuncionario == numFuncionario) { // Verifica se a escolha pertence ao funcionário.
            for (int j = 0; j < countEmenta; j++) {
                if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0) { // Verifica se o dia coincide.

                    // Determina o tipo de prato escolhido e as calorias associadas.
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

                    // Aloca espaço para a nova refeição e armazena as informações.
                    refeicoes = realloc(refeicoes, (refeicoesCount + 1) * sizeof(struct Refeicao));
                    strftime(refeicoes[refeicoesCount].data, 11, "%d/%m/%Y", &ementa[j].data); // Converte a data.
                    strcpy(refeicoes[refeicoesCount].diaSemana, ementa[j].diaSemana);
                    strcpy(refeicoes[refeicoesCount].tipoPrato, prato);
                    refeicoes[refeicoesCount].calorias = calorias;

                    refeicoesCount++;
                }
            }
        }
    }

    // Ordena as refeições pela data (se houver).
    if (refeicoesCount > 0) {
        qsort(refeicoes, refeicoesCount, sizeof(struct Refeicao), compararPorDataR);
    }

    // Exibe as refeições ou uma mensagem caso não haja resultados.
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
    free(refeicoes); // Liberta a memória alocada para a lista de refeições.

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}