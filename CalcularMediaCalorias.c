/**
 * @file CalcularMediaCalorias.c
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

// Função para converter uma estrutura `tm` em uma string no formato "DD/MM/AAAA".
void dataToSring(struct tm data, char dataf[]) {
    strftime(dataf, 11, "%d/%m/%Y", &data); // Formata a data e armazena em dataf.
}

// Função de comparação para ordenar datas em ordem crescente.
int compararPorDataC(const void *a, const void *b) {
    struct DiaCalorias *diaA = (struct DiaCalorias *)a;
    struct DiaCalorias *diaB = (struct DiaCalorias *)b;

    struct tm dataA = {0}, dataB = {0};
    strptime(diaA->data, "%d/%m/%Y", &dataA); // Converte string para struct tm.
    strptime(diaB->data, "%d/%m/%Y", &dataB);

    time_t timeA = mktime(&dataA); // Converte struct tm para time_t.
    time_t timeB = mktime(&dataB);

    // Retorna -1, 1 ou 0 dependendo da ordem.
    return (timeA < timeB) ? -1 : (timeA > timeB);
}

// Função para calcular a média de calorias consumidas em um intervalo de datas.
void CalcularMediaCalorias() {
    char dataInput1[11], dataInput2[11];
    
    // Solicita a primeira data ao usuário.
    printf("Insira uma 1ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput1);
    if (!strcmp(dataInput1, "0")) return; // Encerra se o usuário digitar "0".

    // Substitui possíveis delimitadores diferentes por "/".
    for (int i = 0; i < strlen(dataInput1); i++) {
        if (dataInput1[i] == '-' || dataInput1[i] == '.') dataInput1[i] = '/';
    }
    struct tm data1 = {0};
    strptime(dataInput1, "%d/%m/%Y", &data1); // Converte string para struct tm.

    // Solicita a segunda data ao usuário.
    printf("Insira uma 2ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput2);
    if (!strcmp(dataInput2, "0")) return;

    // Substitui delimitadores e converte para struct tm.
    for (int i = 0; i < strlen(dataInput2); i++) {
        if (dataInput2[i] == '-' || dataInput2[i] == '.') dataInput2[i] = '/';
    }
    struct tm data2 = {0};
    strptime(dataInput2, "%d/%m/%Y", &data2);

    // Determina qual data é o início (data mais antiga) e qual é o fim (data mais recente).
    time_t time1 = mktime(&data1);
    time_t time2 = mktime(&data2);
    struct tm dataInicio = time1 < time2 ? data1 : data2;
    struct tm dataFim = time1 < time2 ? data2 : data1;

    // Estrutura dinâmica para armazenar os dias com calorias.
    struct DiaCalorias *diasCalorias = NULL;
    int diasCount = 0;

    // Percorre as escolhas e a ementa para calcular calorias dentro do intervalo especificado.
    for (int i = 0; i < countEsc; i++) {
        for (int j = 0; j < countEmenta; j++) {
            if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0 && 
                difftime(mktime(&ementa[j].data), mktime(&dataInicio)) >= 0 &&
                difftime(mktime(&ementa[j].data), mktime(&dataFim)) <= 0) {
                
                // Verifica se a data já está na lista de resultados.
                int encontrado = -1;
                for (int k = 0; k < diasCount; k++) {
                    char dataStr[11];
                    dataToSring(ementa[j].data, dataStr); // Converte para string.
                    if (strcmp(diasCalorias[k].data, dataStr) == 0) {
                        encontrado = k;
                        break;
                    }
                }

                // Adiciona a nova data se ainda não existir na lista.
                if (encontrado == -1) {
                    diasCalorias = realloc(diasCalorias, (diasCount + 1) * sizeof(struct DiaCalorias));
                    strftime(diasCalorias[diasCount].data, 11, "%d/%m/%Y", &ementa[j].data);
                    strcpy(diasCalorias[diasCount].diaSemana, ementa[j].diaSemana);
                    diasCalorias[diasCount].totalCalorias = 0;
                    diasCalorias[diasCount].totalRefeicoes = 0;
                    encontrado = diasCount++;
                }

                // Incrementa as calorias e o total de refeições para a data.
                switch (escolhas[i].tipoPrato) {
                    case 'C': diasCalorias[encontrado].totalCalorias += ementa[j].caloriasCarne; break;
                    case 'P': diasCalorias[encontrado].totalCalorias += ementa[j].caloriasPeixe; break;
                    case 'D': diasCalorias[encontrado].totalCalorias += ementa[j].caloriasDieta; break;
                    case 'V': diasCalorias[encontrado].totalCalorias += ementa[j].caloriasVegetariano; break;
                }
                diasCalorias[encontrado].totalRefeicoes++;
            }
        }
    }

    // Limpa a tela e exibe os resultados.
    system("clear");
    if (diasCount == 0) {
        printf("Não existem dias com refeições no intervalo especificado.\n");
    } else {
        qsort(diasCalorias, diasCount, sizeof(struct DiaCalorias), compararPorDataC);

        char dI[11], dF[11];
        dataToSring(dataInicio, dI);
        dataToSring(dataFim, dF);

        printf("\nMédias de Calorias Consumidas entre o dia %s e %s\n", dI, dF);
        printf("-----------------------------------------------------------------------\n");
        printf("| Data       | Dia da Semana | Total de Refeições | Média de Calorias |\n");
        printf("-----------------------------------------------------------------------\n");

        for (int i = 0; i < diasCount; i++) {
            printf("| %-10s | %-12s  | %-17d  | %-17.2f |\n", 
                   diasCalorias[i].data,
                   diasCalorias[i].diaSemana, 
                   diasCalorias[i].totalRefeicoes, 
                   (float)diasCalorias[i].totalCalorias / diasCalorias[i].totalRefeicoes);
        }

        printf("-----------------------------------------------------------------------\n");
    }

    free(diasCalorias); // Liberta a memória alocada.
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}