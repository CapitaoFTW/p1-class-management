#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "menus.h"
#include "funcoes_ucs.h"
#include "funcoes_aulas.h"
#include "funcoes_auxiliares.h"
#include "constantes.h"
#include "estruturas.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    tipoUC dadosUC[MAX_UC];
    tipoAula *dadosAulas=NULL;
    tipoEstudante dadosEstudantes[MAX_ESTUDANTES];
    int opcao, escolha, escolhaMenuUC, escolhaMenuAulas, escolhaMenuEstudantes, escolhaSubMenu, quantUC=0, quantAulas=0, quantAgendadas=0, quantRealizadas=0, quantGravadas=0, quantADecorrer=0, quantEstudantes=0;

    do
    {
        escolha = menuPrincipal(quantUC, quantAgendadas, quantRealizadas, quantGravadas);

        if (escolha == MENU_UCS)
        {
            do
            {
                escolhaMenuUC = menuUCs(quantUC);

                if (escolhaMenuUC == INSERIR)
                {
                    inserirDadosUC(dadosUC, &quantUC);
                }

                if (escolhaMenuUC == ALTERAR)
                {
                    alterarDadosUC(dadosUC, &quantUC);
                }

                if (escolhaMenuUC == LISTAR_UC)
                {
                    listarDadosUC(dadosUC, dadosAulas, quantUC);
                }

                if (escolhaMenuUC == FICHEIROS_UC)
                {
                    do
                    {
                        escolhaSubMenu = subMenuFicheiros();

                        if (escolhaSubMenu == ESCREVER_BIN)
                        {
                            escreverUCFichBin(dadosUC, quantUC);
                        }

                        if (escolhaSubMenu == LER_BIN)
                        {
                            lerUCFichBin(dadosUC, &quantUC);
                        }

                    } while (escolhaSubMenu != 0);
                }

                if (escolhaMenuUC == SAIR_MENU)
                {
                    printf("\n A Sair do Menu das UCs...\n");
                }

            } while (escolhaMenuUC != SAIR_MENU);
        }

        if (escolha == MENU_AULAS)
        {
            do
            {
                escolhaMenuAulas = menuAulas(quantAgendadas, quantRealizadas, quantADecorrer, quantGravadas);

                if (escolhaMenuAulas == INSERIR)
                {
                    dadosAulas = inserirAulas(dadosUC, dadosAulas, quantUC, &quantAulas, &quantAgendadas);
                }

                if (escolhaMenuAulas == ALTERAR)
                {
                    printf("\n Introduza o Que Quer Fazer:\n\n 1 - Alterar Agendamento\n 2 - Cancelar Agendamento\n");
                    opcao = lerInteiro("\n Opção",1,2);

                    if (opcao==1)
                    {
                        dadosAulas = alterarAgendada(dadosUC, dadosAulas, quantUC, quantAulas, quantAgendadas);

                    } else {

                        dadosAulas = cancelarAgendada(dadosAulas, &quantAulas, &quantAgendadas);
                    }
                }

                if (escolhaMenuAulas == INICIAR)
                {
                    dadosAulas = iniciarAula(dadosUC, dadosAulas, quantUC, quantAulas, &quantAgendadas, &quantADecorrer);
                }

                if (escolhaMenuAulas == ACABAR)
                {
                    dadosAulas = acabarAula(dadosUC, dadosAulas, quantUC, quantAulas, &quantADecorrer, &quantRealizadas, &quantGravadas);
                }

                if (escolhaMenuAulas == LISTAR_AULAS)
                {
                    listarAulas(dadosAulas, quantAulas, quantAgendadas, quantRealizadas, quantADecorrer);
                }

                if (escolhaMenuAulas == APRESENTAR)
                {
                    apresentarAula(dadosUC, dadosAulas, quantUC, quantAulas);
                }

                if (escolhaMenuAulas == FICHEIROS_AULAS)
                {
                    do
                    {
                        escolhaSubMenu = subMenuFicheiros();

                        if (escolhaSubMenu == ESCREVER_BIN)
                        {
                            escreverAulasFichBin(dadosAulas, quantAulas);
                        }

                        if (escolhaSubMenu == LER_BIN)
                        {
                            dadosAulas = lerAulasFichBin(dadosAulas, &quantAulas);
                        }

                    } while (escolhaSubMenu != 0);
                }

                if (escolhaMenuAulas == SAIR_MENU)
                {
                    printf("\n A Sair do Menu das Aulas...\n");
                }

            } while (escolhaMenuAulas != SAIR_MENU);
        }

        if (escolha == MENU_ESTUDANTES)
        {
            do
            {
                escolhaMenuEstudantes = menuEstudantes(quantEstudantes);

                if (escolhaMenuEstudantes == INSERIR)
                {
                    inserirEstudante(dadosAulas, dadosEstudantes, quantAulas, &quantEstudantes);
                }

                if (escolhaMenuEstudantes == 2)
                {

                }

                if (escolhaMenuEstudantes == 0)
                {
                    printf("\nA Sair do Menu dos Estudantes...\n");
                }

            } while (escolhaMenuEstudantes != 0);
        }

        if (escolha == MENU_ESTATISTICA)
        {

        }

        if (escolha == MENU_BINARIOS)
        {

        }

        if (escolha == SAIR_MENU)
        {
            printf("\n Saíu do Programa...\n");
        }
    } while (escolha != SAIR_MENU);

    free(dadosAulas);
    dadosAulas=NULL;

    return 0;
}
