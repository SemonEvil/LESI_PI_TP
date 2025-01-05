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

void dataToSring(struct tm data, char dataf[])
{
    strftime(dataf, 11, "%d/%m/%Y", &data);
}

int compararPorDataC(const void *a, const void *b) {
    struct DiaCalorias *diaA = (struct DiaCalorias *)a;
    struct DiaCalorias *diaB = (struct DiaCalorias *)b;

    struct tm dataA = {0};
    struct tm dataB = {0};

    // Converter strings para struct tm
    strptime(diaA->data, "%d/%m/%Y", &dataA);
    strptime(diaB->data, "%d/%m/%Y", &dataB);

    // Comparar as datas
    time_t timeA = mktime(&dataA);
    time_t timeB = mktime(&dataB);

    if (timeA < timeB) return -1;
    if (timeA > timeB) return 1;
    return 0;
}

void CalcularMediaCalorias() {
    char dataInput1[11], dataInput2[11];
    printf("Insira uma 1ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput1);

    if (!strcmp(dataInput1, "0")) {
        return;
    }

    // Substituir delimitadores por "/"
    for (int i = 0; i < strlen(dataInput1); i++) {
        if (dataInput1[i] == '-' || dataInput1[i] == '.') {
            dataInput1[i] = '/';
        }
    }

    struct tm data1 = {0};
    strptime(dataInput1, "%d/%m/%Y", &data1); 

    printf("Insira uma 2ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput2);

    if (!strcmp(dataInput2, "0")) {
        return;
    }

    // Substituir delimitadores por "/"
    for (int i = 0; i < strlen(dataInput2); i++) {
        if (dataInput2[i] == '-' || dataInput2[i] == '.') {
            dataInput2[i] = '/';
        }
    }

    struct tm data2 = {0};
    strptime(dataInput2, "%d/%m/%Y", &data2);

    // Ordenar as datas para determinar o início e o fim
    time_t time1 = mktime(&data1);
    time_t time2 = mktime(&data2);

    struct tm dataInicio = time1 < time2 ? data1 : data2;
    struct tm dataFim = time1 < time2 ? data2 : data1;

    // Utilizar uma estrutura dinâmica para armazenar os resultados
    struct DiaCalorias *diasCalorias = NULL;
    int diasCount = 0;

    // Percorrer as escolhas de refeições
    for (int i = 0; i < countEsc; i++) {
        for (int j = 0; j < countEmenta; j++) {
            // Verificar se a escolha corresponde à ementa e está no intervalo de datas
            if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0 && 
                difftime(mktime(&ementa[j].data), mktime(&dataInicio)) >= 0 &&
                difftime(mktime(&ementa[j].data), mktime(&dataFim)) <= 0) {
                
                // Verificar se a data já está nos resultados
                int encontrado = -1;
                for (int k = 0; k < diasCount; k++) 
                {
                    char dataStr[11];
                    dataToSring(ementa[j].data, dataStr);
                    if (strcmp(diasCalorias[k].data, dataStr) == 0) { // Comparar pela data completa
                        encontrado = k;
                        break;
                    }
                }

                // Se a data ainda não existe, adicionar à estrutura dinâmica
                if (encontrado == -1) {
                    diasCalorias = realloc(diasCalorias, (diasCount + 1) * sizeof(struct DiaCalorias));
                    strftime(diasCalorias[diasCount].data, 11, "%d/%m/%Y", &ementa[j].data); // Adicionar a data
                    strcpy(diasCalorias[diasCount].diaSemana, ementa[j].diaSemana);
                    diasCalorias[diasCount].totalCalorias = 0;
                    diasCalorias[diasCount].totalRefeicoes = 0;
                    encontrado = diasCount;
                    diasCount++;
                }

                // Incrementar as calorias e refeições para a data encontrada
                switch (escolhas[i].tipoPrato) {
                    case 'C':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasCarne;
                        break;
                    case 'P':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasPeixe;
                        break;
                    case 'D':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasDieta;
                        break;
                    case 'V':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasVegetariano;
                        break;
                }
                diasCalorias[encontrado].totalRefeicoes++;
            }
        }
    }

    // Exibir os resultados após todos os cálculos
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

    free(diasCalorias);
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}