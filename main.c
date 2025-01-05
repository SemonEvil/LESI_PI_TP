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

int countFunc = 0;
int countEmenta = 0;
int countEsc = 0;

int main() {
    openFuncionarios();
    openEscolhas();
    openEmenta();

    int opcao;
    
    do {
        Menu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1: //Apresentação das refeições requeridas pelos utentes para um dado dia, para conferência no ato de servir o prato.
                    //Deve conter o número de funcionário, o nome, o prato escolhido e o dia da semana.
                system("clear");
                MostrarRefeicao();
                break;
            case 2: //Listagem dos utentes, ordenada por ordem decrescente do número de funcionário, com o número de refeições servidas 
                    //na semana e o total da despesa, para ser entregue no serviço de Recursos Humanos, para efeitos de desconto no salário.
                system("clear");
                ListarUtentes();
                break;
            case 3: //Listar as refeições e a quantidade de calorias de um utente ao longo de um determinado período.
                system("clear");
                printf("Digite o número do utente para exibir a ementa: ");

                int n1;
                scanf("%d", &n1);

                 if (n1 == 0)
                {
                    break;
                }

                system("clear");
                ListarRefeicoes(n1);
                break;
            case 4: //Calcular as médias das calorias consumidas por refeição por cada dia da semana, em todo o espaço, 
                    //ao longo de um determinado período.
                system("clear");
                CalcularMediaCalorias();
                break;
            case 5: //Gerar a tabela correspondente à ementa semanal usufruída por um determinado utente
                system("clear");
                printf("Digite o número do utente para exibir a ementa: ");

                int n2;
                scanf("%d", &n2);

                if (n2 == 0)
                {
                    break;
                }

                system("clear");
                TabelaEmenta(n2);
                break;
            case 0:
                printf("A sair do programa...\n");
                //free(funcionarios);
                //free(escolhas);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            getchar(); // Captura o "Enter" restante no buffer
        }

    } while (opcao != 0);
    system("clear");
    return 0;
}