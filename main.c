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
            printf("| %-8d | %-24s  | %-12d | %-9.2f |\n",
                   funcionarios[i].numFuncionario,
                   funcionarios[i].nome,
                   totalRefeicoes,
                   totalCusto);
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("\nPressione Enter para voltar ao menu...");  
}

struct Refeicao 
{
    char data[11];
    char diaSemana[10];
    char tipoPrato[15];
    int calorias;
 };

 int compararPorDataR(const void *a, const void *b)
{
    struct tm dataA = {0}, dataB = {0};
    struct Refeicao *refA = (struct Refeicao *)a;
    struct Refeicao *refB = (struct Refeicao *)b;

    strptime(refA->data, "%d/%m/%Y", &dataA);
    strptime(refB->data, "%d/%m/%Y", &dataB);

    time_t timeA = mktime(&dataA);
    time_t timeB = mktime(&dataB);

    return (timeA - timeB);
}


void ListarRefeicoes(int numFuncionario)
{
    printf("Refeições do Funcionário nº %d:\n", numFuncionario);
    printf("-------------------------------------------------------------------------\n");
    printf("| Data       | Dia da Semana | Tipo de Prato     | Calorias             |\n");
    printf("-------------------------------------------------------------------------\n");


    struct Refeicao *refeicoes = NULL;
    int refeicoesCount = 0;


    for (int i = 0; i < countEsc; i++) {
        // Verificar se o registro pertence ao funcionário
        if (escolhas[i].numFuncionario == numFuncionario) {
            for (int j = 0; j < countEmenta; j++) {
                if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0) {

                    // Determinar o prato e calorias
                    char *prato;
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

                    // Armazenar as informações da refeição na estrutura dinâmica
                    refeicoes = realloc(refeicoes, (refeicoesCount + 1) * sizeof(struct Refeicao));

                    strftime(refeicoes[refeicoesCount].data, 11, "%d/%m/%Y", &ementa[j].data);
                    strcpy(refeicoes[refeicoesCount].diaSemana, ementa[j].diaSemana);
                    strcpy(refeicoes[refeicoesCount].tipoPrato, prato);
                    refeicoes[refeicoesCount].calorias = calorias;

                    refeicoesCount++;
                }
            }
        }
    }

    // Ordenar as refeições pela data
    if (refeicoesCount > 0) {
        qsort(refeicoes, refeicoesCount, sizeof(struct Refeicao), compararPorDataR);
    }

    // Exibir os resultados
    if (refeicoesCount == 0) {
        printf("Nenhuma refeição encontrada para o funcionário nº %d.\n", numFuncionario);
    } else {
        for (int i = 0; i < refeicoesCount; i++) {
            printf("| %-10s | %-13s | %-17s | %-20d |\n",
                   refeicoes[i].data,
                   refeicoes[i].diaSemana,
                   refeicoes[i].tipoPrato,
                   refeicoes[i].calorias);
        }
    }

    printf("-------------------------------------------------------------------------\n");
    free(refeicoes);

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

//------------------

struct DiaCalorias 
{
    char data[11];          // Armazenar a data completa (DD/MM/AAAA)
    char diaSemana[10];     // Nome do dia da semana
    int totalCalorias;
    int totalRefeicoes;
};

int compararPorDataC(const void *a, const void *b) {
    struct DiaCalorias *diaA = (struct DiaCalorias *)a;
    struct DiaCalorias *diaB = (struct DiaCalorias *)b;

    struct tm dataA = {0};
    struct tm dataB = {0};

    // Converter strings para struct tm
    strptime(diaA->data, "%d/%m/%Y", &dataA);
    strptime(diaB->data, "%d/%m/%Y", &dataB);

    // Comparar as datas
    time_t timeA = mktime(&dataA);
    time_t timeB = mktime(&dataB);

    if (timeA < timeB) return -1;
    if (timeA > timeB) return 1;
    return 0;
}

void CalcularMediaCalorias() {
    char dataInput1[11], dataInput2[11];
    printf("Insira uma 1ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput1);

    if (!strcmp(dataInput1, "0")) {
        return;
    }

    // Substituir delimitadores por "/"
    for (int i = 0; i < strlen(dataInput1); i++) {
        if (dataInput1[i] == '-' || dataInput1[i] == '.') {
            dataInput1[i] = '/';
        }
    }

    struct tm data1 = {0};
    strptime(dataInput1, "%d/%m/%Y", &data1); 

    printf("Insira uma 2ª data no formato DD/MM/AAAA (ou 0 para sair): ");
    scanf("%s", dataInput2);

    if (!strcmp(dataInput2, "0")) {
        return;
    }

    // Substituir delimitadores por "/"
    for (int i = 0; i < strlen(dataInput2); i++) {
        if (dataInput2[i] == '-' || dataInput2[i] == '.') {
            dataInput2[i] = '/';
        }
    }

    struct tm data2 = {0};
    strptime(dataInput2, "%d/%m/%Y", &data2);

    // Ordenar as datas para determinar o início e o fim
    time_t time1 = mktime(&data1);
    time_t time2 = mktime(&data2);

    struct tm dataInicio = time1 < time2 ? data1 : data2;
    struct tm dataFim = time1 < time2 ? data2 : data1;

    // Utilizar uma estrutura dinâmica para armazenar os resultados
    struct DiaCalorias *diasCalorias = NULL;
    int diasCount = 0;

    // Percorrer as escolhas de refeições
    for (int i = 0; i < countEsc; i++) {
        for (int j = 0; j < countEmenta; j++) {
            // Verificar se a escolha corresponde à ementa e está no intervalo de datas
            if (strcmp(escolhas[i].diaSemana, ementa[j].diaSemana) == 0 && 
                difftime(mktime(&ementa[j].data), mktime(&dataInicio)) >= 0 &&
                difftime(mktime(&ementa[j].data), mktime(&dataFim)) <= 0) {
                
                // Verificar se a data já está nos resultados
                int encontrado = -1;
                for (int k = 0; k < diasCount; k++) 
                {
                    char dataStr[11];
                    dataToSring(ementa[j].data, dataStr);
                    if (strcmp(diasCalorias[k].data, dataStr) == 0) { // Comparar pela data completa
                        encontrado = k;
                        break;
                    }
                }

                // Se a data ainda não existe, adicionar à estrutura dinâmica
                if (encontrado == -1) {
                    diasCalorias = realloc(diasCalorias, (diasCount + 1) * sizeof(struct DiaCalorias));
                    strftime(diasCalorias[diasCount].data, 11, "%d/%m/%Y", &ementa[j].data); // Adicionar a data
                    strcpy(diasCalorias[diasCount].diaSemana, ementa[j].diaSemana);
                    diasCalorias[diasCount].totalCalorias = 0;
                    diasCalorias[diasCount].totalRefeicoes = 0;
                    encontrado = diasCount;
                    diasCount++;
                }

                // Incrementar as calorias e refeições para a data encontrada
                switch (escolhas[i].tipoPrato) {
                    case 'C':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasCarne;
                        break;
                    case 'P':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasPeixe;
                        break;
                    case 'D':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasDieta;
                        break;
                    case 'V':
                        diasCalorias[encontrado].totalCalorias += ementa[j].caloriasVegetariano;
                        break;
                }
                diasCalorias[encontrado].totalRefeicoes++;
            }
        }
    }

    // Exibir os resultados após todos os cálculos
    system("clear");

    if (diasCount == 0) {
        printf("Não existem dias com refeições no intervalo especificado.\n");
    } else {
        qsort(diasCalorias, diasCount, sizeof(struct DiaCalorias), compararPorDataC);

        char dI[11], dF[11];
        dataToSring(dataInicio, dI);
        dataToSring(dataFim, dF);

        printf("\nMédias de Calorias Consumidas entre o dia %s e %s\n", dI, dF);
        printf("-----------------------------------------------------------------------\n");
        printf("| Data       | Dia da Semana | Total de Refeições | Média de Calorias |\n");
        printf("-----------------------------------------------------------------------\n");

        for (int i = 0; i < diasCount; i++) {
            printf("| %-10s | %-12s  | %-17d  | %-17.2f |\n", 
                   diasCalorias[i].data,
                   diasCalorias[i].diaSemana, 
                   diasCalorias[i].totalRefeicoes, 
                   (float)diasCalorias[i].totalCalorias / diasCalorias[i].totalRefeicoes);
        }

        printf("-----------------------------------------------------------------------\n");
    }

    free(diasCalorias);
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
                    if (escolhas[j].tipoPrato == 'P') 
                    {
                        printf("| %-18s| %-8d| %-18s| %-8s| %-18s| %-8s| %-23s| %-8s|\n",
                            ementa[i].pratoPeixe, ementa[i].caloriasPeixe, "-", "-", "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'C') 
                    {
                        printf("| %-18s| %-8s| %-18s| %-8d| %-18s| %-8s| %-23s| %-8s|\n",
                            "-", "-", ementa[i].pratoCarne, ementa[i].caloriasCarne, "-", "-", "-", "-");
                    } else if (escolhas[j].tipoPrato == 'D')
                    {
                        printf("| %-18s| %-8s| %-18s| %-8s| %-18s| %-8d| %-23s| %-8s|\n",
                            "-", "-", "-", "-", ementa[i].pratoDieta, ementa[i].caloriasDieta, "-", "-");
                    } else if (escolhas[j].tipoPrato == 'V') 
                    {
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