/**
 * @file ListarUtentes.c
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


void ListarUtentes()
{
    // Ordenar funcionários por número (decrescente)
    for (int i = 0; i < countFunc - 1; i++) {
        for (int j = i + 1; j < countFunc; j++) {
            if (funcionarios[i].numFuncionario < funcionarios[j].numFuncionario) {
                Funcionarios temp = funcionarios[i];

                funcionarios[i] = funcionarios[j];
                funcionarios[j] = temp;
            }
        }
    }

    // Cabeçalho
    printf("Lista de Utentes:\n");
    printf("-------------------------------------------------------------------\n");
    printf("| Nº Func. | Nome                      | Nº Refeições | Custo (€) |\n");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < countFunc; i++) {
        int totalRefeicoes = 0;
        float totalCusto = 0.0;

        // Processar as escolhas do funcionário
        for (int j = 0; j < countEsc; j++) {
            if (escolhas[j].numFuncionario == funcionarios[i].numFuncionario) {
                totalRefeicoes++;

                // Determinar custo com base no tipo de prato
                float precoPrato = 6.0;

                totalCusto += precoPrato;
            }
        }

        // Exibir dados do funcionário
        if (totalRefeicoes > 0) {
            printf("| %-8d | %-24s  | %-12d | %-9.2f |\n",
                   funcionarios[i].numFuncionario,
                   funcionarios[i].nome,
                   totalRefeicoes,
                   totalCusto);
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("\nPressione Enter para voltar ao menu...");  
}