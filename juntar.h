#ifndef JUNTAR_H
#define JUNTAR_H

#include <time.h> // Para a struct tm utilizada em dataToString

// Conversão e manipulação de datas
int diaSemanaParaInt(char* dia);
void dataToString(struct tm data, char dataf[]);

// Funções principais
void Menu();
void openFuncionarios();
void openEscolhas();
void openEmenta();

// Operações de listagem
void MostrarRefeicao();
void ListarUtentes();
void ListarRefeicoes(int numFuncionario);

// Comparações para ordenação
int compararPorDataR(const void *a, const void *b);
int compararPorDataC(const void *a, const void *b);

// Cálculos
void CalcularMediaCalorias();
void TabelaEmenta(int numeroFuncionario);

#endif
