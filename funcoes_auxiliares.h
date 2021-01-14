#ifndef FUNCOES_AUXILIARES_H_INCLUDED
#define FUNCOES_AUXILIARES_H_INCLUDED

#include <locale.h>
#include "estruturas.h"
#include "constantes.h"

void lerHora(tipoUC dadosUC[], tipoAula *dadosAula);
tipoData lerData(int semestre);
char lerSimNao(char mensagem[MAX_STRING]);
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void limpaBufferStdin(void);

#endif // FUNCOES_AUXILIARES_H_INCLUDED
