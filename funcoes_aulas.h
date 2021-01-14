#ifndef FUNCOES_AULAS_H_INCLUDED
#define FUNCOES_AULAS_H_INCLUDED

#include "constantes.h"
#include "estruturas.h"

tipoAula lerDadosAula(tipoUC vUC[], char designacaoAula [], int quantUC, int *quantAulas, int *quantAgendadas);
tipoAula *inserirAulas(tipoUC vUC[], tipoAula vAulas[], int quantUC, int *quantAulas, int *quantAgendadas);
int procurarAula(tipoAula vAulas[], int quantAulas, char designacaoAula[]);
tipoAula *alterarAgendada(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int quantAgendadas);
tipoAula *cancelarAgendada(tipoAula vAulas[], int *quantAulas, int *quantAgendadas);
tipoAula *iniciarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int *quantAgendadas, int *quantADecorrer);
tipoAula *acabarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int *quantADecorrer, int *quantRealizadas, int *quantGravadas);
void listarAulas(tipoAula vAulas[], int quantAulas, int quantAgendadas, int quantRealizadas, int quantADecorrer);
void escreverDadosAulas(tipoAula dadosAulas);
void apresentarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas);
tipoAula *lerAulasFichBin(tipoAula vAulas[], int *quantAulas);
void escreverAulasFichBin(tipoAula vAulas[], int quantAulas);

tipoEstudante lerDadosEstudante(tipoAula vAulas[], int quantAulas, int *quantEstudantes);
void inserirEstudante(tipoAula vAulas[], tipoEstudante vEstudantes[], int quantAulas, int *quantEstudantes);
int procurarEstudante(tipoEstudante vEstudantes[], int quantEstudantes, int numEstudante);

#endif // FUNCOES_AULAS_H_INCLUDED
