//
//  main.c
//  trabalho-prog-v1
//
//  Created by Simão Oliveira on 22/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Menu() {
    system("clear");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║                ~ MENU PRINCIPAL ~              ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1 - Refeições de um dia                       ║\n");
    printf("║  2 - Utentes por nº de funcionário             ║\n");
    printf("║  3 - Calorias por utente                       ║\n");
    printf("║  4 - Médias de calorias por dia                ║\n");
    printf("║  5 - Gerar ementa semanal                      ║\n");
    printf("║  0 - Sair                                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf(" Escolha uma opção: ");
}

int main() {
    int opcao;
    do {
        Menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Você escolheu a Opção 1.\n");
                break;
            case 2:
                pintf("Você escolheu a Opção 2.\n");
                break;
            case 3:
                printf("Você escolheu a Opção 3.\n");
                break;
            case 4:
                printf("Você escolheu a Opção 4.\n");
                break;
            case 5:
                printf("Você escolheu a Opção 5.\n");
                break;
            case 0:
                printf("A sair do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Captura o "Enter" restante no buffer
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
