/**
 * @file openEscolhas.c
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

void openEscolhas() {
    // Caminho do ficheiro das escolhas
    char *escolhas_path = "escolhas.txt";
    
    // Tenta abrir o ficheiro no modo leitura
    FILE *f_escolhas = fopen(escolhas_path, "r");
    
    // Índice para controlar a posição no array de escolhas
    int index = 0;
    
    // Verifica se o ficheiro foi aberto corretamente
    if (f_escolhas == NULL) {
        // Se o ficheiro não existir ou não puder ser aberto, exibe uma mensagem de erro
        printf("Não existem informações sobre as escolhas!\n");
    } else {
        // Loop para ler todas as linhas do ficheiro até o final
        do
        {
            // Lê os dados da linha atual e os armazena na estrutura 'escolhas'
            // 'fscanf' lê até encontrar o caractere ';' e atribui os valores às variáveis
            fscanf(f_escolhas, "%[^;];%d;%c\n", 
            escolhas[index].diaSemana,     // Lê o dia da semana
            &escolhas[index].numFuncionario,  // Lê o número do funcionário
            &escolhas[index].tipoPrato);    // Lê o tipo do prato (P, C, D, V)

            // Incrementa o índice para armazenar os próximos dados na próxima posição
            index++;
            
        } while (!feof(f_escolhas));  // Continua até o fim do ficheiro
    }

    // Atualiza o contador de escolhas com o número de elementos lidos
    countEsc = index;
    
    // Fecha o ficheiro após a leitura
    fclose(f_escolhas);
}