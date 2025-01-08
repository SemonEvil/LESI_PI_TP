/**
 * @file openFuncionarios.c
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

void openFuncionarios() {
    // Tenta abrir o ficheiro "funcionarios.txt" no modo leitura
    FILE *f_funcionarios = fopen("funcionarios.txt", "r");

    // Verifica se o ficheiro foi aberto corretamente
    if (!f_funcionarios) {
        // Caso o ficheiro não exista ou haja erro na abertura, exibe uma mensagem de erro
        perror("Não existem informações sobre as escolhas!\n");
    }

    // Variáveis para controlar a leitura e armazenamento dos dados
    int index = 0;          // Índice para armazenar os funcionários
    char linha[256];        // Buffer para ler cada linha do ficheiro

    // Loop para ler o ficheiro linha por linha
    while (fgets(linha, sizeof(linha), f_funcionarios)) {
        // Lê os dados de cada linha e armazena nas variáveis da estrutura de funcionários
        // O formato esperado da linha é: <número do funcionário>;<nome>;<NIF>;<telefone>
        if (sscanf(linha, "%d;%[^;];%d;%d", 
            &funcionarios[index].numFuncionario, 
            funcionarios[index].nome, 
            &funcionarios[index].NIF, 
            &funcionarios[index].telefone) == 4)
        {
            // Incrementa o índice para armazenar o próximo funcionário na próxima posição
            index++;
        }
    }

    // Atualiza o contador de funcionários com o número de registros lidos
    countFunc = index;
    
    // Fecha o ficheiro após a leitura
    fclose(f_funcionarios);
}