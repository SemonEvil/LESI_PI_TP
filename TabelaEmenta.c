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

// Função que gera a tabela semanal de ementa para um utente específico
void TabelaEmenta(int numeroFuncionario) 
{
    // Exibe o cabeçalho da tabela para o utente selecionado
    printf("Ementa Semanal para o Utente #%d\n", numeroFuncionario);
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
    printf("| Dia       | Prato Peixe       | Calorias | Prato Carne       | Calorias | Prato Dieta       | Calorias | Prato Vegetariano       | Calorias |\n");
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");

    // Loop para percorrer todas as escolhas dos funcionários
    for (int j = 0; j < countEsc; j++) {
        // Verifica se a escolha corresponde ao número do funcionário fornecido
        if (escolhas[j].numFuncionario == numeroFuncionario) {
            // Loop para encontrar a ementa correspondente ao dia da semana da escolha
            for (int i = 0; i < countEmenta; i++) {
                if (strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) {
                    // Exibe o nome do dia da semana
                    printf("| %-10s", ementa[i].diaSemana);

                    // Preenche as colunas da tabela de acordo com o prato escolhido
                    if (escolhas[j].tipoPrato == 'P') 
                    {
                        // Caso o prato seja de peixe, preenche as colunas correspondentes
                        printf("| %-18s| %-8d| %-18s| %-8s| %-18s| %-8s| %-23s| %-8s|\n",
                            ementa[i].pratoPeixe, ementa[i].caloriasPeixe, "-", "-", "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'C') 
                    {
                        // Caso o prato seja de carne, preenche as colunas correspondentes
                        printf("| %-18s| %-8s| %-18s| %-8d| %-18s| %-8s| %-23s| %-8s|\n",
                            "-", "-", ementa[i].pratoCarne, ementa[i].caloriasCarne, "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'D')
                    {
                        // Caso o prato seja de dieta, preenche as colunas correspondentes
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8d| %-23s| %-8s|\n",
                            "-", "-", "-", "-", ementa[i].pratoDieta, ementa[i].caloriasDieta, "-", "-");
                    } else if (escolhas[j].tipoPrato == 'V') 
                    {
                        // Caso o prato seja vegetariano, preenche as colunas correspondentes
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8s| %-23s| %-8d|\n",
                            "-", "-", "-", "-", "-", "-", ementa[i].pratoVegetariano, ementa[i].caloriasVegetariano);
                    }

                    break; // Encontrou o dia correspondente, pode sair do loop da ementa
                }
            }
            printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
        }
    }
    // Mensagem de retorno ao menu
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}