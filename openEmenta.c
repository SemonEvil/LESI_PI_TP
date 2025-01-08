/**
 * @file openEmenta.c
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

void openEmenta() {
    // Caminho para o arquivo de ementa
    char *ementa_path = "ementa.txt";
    // Abre o arquivo para leitura
    FILE *f_ementa = fopen(ementa_path, "r");

    // Verifica se o arquivo foi aberto corretamente
    char text[255];  // Variável para armazenar cada linha lida do arquivo
    int index = 0;   // Índice para armazenar dados no array de ementas
    
    // Caso o arquivo não exista ou não seja aberto corretamente, exibe uma mensagem de erro
    if (f_ementa == NULL) 
    {
        printf("Não existem informações sobre a ementa!\n");
    } 
    else 
    {
        char dataStr[11];  // String para armazenar a data lida como string
        do 
        {
            // Lê os dados do arquivo e os armazena nas variáveis correspondentes
            // A função fscanf lê os dados no formato especificado (campo separado por ponto e vírgula)
            fscanf(f_ementa, "%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d;%[^;];%d\n", 
            ementa[index].diaSemana, dataStr, ementa[index].pratoPeixe, &ementa[index].caloriasPeixe,
            ementa[index].pratoCarne, &ementa[index].caloriasCarne, ementa[index].pratoDieta, &ementa[index].caloriasDieta,
            ementa[index].pratoVegetariano, &ementa[index].caloriasVegetariano);

            // Limpa a estrutura "data" da ementa antes de usá-la para garantir que não haja lixo de memória
            memset(&ementa[index].data, 0, sizeof(struct tm)); 

            // Converte a data lida de string para a estrutura tm (para trabalhar com datas no formato específico)
            strptime(dataStr, "%d.%m.%Y", &ementa[index].data);
            
            // Incrementa o índice para armazenar a próxima linha de dados na próxima posição do array
            index++;
        } while(!feof(f_ementa));   // Continua enquanto não chegar ao final do arquivo
    }

    // Atualiza o contador de ementas com o número de registros lidos
    countEmenta = index;

    // Fecha o arquivo após a leitura dos dados
    fclose(f_ementa);
}