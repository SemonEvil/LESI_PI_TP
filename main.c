#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int numFuncionario;         // número do funcionário (ex: 0001, 0002, etc.)
    char nome[100];             // nome do funcionário
    int NIF;                    // NIF do funcionário
    int telefone;               // número de telefone do funcionário
} Funcionarios;

typedef struct {
    char diaSemana[6];          // dia da semana (2feira, 3feira, etc.)
    struct tm data;             // data (ex: 18.11.2024)
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
    char diaSemana[6];         // dia da semana (2feira, 3feira, etc.)
    int numFuncionario;         // número do funcionário (ex: 0001, 0002, etc.)
    char tipoPrato;             // tipo do prato (C- prato de carne, P - prato peixe, D – dieta, V - vegetariano)
} Escolhas;


// variáveis globais
Ementa ementa[10];
Escolhas escolhas[999];
Funcionarios funcionarios[999];

FILE *f_funcionarios;
FILE *f_ementa;
FILE *f_escolhas;

int countFunc = 0;
int countEmenta = 0;
int countEsc = 0;

int diaSemanaParaInt(char* dia) 
{
    if (strcmp(dia, "2feira") == 0) 
    {
        return 0;  // Segunda-feira
    } 
    else if (strcmp(dia, "3feira") == 0) 
    {
        return 1;  // Terça-feira
    } 
    else if (strcmp(dia, "4feira") == 0) 
    {
        return 2;  // Quarta-feira
    } 
    else if (strcmp(dia, "5feira") == 0) 
    {
        return 3;  // Quinta-feira
    } 
    else if (strcmp(dia, "6feira") == 0) 
    {
        return 4;  // Sexta-feira
    } 
    else 
    {
        return -1; // Caso não encontre o dia
    }
}


void dataToSring(struct tm data, char dataf[])
{
    strftime(dataf, 11, "%d/%m/%Y", &data);
}

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
        char dataStr[11];
        do 
        {
            fscanf(f_ementa, "%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d;%[^;];%d\n", 
            ementa[index].diaSemana, dataStr, ementa[index].pratoPeixe, &ementa[index].caloriasPeixe,
            ementa[index].pratoCarne, &ementa[index].caloriasCarne, ementa[index].pratoDieta, &ementa[index].caloriasDieta,
            ementa[index].pratoVegetariano, &ementa[index].caloriasVegetariano);

            memset(&ementa[index].data, 0, sizeof(struct tm)); // Limpar a estrutura antes de usar
            strptime(dataStr, "%d.%m.%Y", &ementa[index].data);

            index++;
        } while(!feof(f_ementa));   
    }

    countEmenta = index;
    fclose(f_ementa);
}

void MostrarRefeicao() 
{
    int sem;
    char dataInput[11];
    printf("Insira uma data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput);
    
    if (!strcmp(dataInput, "0"))
    {
        return;
    }
    
    // Substituir os delimitadores (caso sejam "-" ou ".") por "/"
    for (int i = 0; i < strlen(dataInput); i++) {
        if (dataInput[i] == '-' || dataInput[i] == '.') {
            dataInput[i] = '/';
        }
    }

    struct tm dataEscolhida = {0};
    strptime(dataInput, "%d/%m/%Y", &dataEscolhida); 

    int found = 0;
    for (int i = 0; i < countEmenta; i++) 
    {
        // Comparando a data fornecida com a data da ementa
        if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0) 
        {
            found = 1;
            system("clear");
            printf("Refeições requeridas para o dia %02d/%02d/%d\n", 
                   ementa[i].data.tm_mday, 
                   ementa[i].data.tm_mon + 1, 
                   ementa[i].data.tm_year + 1900);
            printf("-------------------------------------------------------------------------------------------------------\n");
            printf("| Nº Func. | Nome                     | Dia da semana | Prato                                         |\n");
            printf("-------------------------------------------------------------------------------------------------------\n");

            char prato[999];
            // Exibe as refeições selecionadas para este dia
            for (int j = 0; j < countEsc; j++) 
            {
                // Verifica se a refeição é para o dia selecionado
                if (difftime(mktime(&dataEscolhida), mktime(&ementa[i].data)) == 0 && 
                    strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) 
                {
                    // Atribui o prato de acordo com o tipo
                    switch (escolhas[j].tipoPrato)
                    {
                        case 'P': strcpy(prato, ementa[i].pratoPeixe); break;
                        case 'C': strcpy(prato, ementa[i].pratoCarne); break;
                        case 'D': strcpy(prato, ementa[i].pratoDieta); break;
                        case 'V': strcpy(prato, ementa[i].pratoVegetariano); break;
                        default: strcpy(prato, "Indefinido"); break;
                    }

                    // Exibe os dados do funcionário e o prato escolhido em formato de tabela
                    printf("| %-8d | %-24s | %-13s | %-45s |\n", 
                           funcionarios[escolhas[j].numFuncionario - 1].numFuncionario, 
                           funcionarios[escolhas[j].numFuncionario - 1].nome, escolhas[j].diaSemana, 
                           prato);
                }
            }

            printf("-------------------------------------------------------------------------------------------------------\n");
            break;
        }
    }

    if (!found) 
    {
        printf("Não há ementa registrada para a data %s.\n", dataInput);
    }

    printf("\nPressione Enter para voltar ao menu...");
    getchar();  // Para limpar o buffer do teclado
}

void ListarUtentes()
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
            printf("| %-9d | %-24s  | %-12d | %-9.2f |\n",
                   funcionarios[i].numFuncionario,
                   funcionarios[i].nome,
                   totalRefeicoes,
                   totalCusto);
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("\nPressione Enter para voltar ao menu...");  
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
                    

                    char data[11];
                    dataToSring(ementa[j].data, data);
                    // Exibir informações da refeição
                    printf("| %-10s | %-13s | %-17s | %-20d |\n",
                           data,
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
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

void CalcularMediaCalorias() {

    char dataInput1[11], dataInput2[11];;
    printf("Insira uma 1ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput1);

    if (!strcmp(dataInput1, "0"))
    {
        return;
    }

    // Substituir os delimitadores (caso sejam "-" ou ".") por "/"
    for (int i = 0; i < strlen(dataInput1); i++) {
        if (dataInput1[i] == '-' || dataInput1[i] == '.') {
            dataInput1[i] = '/';
        }
    }

    struct tm data1 = {0};
    strptime(dataInput1, "%d/%m/%Y", &data1); 

    printf("Insira uma 2ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput2);

   if (!strcmp(dataInput2, "0"))
    {
        return;
    }

    // Substituir os delimitadores (caso sejam "-" ou ".") por "/"
    for (int i = 0; i < strlen(dataInput2); i++) {
        if (dataInput2[i] == '-' || dataInput2[i] == '.') {
            dataInput2[i] = '/';
        }
    }

    struct tm data2 = {0};
    strptime(dataInput2, "%d/%m/%Y", &data2);

    time_t time1 = mktime(&data1);
    time_t time2 = mktime(&data2);

    struct tm dataInicio = {0};  
    struct tm dataFim = {0};
    
    // Comparação
    if (time1 > time2) 
    {
        memcpy(&dataFim, &data1, sizeof(struct tm));  // Copia data1 para dataFim
        memcpy(&dataInicio, &data2, sizeof(struct tm)); // Copia data2 para dataInicio
    } 
    else
    {
        memcpy(&dataFim, &data2, sizeof(struct tm));  // Copia data2 para dataFim
        memcpy(&dataInicio, &data1, sizeof(struct tm)); // Copia data1 para dataInicio
    }

    char dI[11], dF[11];
    dataToSring(dataInicio, dI);
    dataToSring(dataFim, dF);

    system("clear");
    printf("\nMédias de Calorias Consumidas entre o dia %s e %s\n", dI, dF);
    printf("----------------------------------------------------------\n");
    printf("| Dia da Semana | Total de Refeições | Média de Calorias |\n");
    printf("----------------------------------------------------------\n");

    int index = 0;
    int totalCalorias[5] = {0}; // Total de calorias para cada dia da semana (segunda a sexta)
    int totalRefeicoes[5] = {0}; // Total de refeições para cada dia da semana
    int diasPresentes[5] = {0};  // Marcar quais dias da semana estão presentes no intervalo (0 a 4)

    for (int i = 0; i < countEsc; i++) {
        for (int j = 0; j < countEmenta; j++) 
        {
            time_t timeEmenta = mktime(&ementa[j].data);
            time_t timeInicio = mktime(&dataInicio);
            time_t timeFim = mktime(&dataFim);
            
            // Verificar se a data da ementa está dentro do intervalo de datas
            if (timeEmenta >= timeInicio && timeEmenta <= timeFim) 
            {
                // Determinar o índice do dia da semana
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

                // Se o dia da semana for válido, calcular as calorias
                if (diaSemanaIndex >= 0) 
                {
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
                    printf("\n%d\n", totalRefeicoes[diaSemanaIndex]);
                    diasPresentes[diaSemanaIndex] = 1;  // Marca que este dia apareceu no intervalo
                }
            }
        }
    }

    // Exibir os resultados apenas para os dias presentes no intervalo
    const char* diasSemana[] = {"2feira", "3feira", "4feira", "5feira", "6feira"};

    for (int i = 0; i < 5; i++) 
    {
        if (diasPresentes[i]) 
        {   // Verificar se o dia foi presente no intervalo
            if (totalRefeicoes[i] > 0) 
            {
                printf("| %-12s  | %-17d  | %-17.2f |\n", 
                    diasSemana[i], 
                    totalRefeicoes[i], 
                    (float)totalCalorias[i] / totalRefeicoes[i]);
            } else \
            {
                printf("| %-12s  | %-17d  | %-17s |\n", diasSemana[i], 0, "N/A");
            }
        }
    }
    printf("----------------------------------------------------------\n");
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

void TabelaEmenta(int numeroFuncionario) 
{
    printf("Ementa Semanal para o Utente #%d\n", numeroFuncionario);
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
    printf("| Dia       | Prato Peixe       | Calorias | Prato Carne       | Calorias | Prato Dieta       | Calorias | Prato Vegetariano       | Calorias |\n");
    printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");

    for (int j = 0; j < countEsc; j++) {
        if (escolhas[j].numFuncionario == numeroFuncionario) {
            // Encontrar a ementa correspondente ao dia da escolha
            for (int i = 0; i < countEmenta; i++) {
                if (strcmp(escolhas[j].diaSemana, ementa[i].diaSemana) == 0) {
                    // Imprimir os dados do dia com base na escolha
                    printf("| %-10s", ementa[i].diaSemana);

                    // Preencher as colunas com base na escolha
                    if (escolhas[j].tipoPrato == 'P') {
                        printf("| %-18s| %-8d| %-18s| %-8s| %-18s| %-8s| %-23s| %-8s|\n",
                            ementa[i].pratoPeixe, ementa[i].caloriasPeixe, "-", "-", "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'C') {
                        printf("| %-18s| %-8s| %-18s| %-8d| %-18s| %-8s| %-23s| %-8s|\n",
                            "-", "-", ementa[i].pratoCarne, ementa[i].caloriasCarne, "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'D') {
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8d| %-23s| %-8s|\n",
                            "-", "-", "-", "-", ementa[i].pratoDieta, ementa[i].caloriasDieta, "-", "-");
                    } else if (escolhas[j].tipoPrato == 'V') {
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8s| %-23s| %-8d|\n",
                            "-", "-", "-", "-", "-", "-", ementa[i].pratoVegetariano, ementa[i].caloriasVegetariano);
                    }

                    break; // Encontrou o dia correspondente, pode sair do loop da ementa
                }
            }
            printf("+-----------+-------------------+----------+-------------------+----------+-------------------+----------+-------------------------+----------+\n");
        }
    }

    printf("\nPressione Enter para voltar ao menu...");
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