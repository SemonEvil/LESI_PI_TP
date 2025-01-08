/**
 * @file MostrarRefeicao.c
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

// Função que exibe as refeições do dia para um determinado dia fornecido pelo usuário
void MostrarRefeicao() 
{
    int sem;
    char dataInput[11];
    
    // Solicita ao usuário que insira uma data no formato DD/MM/AAAA
    printf("Insira uma data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput);
    
    // Se o usuário digitar "0", a função retorna sem fazer nada
    if (!strcmp(dataInput, "0"))
    {
        return;
    }
    
    // Substitui os delimitadores "-" ou "." por "/" para garantir que o formato esteja correto
    for (int i = 0; i < strlen(dataInput); i++) {
        if (dataInput[i] == '-' || dataInput[i] == '.') {
            dataInput[i] = '/';
        }
    }

    // Converte a data inserida pelo usuário em uma estrutura 'tm'
    struct tm dataEscolhida = {0};
    strptime(dataInput, "%d/%m/%Y", &dataEscolhida); 

    int found = 0;

    // Percorre todas as ementas e compara a data fornecida com a data da ementa
    for (int i = 0; i < countEmenta; i++) 
    {
        // Verifica se a data fornecida corresponde à data de alguma ementa
        if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0) 
        {
            found = 1;
            system("clear");  // Limpa a tela
            // Exibe o título com a data formatada
            printf("Refeições requeridas para o dia %02d/%02d/%d\n", 
                   ementa[i].data.tm_mday, 
                   ementa[i].data.tm_mon + 1, 
                   ementa[i].data.tm_year + 1900);
            printf("-------------------------------------------------------------------------------------------------------\n");
            printf("| Nº Func. | Nome                     | Dia da semana | Prato                                         |\n");
            printf("-------------------------------------------------------------------------------------------------------\n");

            char prato[999];

            // Exibe as refeições selecionadas para este dia
            for (int j = 0; j < countEsc; j++) 
            {
                // Verifica se a refeição é para o dia e semana selecionados
                if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0 && 
                    strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) 
                {
                    // Atribui o nome do prato baseado no tipo de prato escolhido
                    switch (escolhas[j].tipoPrato)
                    {
                        case 'P': strcpy(prato, ementa[i].pratoPeixe); break;
                        case 'C': strcpy(prato, ementa[i].pratoCarne); break;
                        case 'D': strcpy(prato, ementa[i].pratoDieta); break;
                        case 'V': strcpy(prato, ementa[i].pratoVegetariano); break;
                        default: strcpy(prato, "Indefinido"); break;
                    }

                    // Exibe os dados do funcionário e o prato escolhido em formato de tabela
                    printf("| %-8d | %-24s | %-13s | %-45s |\n", 
                           funcionarios[escolhas[j].numFuncionario - 1].numFuncionario, 
                           funcionarios[escolhas[j].numFuncionario - 1].nome, escolhas[j].diaSemana, 
                           prato);
                }
            }

            printf("-------------------------------------------------------------------------------------------------------\n");
            break;
        }
    }

    // Se nenhuma ementa foi encontrada para a data fornecida
    if (!found) 
    {
        printf("Não há ementa registrada para a data %s.\n", dataInput);
    }

    // Espera o usuário pressionar Enter antes de retornar ao menu
    printf("\nPressione Enter para voltar ao menu...");
    getchar();  // Limpa o buffer do teclado
}