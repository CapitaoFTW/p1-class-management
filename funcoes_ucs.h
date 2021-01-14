#ifndef FUNCOES_UCS_H_INCLUDED
#define FUNCOES_UCS_H_INCLUDED

#include "constantes.h"
#include "estruturas.h"

tipoUC lerDadosUC();
void inserirDadosUC(tipoUC vUC[MAX_UC], int *quantUC);
int procurarUC(tipoUC vUC[],int quantUC, int codigoUC);
void alterarDadosUC(tipoUC vUC[MAX_UC], int *quantUC);
void listarDadosUC(tipoUC dadosUC[MAX_UC], tipoAula dadosAulas[], int quantUC);
void escreverDadosUC(tipoUC dadosUC, tipoAula dadosAula[]);
void escreverUCFichBin(tipoUC vUC[], int quantUC);
void lerUCFichBin(tipoUC vUC[], int *quantUC);

#endif // FUNCOES_UCS_H_INCLUDED
