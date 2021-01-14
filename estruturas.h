#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "constantes.h"

typedef struct
{
    int dia, mes, ano;

} tipoData;

typedef struct
{
    int horas, minutos;

} tipoHora;

typedef struct
{
    char designacaoAula[MAX_STRING];
    int numero, tipoAcesso;

} tipoEstudante;

typedef struct
{
    char designacao[MAX_STRING],nomeDocente[LIM_NOME], opcaoGravacao;
    int tipoAula, estadoAula, codigoUC;
    tipoHora horaInicio, horaFim;
    tipoData dataAula;

} tipoAula;

typedef struct
{
    char designacao[MAX_STRING];
    int codigo, tipoUC, semestre, regime, quantAgendadas, quantADecorrer, quantT, quantAulasT, quantTRealizadas, quantTP, quantAulasTP, quantTPRealizadas, quantPL, quantAulasPL, quantPLRealizadas, duracaoT, duracaoTP, duracaoPL;

} tipoUC;

#endif // ESTRUTURAS_H_INCLUDED
