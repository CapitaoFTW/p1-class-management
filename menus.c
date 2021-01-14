#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "estruturas.h"
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_ucs.h"
#include "menus.h"

int menuPrincipal(int quantUC, int quantAgendadas, int quantRealizadas, int quantGravadas)
{
    int opcao;

    printf(" _____________________________________________\n|\t\t\t\t\t      |\n|\t\tMenu Principal\t\t      |\n|_____________________________________________|");
    printf("\n\n UCs Inseridas: %d\n", quantUC);

    if (quantUC != 0)
    printf(" Aulas Agendadas: %d\n Aulas Realizadas: %d\n", quantAgendadas, quantRealizadas);

    if(quantRealizadas != 0)
    printf(" Aulas Gravadas: %d\n", quantGravadas);

    printf("\n 1 - Unidades Curriculares\n 2 - Aulas Online\n 3 - Estudantes\n 4 - Dados Estatísticos\n\n 0 - Sair do Programa\n");
    opcao = lerInteiro("\n Opção",0,5);

    return opcao;
}

int menuUCs(int quantUC)
{
    int opcao;

    printf(" _____________________________________________\n|\t\t\t\t\t      |\n|\t     Unidades Curriculares\t      |\n|_____________________________________________|\n\n UCs Inseridas: %d\n", quantUC);
    printf("\n 1 - Inserir Dados\n 2 - Alterar Dados\n 3 - Listar Dados\n 4 - Ficheiros Binários\n\n 0 - Voltar ao Menu Principal\n");
    opcao = lerInteiro("\n Opção",0,4);

    return opcao;
}

int menuAulas(int quantAgendadas, int quantRealizadas, int quantADecorrer, int quantGravadas)
{
    int opcao;

    printf(" _____________________________________________\n|\t\t\t\t\t      |\n|\t\t Aulas Online\t\t      |\n|_____________________________________________|\n");
    printf("\n Aulas Agendadas: %d\n Aulas Realizadas: %d\n Aulas a Decorrer: %d\n", quantAgendadas, quantRealizadas, quantADecorrer);

    if(quantRealizadas != 0)
    {
        printf(" Aulas Gravadas: %d\n", quantGravadas);
    }

    printf("\n 1 - Agendar Aula\n 2 - Alterar Aula Agendada\n 3 - Iniciar Aula\n 4 - Acabar Aula\n 5 - Listar Aulas\n 6 - Apresentar Aula Específica\n 7 - Ficheiros Binários\n\n 0 - Voltar ao Menu Principal\n");
    opcao = lerInteiro("\n Opção",0,7);

    return opcao;
}

int menuEstudantes(int quantEstudantes)
{
    int opcao;

    printf(" _____________________________________________\n|\t\t\t\t\t      |\n|\t\t  Estudantes\t\t      |\n|_____________________________________________|\n");
    printf("\n Estudantes Inseridos: %d\n", quantEstudantes);

    printf("\n 1 - Aceder Estudante a Aula\n 2 - Alterar Dados\n\n 0 - Voltar ao Menu Principal\n");
    opcao = lerInteiro("\n Opção",0,2);

    return opcao;
}

int subMenuFicheiros()
{
    int opcao;

    printf(" _____________________________________________\n|\t\t\t\t\t      |\n|\t      Ficheiros Binários\t      |\n|_____________________________________________|\n");

    printf("\n 1 - Armazenar Dados em Ficheiro Binário\n 2 - Ler Dados de Ficheiro Binário\n\n 0 - Voltar ao Menu Anterior\n");
    opcao = lerInteiro("\n Opção",0,2);

    return opcao;
}
