#ifndef STRUCTS_H
#define STRUCTS_H

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

extern int countFunc;
extern int countEmenta;
extern int countEsc;

struct Refeicao 
{
    char data[11];
    char diaSemana[10];
    char tipoPrato[15];
    int calorias;
 };

struct DiaCalorias 
{
    char data[11];          // Armazenar a data completa (DD/MM/AAAA)
    char diaSemana[10];     // Nome do dia da semana
    int totalCalorias;
    int totalRefeicoes;
};

#endif