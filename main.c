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
    char diaSemana[10];         // dia da semana (2feira, 3feira, etc.)
    char data[12];              // data (ex: 18.11.2024)
    char pratoPeixe[100];       // nome do prato de peixe
    int caloriasPeixe;          // calorias do prato de peixe
    char pratoCarne[100];       // nome do prato de carne
    int caloriasCarne;          // calorias do prato de carne
    char pratoDieta[100];       // nome do prato de dieta
    int caloriasDieta;          // calorias do prato de dieta
    char pratoVegetariano[100]; // nome do prato vegetariano
    int caloriasVegetariano;    // calorias do prato vegetariano
} Ementa;

typedef struct {
    char diaSemana[10];         // dia da semana (2feira, 3feira, etc.)
    int numFuncionario;         // número do funcionário (ex: 0001, 0002, etc.)
    char tipoPrato;             // tipo do prato (C- prato de carne, P - prato peixe, D – dieta, V - vegetariano)
} Escolhas;

Ementa dias[5];
FILE *f_funcionarios;
FILE *f_ementa;
FILE *f_escolhas;
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

void openEmenta()
{
    // abrir o ficheiro
    char *ementa_path = "Ementa.txt";
    f_ementa = fopen(ementa_path, "r");

    // verificar se existe ementa e guardar dados
    char text[255];
    int index = 0;
    
    if (f_ementa == NULL)
    {
        printf("Não existem informações sobre a ementa!\n");
    }
    else
    {
        while(fgets(text, 255, f_ementa) != NULL)
        {
            char *token = strtok(text, ";");

            // Armazena os dados na struct correspondente
            if (token != NULL) strncpy(dias[index].diaSemana, token, sizeof(dias[index].diaSemana));
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].data, token, sizeof(dias[index].data));
            // remover \n do dia[i].diaSemana
            dias[index].diaSemana[strcspn(dias[index].diaSemana, "\n")] = 0;

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
    fclose(f_ementa);
}

void openEscolhas()
{
    // abrir o ficheiro
    char *escolhas_path = "Escolhas.txt";
    f_escolhas = fopen(escolhas_path, "r");

    // verificar se existe ementa e guardar dados
    char text[255];
    int index = 0;
    
    if (f_ementa == NULL)
    {
        printf("Não existem informações sobre a ementa!\n");
    }
    else
    {
        while(fgets(text, 255, f_ementa) != NULL)
        {
            char *token = strtok(text, ";");

            // Armazena os dados na struct correspondente
            if (token != NULL) strncpy(dias[index].diaSemana, token, sizeof(dias[index].diaSemana));
            token = strtok(NULL, ";");
            if (token != NULL) strncpy(dias[index].data, token, sizeof(dias[index].data));
            // remover \n do dia[i].diaSemana
            dias[index].diaSemana[strcspn(dias[index].diaSemana, "\n")] = 0;

            if (token != NULL) strncpy(dias[index].diaSemana, token, sizeof(dias[index].diaSemana));
            token = strtok(NULL, ";");
            index++;
        }
    }
    
    countEmenta = index;
    fclose(f_ementa);
}

void ShowRefeicaoPorDia()
{
    
}

int main() 
{
    openEmenta();
    int opcao;
    
    do {
        Menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: //Apresentação das refeições requeridas pelos utentes para um dado dia, para conferência no ato de servir o prato. 
                    //Deve conter o número de funcionário, o nome, o prato escolhido e o dia da semana.
                printf("Você escolheu a Opção 1.\n");
                ShowRefeicaoPorDia();
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
