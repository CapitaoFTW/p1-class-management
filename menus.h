#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "estruturas.h"
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_ucs.h"

int menuPrincipal(int quantUC, int quantAgendadas, int quantRealizadas, int quantGravadas);
int menuUCs(int quantUC);
int menuAulas(int quantAgendadas, int quantRealizadas, int quantADecorrer, int quantGravadas);
int menuEstudantes(int quantEstudantes);
int subMenuFicheiros();
#endif // MENUS_H_INCLUDED
