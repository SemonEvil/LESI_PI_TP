#ifndef JUNTAR_H
#define JUNTAR_H

#include <time.h> // Para manipulação de datas

// Funções para manipulação de datas
int diaSemanaParaInt(char* dia); // Converte um dia da semana para inteiro
void dataToString(struct tm data, char dataf[]); // Converte uma data para string

// Funções principais do programa
void Menu(); // Exibe o menu principal
void openFuncionarios(); // Carrega dados dos funcionários
void openEscolhas(); // Carrega as escolhas dos utentes
void openEmenta(); // Carrega a ementa

// Operações de listagem
void MostrarRefeicao(); // Mostra informações de uma refeição
void ListarUtentes(); // Lista os utentes
void ListarRefeicoes(int numFuncionario); // Lista refeições de um funcionário

// Funções de comparação
int compararPorDataR(const void *a, const void *b); // Ordena por data decrescente
int compararPorDataC(const void *a, const void *b); // Ordena por data crescente

// Funções para cálculos
void CalcularMediaCalorias(); // Calcula a média de calorias
void TabelaEmenta(int numeroFuncionario); // Gera tabela de ementa por funcionário

#endif