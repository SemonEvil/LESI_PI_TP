/**
 * @file main.c
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

// Variáveis globais que armazenam o número total de funcionários, ementas e escolhas.
int countFunc = 0;
int countEmenta = 0;
int countEsc = 0;

int main() {
    // Inicializa os dados carregando as informações de arquivos externos.
    openFuncionarios();
    openEscolhas();
    openEmenta();

    int opcao; // Variável para armazenar a escolha do menu.

    do {
        Menu(); // Exibe o menu principal.
        scanf("%d", &opcao); // Lê a opção do usuário.
        getchar(); // Limpa o buffer de entrada.

        // Processa a opção escolhida pelo usuário.
        switch (opcao) {
            case 1: // Apresenta as refeições requeridas por utentes em um dado dia.
                system("clear");
                MostrarRefeicao();
                break;

            case 2: // Lista os utentes ordenados por número de funcionário com resumo semanal.
                system("clear");
                ListarUtentes();
                break;

            case 3: // Lista as refeições e calorias de um utente em um período.
                system("clear");
                printf("Digite o número do utente para exibir a ementa: ");

                int n1;
                scanf("%d", &n1);

                if (n1 == 0) { // Sai da opção caso o usuário insira 0.
                    break;
                }

                system("clear");
                ListarRefeicoes(n1); // Chama a função para listar as refeições.
                break;

            case 4: // Calcula as médias de calorias consumidas por dia em um período.
                system("clear");
                CalcularMediaCalorias();
                break;

            case 5: // Gera a tabela da ementa semanal de um determinado utente.
                system("clear");
                printf("Digite o número do utente para exibir a ementa: ");

                int n2;
                scanf("%d", &n2);

                if (n2 == 0) { // Sai da opção caso o usuário insira 0.
                    break;
                }

                system("clear");
                TabelaEmenta(n2); // Chama a função para exibir a tabela da ementa.
                break;

            case 0: // Encerra o programa.
                printf("A sair do programa...\n");
                // Desaloca memória, se necessário.
                break;

            default: // Opção inválida.
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            getchar(); // Captura o "Enter" restante no buffer.
        }

    } while (opcao != 0); // Continua o loop até o usuário escolher sair.

    system("clear");
    return 0;
}