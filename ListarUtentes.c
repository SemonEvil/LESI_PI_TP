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

// Função para listar os utentes (funcionários) ordenados por número de funcionário
void ListarUtentes()
{
    // Ordenação dos funcionários por número de funcionário (decrescente)
    for (int i = 0; i < countFunc - 1; i++) {
        for (int j = i + 1; j < countFunc; j++) {
            if (funcionarios[i].numFuncionario < funcionarios[j].numFuncionario) {
                // Troca dos funcionários de posição se o funcionário i for menor que o funcionário j
                Funcionarios temp = funcionarios[i];
                funcionarios[i] = funcionarios[j];
                funcionarios[j] = temp;
            }
        }
    }

    // Exibe o cabeçalho da tabela de utentes
    printf("Lista de Utentes:\n");
    printf("-------------------------------------------------------------------\n");
    printf("| Nº Func. | Nome                      | Nº Refeições | Custo (€) |\n");
    printf("-------------------------------------------------------------------\n");

    // Loop para percorrer todos os funcionários
    for (int i = 0; i < countFunc; i++) {
        int totalRefeicoes = 0;  // Contador de refeições feitas pelo funcionário
        float totalCusto = 0.0;  // Total do custo das refeições do funcionário

        // Processa as escolhas de refeição de cada funcionário
        for (int j = 0; j < countEsc; j++) {
            if (escolhas[j].numFuncionario == funcionarios[i].numFuncionario) {
                totalRefeicoes++;  // Aumenta o número de refeições feitas

                // Determina o custo da refeição com base no tipo de prato
                float precoPrato = 6.0;  // Define o preço fixo de cada prato (pode ser ajustado conforme necessário)
                totalCusto += precoPrato;  // Acumula o custo total
            }
        }

        // Exibe os dados do funcionário (somente se ele fez refeições)
        if (totalRefeicoes > 0) {
            printf("| %-8d | %-24s  | %-12d | %-9.2f |\n",
                   funcionarios[i].numFuncionario,  // Número do funcionário
                   funcionarios[i].nome,            // Nome do funcionário
                   totalRefeicoes,                  // Número total de refeições
                   totalCusto);                     // Custo total das refeições
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("\nPressione Enter para voltar ao menu...");  // Mensagem de retorno ao menu
}