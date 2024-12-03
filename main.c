#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Função de limpeza apenas para caracteres de controle
void limparCaracteresDeControle(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        // Mantém apenas caracteres visíveis e espaços
        if ((*src >= 32 && *src <= 126) || *src == '\t') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void openFuncionarios() {
    FILE *f_funcionarios = fopen("funcionarios.txt", "r");
    if (!f_funcionarios) {
        perror("Não existem informações sobre as escolhas!\n");
    }

    int index = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), f_funcionarios)) {
        if (sscanf(linha, "%d;%[^;];%d;%d", &funcionarios[index].numFuncionario, funcionarios[index].nome, &funcionarios[index].NIF, &funcionarios[index].telefone) == 4)
        {
            index++;
        }
    }

    countFunc = index;
    fclose(f_funcionarios);
}

void openEscolhas() {
    // abrir o ficheiro
    char *escolhas_path = "escolhas.txt";
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
    char *ementa_path = "ementa.txt";
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

int diaSemanaParaInt(char* dia) {
    if (strcmp(dia, "2feira") == 0) {
        return 0;  // Segunda-feira
    } else if (strcmp(dia, "3feira") == 0) {
        return 1;  // Terça-feira
    } else if (strcmp(dia, "4feira") == 0) {
        return 2;  // Quarta-feira
    } else if (strcmp(dia, "5feira") == 0) {
        return 3;  // Quinta-feira
    } else if (strcmp(dia, "6feira") == 0) {
        return 4;  // Sexta-feira
    } else {
        return -1; // Caso não encontre o dia
    }
}

void ShowRefeicaoPorDia() 
{
    int dia, sem;

    printf("\n===== Escolha o Dia da Semana =====\n");
    printf("2 - Segunda-feira\n");
    printf("3 - Terça-feira\n");
    printf("4 - Quarta-feira\n");
    printf("5 - Quinta-feira\n");
    printf("6 - Sexta-feira\n");
    printf("0 - Voltar ao menu principal\n");
    printf("===================================\n");
    printf("Escolha um dia: ");
    scanf("%d", &dia);

    switch (dia) 
    {
        case 2: //Segunda
            sem = 0; 
            break;

        case 3: //Terça
            sem = 1; 
            break;

        case 4: //Quarta
            sem = 2; 
            break;

        case 5: //Quinta
            sem = 3; 
            break;

        case 6: //Sexta
            sem = 4; 
            break;

        case 0:
            printf("\nVoltando ao menu principal...\n");
            system("clear");
            return;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            system("clear");
            return;
    }
    // Títulos de refeição
    system("clear");
    printf("\n==== Refeições para o dia: %s ====\n", ementa[sem].diaSemana);
    printf("====================================\n");

    char prato[999];

    for (int i = 0; i < countEsc; i++) 
    {       
        int escolhaDiaInt = diaSemanaParaInt(escolhas[i].diaSemana);
           
        if (escolhaDiaInt == sem || escolhas[i].diaSemana == ementa[sem].diaSemana)
        {
            switch (escolhas[i].tipoPrato)
            {
                case 'P':
                    strcpy(prato, ementa[sem].pratoPeixe); 
                    break;
                case 'C': 
                    strcpy(prato, ementa[sem].pratoCarne); 
                    break;
                case 'D': 
                    strcpy(prato, ementa[sem].pratoDieta); 
                    break;
                case 'V': 
                    strcpy(prato, ementa[sem].pratoVegetariano); 
                    break;
            }
            // Exibe a refeição de um funcionário de forma mais bonita
            printf("\n---------------------------------------------------\n");
            printf("| Funcionario: %-4d | %-25s | Prato: %s |\n", 
                    funcionarios[escolhas[i].numFuncionario - 1].numFuncionario, 
                    funcionarios[escolhas[i].numFuncionario - 1].nome, 
                    prato);
            printf("---------------------------------------------------\n");
        }
    }
    getchar();
}

void ShowUtentes()
{
    // Ordenar funcionários por número (decrescente)
    for (int i = 0; i < countFunc - 1; i++) {
        for (int j = i + 1; j < countFunc; j++) {
            if (funcionarios[i].numFuncionario < funcionarios[j].numFuncionario) {
                Funcionarios temp = funcionarios[i];

                funcionarios[i] = funcionarios[j];
                funcionarios[j] = temp;
            }
        }
    }

    // Cabeçalho
    printf("Lista de Utentes:\n");
    printf("-------------------------------------------------------------------\n");
    printf("| Nº Func. | Nome                      | Nº Refeições | Custo (€) |\n");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < countFunc; i++) {
        int totalRefeicoes = 0;
        float totalCusto = 0.0;

        // Processar as escolhas do funcionário
        for (int j = 0; j < countEsc; j++) {
            if (escolhas[j].numFuncionario == funcionarios[i].numFuncionario) {
                totalRefeicoes++;

                // Determinar custo com base no tipo de prato
                float precoPrato = 6.0;

                totalCusto += precoPrato;
            }
        }

        // Exibir dados do funcionário
        if (totalRefeicoes > 0) {
            printf("| %-9d | %-24s | %-12d | %-9.2f |\n",
                   funcionarios[i].numFuncionario,
                   funcionarios[i].nome,
                   totalRefeicoes,
                   totalCusto);
        }
    }

    printf("-------------------------------------------------------------------\n");
}

void ListarRefeicoes(int numFuncionario)
{
    printf("Refeições do Funcionário nº %d:\n", numFuncionario);
    printf("-------------------------------------------------------------------------\n");
    printf("| Data       | Dia da Semana | Tipo de Prato     | Calorias             |\n");
    printf("-------------------------------------------------------------------------\n");

    int encontrou = 0;

    for (int i = 0; i < countEsc; i++) {
        // Verificar se o registro pertence ao funcionário
        if (escolhas[i].numFuncionario == numFuncionario) {
            for (int j = 0; j < countEmenta; j++) {
                if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0) {
                    // FUTURO: Verificar se a data está dentro do intervalo fornecido
                    /*
                    if (strcmp(ementa[j].data, dataInicio) >= 0 && strcmp(ementa[j].data, dataFim) <= 0) {
                    */

                    encontrou = 1;

                    // Determinar o prato e calorias
                    char* prato;
                    int calorias = 0;

                    if (escolhas[i].tipoPrato == 'C') {
                        prato = "Carne";
                        calorias = ementa[j].caloriasCarne;
                    } else if (escolhas[i].tipoPrato == 'P') {
                        prato = "Peixe";
                        calorias = ementa[j].caloriasPeixe;
                    } else if (escolhas[i].tipoPrato == 'D') {
                        prato = "Dieta";
                        calorias = ementa[j].caloriasDieta;
                    } else if (escolhas[i].tipoPrato == 'V') {
                        prato = "Vegetariano";
                        calorias = ementa[j].caloriasVegetariano;
                    }

                    // Exibir informações da refeição
                    printf("| %-10s | %-13s | %-17s | %-20d |\n",
                           ementa[j].data,
                           ementa[j].diaSemana,
                           prato,
                           calorias);

                    // FUTURO: Fechar a lógica do intervalo de datas
                    /*
                    }
                    */
                }
            }
        }
    }

    if (!encontrou) {
        printf("Nenhuma refeição encontrada para o funcionário nº %d.\n", numFuncionario);
    }

    printf("-------------------------------------------------------------------------\n");

    getchar();
}

void CalcularMediaCalorias() {
    printf("\nMédias de Calorias Consumidas por Dia da Semana (Segunda a Sexta):\n");
    printf("----------------------------------------------------------\n");
    printf("| Dia da Semana | Total de Refeições | Média de Calorias |\n");
    printf("----------------------------------------------------------\n");

    int totalCalorias[5] = {0}; // Total de calorias para cada dia da semana (segunda a sexta)
    int totalRefeicoes[5] = {0}; // Total de refeições para cada dia da semana

    for (int i = 0; i < countEsc; i++) {
        for (int j = 0; j < countEmenta; j++) {
            //printf("Comparando: %s com %s\n", escolhas[i].diaSemana, ementa[j].diaSemana); // Depuração
            if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0) {
                // FUTURO: Verificar se a data está dentro do intervalo fornecido
                /*
                if (strcmp(ementa[j].data, dataInicio) >= 0 && strcmp(ementa[j].data, dataFim) <= 0) {
                */

                // Determinar o índice do dia da semana (segunda a sexta: 0 a 4)
                int diaSemanaIndex = -1;

                if (strcmp(ementa[j].diaSemana, "2feira") == 0) 
                    diaSemanaIndex = 0;
                else if (strcmp(ementa[j].diaSemana, "3feira") == 0) 
                    diaSemanaIndex = 1;
                else if (strcmp(ementa[j].diaSemana, "4feira") == 0) 
                    diaSemanaIndex = 2;
                else if (strcmp(ementa[j].diaSemana, "5feira") == 0) 
                    diaSemanaIndex = 3;
                else if (strcmp(ementa[j].diaSemana, "6feira") == 0) 
                    diaSemanaIndex = 4;

                if (diaSemanaIndex >= 0) {
                    // Somar calorias com base no tipo de prato escolhido
                    if (escolhas[i].tipoPrato == 'C') {
                        totalCalorias[diaSemanaIndex] += ementa[j].caloriasCarne;
                    } else if (escolhas[i].tipoPrato == 'P') {
                        totalCalorias[diaSemanaIndex] += ementa[j].caloriasPeixe;
                    } else if (escolhas[i].tipoPrato == 'D') {
                        totalCalorias[diaSemanaIndex] += ementa[j].caloriasDieta;
                    } else if (escolhas[i].tipoPrato == 'V') {
                        totalCalorias[diaSemanaIndex] += ementa[j].caloriasVegetariano;
                    }

                    totalRefeicoes[diaSemanaIndex]++;
                }

                // FUTURO: Fechar a lógica do intervalo de datas
                /*
                }
                */
            }
        }
    }

    // Exibir os resultados
    const char* diasSemana[] = {"2feira", "3feira", "4feira", "5feira", "6feira"};

    for (int i = 0; i < 5; i++) {
        if (totalRefeicoes[i] > 0) {
            printf("| %-12s  | %-17d  | %-17.2f |\n", 
                   diasSemana[i], 
                   totalRefeicoes[i], 
                   (float)totalCalorias[i] / totalRefeicoes[i]);
        } else {
            printf("| %-12s  | %-17d  | %-17s |\n", diasSemana[i], 0, "N/A");
        }
    }

    printf("----------------------------------------------------------\n");
}

void TabelaEmenta(int numeroFuncionario) 
{
    printf("Ementa Semanal para o Utente #%d\n", numeroFuncionario);
    printf("+-----------+---------------------------------------------------------------------------------------------------------+\n");
    printf("| Dia       | Prato Peixe | Calorias | Prato Carne | Calorias | Prato Dieta | Calorias | Prato Vegetariano | Calorias |\n");
    printf("+-----------+---------------------------------------------------------------------------------------------------------+\n");

    // Percorrer os dias da semana e gerar a tabela
    for (int i = 0; i < countEmenta; i++) {
        // Para cada escolha do utente, verificamos se ele escolheu um prato nesse dia
        for (int j = 0; j < countEsc; j++) {
            if (escolhas[j].numFuncionario == numeroFuncionario && strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) {
                printf("| %-10s| ", ementa[i].diaSemana);

                // Finaliza a linha
                printf("\n");
            }
        }
    }
    getchar();
}

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
                ShowRefeicaoPorDia();
                break;
            case 2: //Listagem dos utentes, ordenada por ordem decrescente do número de funcionário, com o número de refeições servidas 
                    //na semana e o total da despesa, para ser entregue no serviço de Recursos Humanos, para efeitos de desconto no salário.
                system("clear");
                ShowUtentes();
                break;
            case 3: //Listar as refeições e a quantidade de calorias de um utente ao longo de um determinado período.
                system("clear");
                printf("Digite o número do utente para exibir a ementa: ");
                int n1;
                scanf("%d", &n1);
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
        }

        if (opcao != 0) {
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Captura o "Enter" restante no buffer
        }

    } while (opcao != 0);

    return 0;
}