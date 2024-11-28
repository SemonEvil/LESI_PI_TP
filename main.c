#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numFuncionario;         // número do funcionário (ex: 0001, 0002, etc.)
    char nome[100];             // nome do funcionário
    int NIF;                    // NIF do funcionário
    int telefone;               // número de telefone do funcionário
} Funcionarios;

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


// variáveis globais
Ementa ementa[5];
Escolhas escolhas[999];
Funcionarios funcionarios[999];

FILE *f_funcionarios;
FILE *f_ementa;
FILE *f_escolhas;

int countFunc = 0;
int countEmenta = 0;
int countEsc = 0;

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

void openFuncionarios() {
     // abrir o ficheiro
    char *funcionarios_path = "Funcionarios.txt";
    f_funcionarios = fopen(funcionarios_path, "r");

    int index = 0;

    if (f_funcionarios == NULL) {
        printf("Não existem informações sobre as escolhas!\n");
    } else {
        do
        {
            fscanf(f_funcionarios, "%d;%[^;];%d;%d\n", 
                  &funcionarios[index].numFuncionario, 
                  funcionarios[index].nome, 
                  &funcionarios[index].NIF, 
                  &funcionarios[index].telefone);
            index++;
            
        } while (!feof(f_funcionarios));
    }

    countFunc = index;
    fclose(f_funcionarios);
}

void openEscolhas() {
    // abrir o ficheiro
    char *escolhas_path = "Escolhas.txt";
    f_escolhas = fopen(escolhas_path, "r");
    
    int index = 0;
    
    if (f_escolhas == NULL) {
        printf("Não existem informações sobre as escolhas!\n");
    } else {
        do
        {
            fscanf(f_escolhas,"%[^;];%d;%c\n",escolhas[index].diaSemana,&escolhas[index].numFuncionario,&escolhas[index].tipoPrato);
            index++;
            
        } while (!feof(f_escolhas));
    }

    countEsc = index;
    fclose(f_escolhas);
}

void openEmenta() {
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
        do 
        {
            fscanf(f_ementa, "%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d;%[^;];%d\n", 
            ementa[index].diaSemana, ementa[index].data, ementa[index].pratoPeixe, &ementa[index].caloriasPeixe,
            ementa[index].pratoCarne, &ementa[index].caloriasCarne, ementa[index].pratoDieta, &ementa[index].caloriasDieta,
            ementa[index].pratoVegetariano, &ementa[index].caloriasVegetariano);
            index++;
        } while(!feof(f_ementa));
    }

    countEmenta = index;
    fclose(f_ementa);
}

void ShowRefeicaoPorDia() {
    for (int i = 0; i < countEsc; i++) {
        printf("Funcionário: %d - %s | Prato: %c | Dia: %s\n",
        funcionarios[escolhas[1].numFuncionario - 1].numFuncionario, 
        funcionarios[escolhas[1].numFuncionario - 1].nome, 
        escolhas[i].tipoPrato, 
        escolhas[i].diaSemana);
    }
}

int main() {
    openFuncionarios(); //ERRO NESTA FUNÇ
    openEscolhas();
    openEmenta();
    int opcao;
    
    do {
        Menu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                printf("Você escolheu a Opção 1.\n");
                system("clear");
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
                //free(funcionarios);
                //free(escolhas);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Captura o "Enter" restante no buffer
        }

    } while (opcao != 0);

    return 0;
}