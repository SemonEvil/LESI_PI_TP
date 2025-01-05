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

void MostrarRefeicao() 
{
    int sem;
    char dataInput[11];
    printf("Insira uma data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput);
    
    if (!strcmp(dataInput, "0"))
    {
        return;
    }
    
    // Substituir os delimitadores (caso sejam "-" ou ".") por "/"
    for (int i = 0; i < strlen(dataInput); i++) {
        if (dataInput[i] == '-' || dataInput[i] == '.') {
            dataInput[i] = '/';
        }
    }

    struct tm dataEscolhida = {0};
    strptime(dataInput, "%d/%m/%Y", &dataEscolhida); 

    int found = 0;
    for (int i = 0; i < countEmenta; i++) 
    {
        // Comparando a data fornecida com a data da ementa
        if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0) 
        {
            found = 1;
            system("clear");
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
                // Verifica se a refeição é para o dia selecionado
                if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0 && 
                    strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) 
                {
                    // Atribui o prato de acordo com o tipo
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

    if (!found) 
    {
        printf("Não há ementa registrada para a data %s.\n", dataInput);
    }

    printf("\nPressione Enter para voltar ao menu...");
    getchar();  // Para limpar o buffer do teclado
}