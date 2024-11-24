//
//  main.c
//  trabalho-prog-v1
//
//  Created by Simão Oliveira on 22/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char diaSemana[10];         // Dia da semana (2feira, 3feira, etc.)
    char data[12];              // Data (ex: 18.11.2024)
    char pratoPeixe[100];       // Nome do prato de peixe
    int caloriasPeixe;          // Calorias do prato de peixe
    char pratoCarne[100];       // Nome do prato de carne
    int caloriasCarne;          // Calorias do prato de carne
    char pratoDieta[100];       // Nome do prato de dieta
    int caloriasDieta;          // Calorias do prato de dieta
    char pratoVegetariano[100]; // Nome do prato vegetariano
    int caloriasVegetariano;    // Calorias do prato vegetariano
} Ementa;

int countEmenta = 0;

void Menu() {
    system("clear");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║                ~ MENU PRINCIPAL ~              ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1 - Refeições do dia                          ║\n");
    printf("║  2 - Utentes por nº de funcionário             ║\n");
    printf("║  3 - Calorias por utente                       ║\n");
    printf("║  4 - Médias de calorias por dia                ║\n");
    printf("║  5 - Gerar ementa semanal                      ║\n");
    printf("║  0 - Sair                                      ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf(" Escolha uma opção: ");
}

void OpenEmenta()
{
    const char *cementa = "/Users/simao/Documents/PSI/Projeto/trabalho-prog-v1/trabalho-prog-v1/Ementa.txt";
    //const char *caminho = "Ementa.txt";
    FILE *ementa = fopen(cementa, "r");
    char text[255];
    Ementa dias[5];
    int index = 0;
    
    if (ementa == NULL)
    {
        printf("Não existem informações sobre a ementa!\n");
    }
    else
    {
        while(fgets(text, 255, ementa) != NULL)
        {
            char *token = strtok(text, ";");

            // Armazena os dados na struct correspondente
            if (token != NULL) strncpy(dias[index].diaSemana, token, sizeof(dias[index].diaSemana));
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].data, token, sizeof(dias[index].data));

            // Preenche o prato de peixe
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].pratoPeixe, token, sizeof(dias[index].pratoPeixe));
            token = strtok(NULL, ";");
            if (token != NULL) dias[index].caloriasPeixe = atoi(token);

            // Preenche o prato de carne
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].pratoCarne, token, sizeof(dias[index].pratoCarne));
            token = strtok(NULL, ";");
            if (token != NULL) dias[index].caloriasCarne = atoi(token);

            // Preenche o prato de dieta
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].pratoDieta, token, sizeof(dias[index].pratoDieta));
            token = strtok(NULL, ";");
            if (token != NULL) dias[index].caloriasDieta = atoi(token);

            // Preenche o prato vegetariano
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].pratoVegetariano, token, sizeof(dias[index].pratoVegetariano));
            token = strtok(NULL, ";");
            if (token != NULL) dias[index].caloriasVegetariano = atoi(token);

            index++;
    
        }
    }
    
    countEmenta = index;
    fclose(ementa);
    
    
    printf("%-10s%-20s%-12s%-20s%-12s%-20s%-12s%-20s%-12s\n",
           "Dia", "Prato Peixe", "Calorias", "Prato Carne", "Calorias",
           "Prato Dieta", "Calorias", "Vegetariano", "Calorias");

    printf("-----------------------------------------------------------------------------------------------\n");

    // Imprimir os dados no formato de tabela
    for (int i = 0; i < countEmenta; i++)
    {
        printf("%-10s%-20s%-12d%-20s%-12d%-20s%-12d%-20s%-12d\n",
        dias[i].diaSemana, dias[i].pratoPeixe, dias[i].caloriasPeixe,
        dias[i].pratoCarne, dias[i].caloriasCarne,
        dias[i].pratoDieta, dias[i].caloriasDieta,
        dias[i].pratoVegetariano, dias[i].caloriasVegetariano);
    }
}

int main() {
    
    OpenEmenta();
    int opcao;
    
    do {
        Menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Você escolheu a Opção 1.\n");
                break;
            case 2:
                printf("Você escolheu a Opção 2.\n");
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
