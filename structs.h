#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um funcionário
typedef struct {
    int numFuncionario;         // Número do funcionário (ex: 0001, 0002, etc.)
    char nome[100];             // Nome completo do funcionário
    int NIF;                    // Número de Identificação Fiscal (NIF)
    int telefone;               // Número de telefone do funcionário
} Funcionarios;

// Estrutura que representa uma ementa
typedef struct {
    char diaSemana[6];          // Dia da semana (ex: 2feira, 3feira, etc.)
    struct tm data;             // Data da ementa (ex: 18.11.2024)
    char pratoPeixe[100];       // Nome do prato de peixe
    int caloriasPeixe;          // Calorias do prato de peixe
    char pratoCarne[100];       // Nome do prato de carne
    int caloriasCarne;          // Calorias do prato de carne
    char pratoDieta[100];       // Nome do prato de dieta
    int caloriasDieta;          // Calorias do prato de dieta
    char pratoVegetariano[100]; // Nome do prato vegetariano
    int caloriasVegetariano;    // Calorias do prato vegetariano
} Ementa;

// Estrutura que representa as escolhas feitas pelos funcionários
typedef struct {
    char diaSemana[6];          // Dia da semana (ex: 2feira, 3feira, etc.)
    int numFuncionario;         // Número do funcionário associado à escolha
    char tipoPrato;             // Tipo de prato escolhido ('C' - Carne, 'P' - Peixe, 'D' - Dieta, 'V' - Vegetariano)
} Escolhas;

// Variáveis globais para armazenar os dados
Ementa ementa[10];              // Lista de ementas (máximo de 10)
Escolhas escolhas[999];         // Lista de escolhas feitas (máximo de 999)
Funcionarios funcionarios[999]; // Lista de funcionários cadastrados (máximo de 999)

// Ponteiros para manipular os arquivos
FILE *f_funcionarios;           // Arquivo de funcionários
FILE *f_ementa;                 // Arquivo de ementas
FILE *f_escolhas;               // Arquivo de escolhas

// Contadores globais
extern int countFunc;           // Contador de funcionários
extern int countEmenta;         // Contador de ementas
extern int countEsc;            // Contador de escolhas

// Estrutura para representar uma refeição específica
struct Refeicao {
    char data[11];              // Data da refeição (DD/MM/AAAA)
    char diaSemana[10];         // Dia da semana
    char tipoPrato[15];         // Tipo de prato (ex: Carne, Peixe, etc.)
    int calorias;               // Quantidade de calorias do prato
};

// Estrutura para calcular médias de calorias por dia
struct DiaCalorias {
    char data[11];              // Data (DD/MM/AAAA)
    char diaSemana[10];         // Dia da semana
    int totalCalorias;          // Total de calorias consumidas no dia
    int totalRefeicoes;         // Total de refeições servidas no dia
};

#endif