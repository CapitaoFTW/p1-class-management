#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_aulas.h"
#include "funcoes_ucs.h"
#include "estruturas.h"

tipoAula lerDadosAula(tipoUC vUC[], char designacaoAula [], int quantUC, int *quantAulas, int *quantAgendadas)
{
    tipoAula dadosAula;
    int codigoUC, pos;

        codigoUC=lerInteiro("\n Introduza o Código da UC",1,10000);

        pos=procurarUC(vUC,quantUC,codigoUC);

        if (pos == -1)
        {
            printf("\n O Código que Inseriu não Pertence a Qualquer UC\n\n A Voltar Para o Menu das Aulas...\n");
            (*quantAgendadas)--;
            (*quantAulas)--;

        } else {

            dadosAula.codigoUC=vUC[pos].codigo;
            strcpy(dadosAula.designacao,designacaoAula);
            lerString("\n Introduza o Nome do Docente: ",dadosAula.nomeDocente,MAX_STRING);

            do
            {
                printf("\n Qual o Tipo de Aula?\n\n 1 - Téorica\n 2 - Teórico-Prática\n 3 - Prática Laboratorial\n");
                dadosAula.tipoAula=lerInteiro("\n Opção",T,PL);

                if (dadosAula.tipoAula==T)
                {
                    if (vUC[pos].quantT==0)
                    {
                        printf("\n Não Existem Aulas T na UC!");
                        printf("\n Tente Novamente!\n");

                    } else {

                        vUC[pos].quantAulasT++;
                    }
                }

                if (dadosAula.tipoAula==TP)
                {
                    if (vUC[pos].quantTP==0)
                    {
                        printf("\n Não Existem Aulas TP na UC!");
                        printf("\n Tente Novamente!\n");

                    } else {

                        vUC[pos].quantAulasTP++;
                    }
                }

                if (dadosAula.tipoAula==PL)
                {
                    if (vUC[pos].quantPL==0)
                    {
                        printf("\n Não Existem Aulas PL na UC!");
                        printf("\n Tente Novamente!\n");

                    } else {

                        vUC[pos].quantAulasPL++;
                    }
                }

            } while ((vUC[pos].quantT == 0 && dadosAula.tipoAula==T) || (vUC[pos].quantTP == 0 && dadosAula.tipoAula==TP) || (vUC[pos].quantPL == 0 && dadosAula.tipoAula==PL));

            printf("\n Introduza a Data da Aula:\n");
            dadosAula.dataAula=lerData(vUC[pos].semestre);

            printf("\n Introduza a Hora de Início:\n\n");
            lerHora(vUC,&dadosAula);

            dadosAula.estadoAula=AGENDADA;

            vUC[pos].quantAgendadas++;
    }

    return dadosAula;
}

tipoAula *inserirAulas(tipoUC vUC[], tipoAula vAulas[], int quantUC, int *quantAulas, int *quantAgendadas)
{
    tipoAula *pAulas, dadosAula;

    int pos;
    char designacaoAula[MAX_STRING];

    if (quantUC != 0)
    {
        lerString("\n Qual é a Designação da Aula? ",designacaoAula,MAX_STRING);
        pAulas = vAulas;
        pos=procurarAula(vAulas,*quantAulas,designacaoAula);
        dadosAula = lerDadosAula(vUC, designacaoAula, quantUC, &(*quantAgendadas), &(*quantAulas));

        if (pos != -1)
        {
            printf("\n A Aula com Designação Dada já Existe!\n\n A Voltar Para o Menu das Aulas...\n");

        } else {

            vAulas = realloc(vAulas,(*quantAgendadas+1)*sizeof(tipoAula));

            if (vAulas == NULL)
            {
                printf(" Erro - Impossível Agendar a Aula!");
                vAulas = pAulas;

            } else {

                vAulas[*quantAgendadas] = dadosAula;
                (*quantAgendadas)++;
                (*quantAulas)++;
            }
        }

    } else {

        printf("\n Insira Primeiro Pelo Menos uma UC!\n\n A Voltar ao Menu das Aulas...\n");
    }

    return vAulas;
}

int procurarAula(tipoAula vAulas[], int quantAulas, char designacaoAula[])
{
    int i, pos=-1;

    for (i=0; i<quantAulas; i++)
    {
        if (strcmp(vAulas[i].designacao, designacaoAula)==0)
        {
            pos = i;
            i = quantAulas;
        }
    }

    return pos;
}

tipoAula *alterarAgendada(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int quantAgendadas)
{
    int i, posAula, posUC, opcao;
    char designacaoAula[MAX_STRING];

    if (quantAgendadas == 0)
    {
        printf("\n Não Existem Aulas Agendadas!\n");

    } else {

            lerString("\n Escreva a Designação da Aula a Alterar o Agendamento: ",designacaoAula,MAX_STRING);
            posAula = procurarAula(vAulas, quantAulas, designacaoAula);

            if (posAula == -1)
            {
                printf("\n A Aula com a Designação Dada não Existe!\n\n A Voltar Para o Menu das Aulas...\n");

            } else {

                posUC = procurarUC(vUC,quantUC,vAulas->codigoUC);

                for (i=posAula;i<=posAula;i++)
                {
                    printf("\n Insira a Nova Data:\n");
                    vAulas[i].dataAula=lerData(vUC[posUC].semestre);

                    printf("\n Quer Alterar Também a Hora?\n S - Sim\n N - Nao\n");
                    opcao=lerSimNao("\n Opção -> ");

                    if (opcao == 'S')
                    {
                        do
                        {
                            printf("\n Introduza a Nova Hora de Início:\n\n ");
                            lerHora(&vUC[posUC],&vAulas[i]);

                        } while (vAulas[i].horaFim.horas > MAX_DIURNO || vAulas[i].horaFim.horas > MAX_POSLABORAL);
                    }

                    printf("\n Agendamento Alterado Com Sucesso!\n");
                }
            }
        }

    return vAulas;
}

tipoAula *cancelarAgendada(tipoAula vAulas[], int *quantAulas, int *quantAgendadas)
{
    tipoAula *pAulas;
    int i, pos;
    char designacaoAula[MAX_STRING];

    pAulas = vAulas;

    if (*quantAgendadas == 0)
    {
        printf("\n Não Existem Aulas Agendadas!\n");

    } else {

        lerString("\n Escreva a Designação da Aula a Cancelar: ",designacaoAula,MAX_STRING);
        pos = procurarAula(vAulas, *quantAulas, designacaoAula);

        if (pos == -1)
        {
            printf ("\n A Aula com a Designação Dada não Existe!\n\n A Voltar Para o Menu das Aulas...\n");

        } else {

            for (i=pos;i<*quantAgendadas-1;i++)
            {
                vAulas[i] = vAulas[i+1];
            }

            vAulas = realloc(vAulas,(*quantAgendadas-1)*sizeof(tipoAula));

            if (vAulas == NULL && (*quantAgendadas-1) != 0)
            {
                printf (" Erro na Alocação de Memória ");

                vAulas = pAulas;
            }

            (*quantAgendadas)--;
            (*quantAulas)--;
            printf("\n Agendamento Cancelado Com Sucesso!\n\n A Voltar Para o Menu das Aulas...\n");
        }
    }

    return vAulas;
}

tipoAula *iniciarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int *quantAgendadas, int *quantADecorrer)
{
    int posAula, posUC;
    char designacaoAula[MAX_STRING];

        if (*quantAgendadas == 0)
        {
            printf("\n Não Existem Aulas Agendadas!\n");

        } else {

            lerString("\n Escreva a Designação da Aula a Iniciar: ",designacaoAula,MAX_STRING);
            posAula = procurarAula(vAulas, quantAulas, designacaoAula);

            if (posAula == -1)
            {
                printf("\n A Aula com a Designação Dada não Existe!\n\n A Voltar Para o Menu das Aulas...\n");

            } else {

                posUC = procurarUC(vUC, quantUC, vAulas[posAula].codigoUC);

                if (vUC[posUC].quantADecorrer<1)
                {
                    if (vAulas[posAula].estadoAula==AGENDADA)
                    {
                        vAulas[posAula].estadoAula=A_DECORRER;

                        printf(" Deseja Começar a Gravar a Aula?\n\n S - Sim\n N - Não\n");
                        vAulas[posAula].opcaoGravacao=lerSimNao("\n Opção -> ");

                        vUC[posUC].quantADecorrer++;
                        (*quantADecorrer)++;
                        (*quantAgendadas)--;

                        printf("\n A Aula Iniciou com Sucesso!\n");

                        if (vAulas[posAula].opcaoGravacao == 'S')
                        {
                            printf(" Gravação Iniciada!\n");
                        }

                    } else {

                        printf("\n Só pode Iniciar uma Aula que Esteja Agendada!\n");
                    }

                } else {

                    printf("\n Já Tem uma Aula da Mesma UC a Decorrer, Tente de Novo Mais Tarde!\n");
                }
            }
        }

    return vAulas;
}

tipoAula *acabarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas, int *quantADecorrer, int *quantRealizadas, int *quantGravadas)
{
    int posAula, posUC;
    char designacaoAula[MAX_STRING];

        if (*quantADecorrer == 0)
        {
            printf("\n Não Existem Aulas A Decorrer!\n");

        } else {

            lerString("\n Escreva a Designação da Aula a Acabar: ",designacaoAula,MAX_STRING);
            posAula = procurarAula(vAulas, quantAulas, designacaoAula);

            if (posAula == -1)
            {
                printf("\n A Aula com a Designação Dada não Existe ou não está a Decorrer!\n\n A Voltar Para o Menu das Aulas...\n");

            } else {

                posUC = procurarUC(vUC, quantUC, vAulas[posAula].codigoUC);

                vAulas[posAula].estadoAula=REALIZADA;
                (*quantRealizadas)++;
                (*quantADecorrer)--;
                vUC[posUC].quantADecorrer--;

                printf("\n A Aula Acabou com Sucesso!\n");

                if (vAulas[posAula].opcaoGravacao == 'S' || vAulas[posAula].opcaoGravacao == 's')
                {
                    printf(" Gravação Finalizada!\n");
                    (*quantGravadas)++;
                }

                if (vAulas[posAula].tipoAula==T)
                vUC[posUC].quantTRealizadas++;

                if (vAulas[posAula].tipoAula==TP)
                vUC[posUC].quantTPRealizadas++;

                if (vAulas[posAula].tipoAula==PL)
                vUC[posUC].quantPLRealizadas++;
            }
        }

    return vAulas;
}

void listarAulas(tipoAula vAulas[], int quantAulas, int quantAgendadas, int quantRealizadas, int quantADecorrer)
{
    int i;

    if (quantAulas == 0)
    {
        printf("\n Ainda Não Existe Qualquer Registo de Aulas!\n");

    } else {

        if (quantAgendadas != 0)
        printf("\n ********** Listagem das Aulas Agendadas **********\n");

        for (i=0;i<quantAulas;i++)
        {
            if(vAulas[i].estadoAula==AGENDADA)
            {
                escreverDadosAulas(vAulas[i]);
            }
        }

        if (quantRealizadas != 0)
        printf("\n ********** Listagem das Aulas Realizadas **********\n");

        for (i=0;i<quantAulas;i++)
        {
            if(vAulas[i].estadoAula==REALIZADA)
            {
                escreverDadosAulas(vAulas[i]);
            }
        }

        if (quantADecorrer != 0)
        printf("\n ********** Listagem das Aulas a Decorrer **********\n");

        for (i=0;i<quantAulas;i++)
        {
            if(vAulas[i].estadoAula==A_DECORRER)
            {
                escreverDadosAulas(vAulas[i]);
            }
        }
    }
}

void escreverDadosAulas(tipoAula dadosAulas)
{
    printf("\n ----- Dados de %s [Código da UC: %d]-----\n", dadosAulas.designacao,dadosAulas.codigoUC);

    printf("\n Docente: %s\n", dadosAulas.nomeDocente);

    if (dadosAulas.tipoAula==T)
    {
        printf(" Aula T");

    } else {

        if (dadosAulas.tipoAula==TP)
        {
            printf(" Aula TP");

        } else {

            printf(" Aula PL");
        }
    }

    if (dadosAulas.opcaoGravacao == 'S' || dadosAulas.opcaoGravacao == 's')
    {
        if (dadosAulas.estadoAula==A_DECORRER)
        printf(" a Ser Gravada");

        else
        printf(" Gravada");

        printf("\n");

    } else {

        if (dadosAulas.estadoAula==A_DECORRER)
        printf(" que não está a Ser Gravada");

        if (dadosAulas.estadoAula==REALIZADA)
        printf(" que não Foi Gravada");

        printf("\n");
    }

    if (dadosAulas.estadoAula==AGENDADA)
    {
        printf(" Agendada para o Dia %02d/%02d/%02d das %02dh%02d às %02dh%02d", dadosAulas.dataAula.dia, dadosAulas.dataAula.mes, dadosAulas.dataAula.ano, dadosAulas.horaInicio.horas, dadosAulas.horaInicio.minutos, dadosAulas.horaFim.horas, dadosAulas.horaFim.minutos);

    } else {

        if (dadosAulas.estadoAula==REALIZADA)
        {
            printf(" Realizada no Dia %02d/%02d/%02d às %02dh%02d até às %02dh%02d", dadosAulas.dataAula.dia, dadosAulas.dataAula.mes, dadosAulas.dataAula.ano, dadosAulas.horaInicio.horas, dadosAulas.horaInicio.minutos, dadosAulas.horaFim.horas, dadosAulas.horaFim.minutos);

        } else {

            printf(" Está a Decorrer Hoje, Dia %02d/%02d/%02d, Começou às %02dh%02d e Acaba às %02dh%02d", dadosAulas.dataAula.dia, dadosAulas.dataAula.mes, dadosAulas.dataAula.ano, dadosAulas.horaInicio.horas, dadosAulas.horaInicio.minutos, dadosAulas.horaFim.horas, dadosAulas.horaFim.minutos);
        }
    }

    printf("\n");
}

void apresentarAula(tipoUC vUC[], tipoAula vAulas[], int quantUC, int quantAulas)
{
    int posAula, posUC, quantPorAgendar;
    char designacaoAula[MAX_STRING];

    if (quantAulas == 0)
    {
        printf("\n Ainda Não Existe Qualquer Registo de Aulas!\n");

    } else {

        lerString("\n Qual é a Designação da Aula? ",designacaoAula,MAX_STRING);
        posAula = procurarAula(vAulas, quantAulas, designacaoAula);

        if (posAula == -1)
        {
            printf("\n A Aula com Designação Dada não Existe!\n\n A Voltar Para o Menu das Aulas...\n");

        } else {

            posUC = procurarUC(vUC, quantUC, vAulas[posAula].codigoUC);
            escreverDadosAulas(vAulas[posAula]);

            printf("\n Designação da UC: %s\n", vUC[posUC].designacao);

            if(vAulas[posAula].tipoAula==T)
            quantPorAgendar = vUC[posUC].quantT - vUC[posUC].quantAulasT;

            if(vAulas[posAula].tipoAula==TP)
            quantPorAgendar = vUC[posUC].quantTP - vUC[posUC].quantAulasTP;

            if(vAulas[posAula].tipoAula==PL)
            quantPorAgendar = vUC[posUC].quantPL - (vUC[posUC].quantAulasPL);

            printf(" Quantidade de Aulas por Agendar: %d\n", quantPorAgendar);
        }
    }
}

tipoAula *lerAulasFichBin(tipoAula vAulas[], int *quantAulas)
{
    FILE *ficheiroAulas;

    tipoAula *pAulas;

    ficheiroAulas = fopen("Aulas.dat", "rb");

    if (ficheiroAulas == NULL)
    {
        printf("\nImpossivel Abrir Ficheiro!\n");

    } else {

        fread(&(*quantAulas), sizeof(int), 1, ficheiroAulas);

        pAulas = vAulas;

        vAulas = realloc(vAulas, (*quantAulas) * sizeof(tipoAula));

        if (vAulas == NULL && *quantAulas != 0)
        {
            printf("\nErro ao Reservar Memória!\n");
            vAulas = pAulas;

        } else {

            fread (vAulas, sizeof(tipoAula), *quantAulas, ficheiroAulas);
        }

        printf("\n Dados Lidos com Sucesso!\n\n A Voltar ao Menu dos Ficheiros Binários...\n");

        fclose (ficheiroAulas);
    }

    return vAulas;
}

void escreverAulasFichBin(tipoAula vAulas[], int quantAulas)
{
    FILE *ficheiroAulas;

    ficheiroAulas = fopen("Aulas.dat","wb");

    if (ficheiroAulas == NULL)
    {
        printf("\nImpossível Abrir Ficheiro!\n");

    } else {

        fwrite (&quantAulas, sizeof(int), 1, ficheiroAulas);
        fwrite (vAulas, sizeof(tipoAula), quantAulas, ficheiroAulas);

        printf("\n Dados Escritos com Sucesso!\n\n A Voltar ao Menu dos Ficheiros Binários...\n");

        fclose (ficheiroAulas);
    }
}

tipoEstudante lerDadosEstudante(tipoAula vAulas[], int quantAulas, int *quantEstudantes)
{
    tipoEstudante dadosEstudantes;
    char designacaoAula[MAX_STRING];
    int pos;

    lerString("\n Qual é a Designação da Aula à Qual Quer que o Estudante Aceda? ",designacaoAula,MAX_STRING);
    pos = procurarAula(vAulas,quantAulas,designacaoAula);

    if (pos == -1)
    {
        printf("\n A Designação que Inseriu não Pertence a Qualquer Aula\n\n A Voltar ao Menu dos Estudantes...\n");
        (*quantEstudantes)--;

    } else {

        if (vAulas[pos].estadoAula != AGENDADA)
        {
            strcpy(dadosEstudantes.designacaoAula,designacaoAula);

            if (vAulas[pos].estadoAula == A_DECORRER)
            {
                dadosEstudantes.tipoAcesso=ONLINE;

            } else {

                if (vAulas[pos].opcaoGravacao=='S')
                dadosEstudantes.tipoAcesso=OFFLINE;
            }

        } else {

            printf("\n Essa Aula Ainda Está Agendada!\n\n A Voltar ao Menu do Estudantes...\n");
            (*quantEstudantes)--;
        }
    }

    return dadosEstudantes;
}

void inserirEstudante(tipoAula vAulas[], tipoEstudante vEstudantes[], int quantAulas, int *quantEstudantes)
{
    int pos, numEstudante;

    if (quantAulas==0)
    {
        printf("\n Não Há Qualquer Registo de Aulas!\n\n A Voltar Para o Menu dos Estudantes...\n");

    } else {

        printf("\n\t Introduza os Dados do %dº Estudante\n", (*quantEstudantes)+1);

        if (*quantEstudantes < MAX_ESTUDANTES)
        {
            numEstudante = lerInteiro("\n Introduza o Número do Estudante: ",1,10000);
            pos = procurarEstudante(vEstudantes, *quantEstudantes, numEstudante);

            if (pos != -1)
            {
                printf("\n O Número que Inseriu já Pertence a um Estudante\n\n A Voltar Para o Menu dos Estudantes...\n");

            } else {

                vEstudantes[*quantEstudantes] = lerDadosEstudante(vAulas, quantAulas, &(*quantEstudantes));
                vEstudantes[*quantEstudantes].numero = numEstudante;
                (*quantEstudantes)++;
            }

        } else {

            printf("\n Impossível Inserir Mais Estudantes!");
        }
    }
}

int procurarEstudante(tipoEstudante vEstudantes[], int quantEstudantes, int numEstudante)
{
    int i, pos=-1;

    for (i=0;i<quantEstudantes;i++)
    {
        if (vEstudantes[i].numero == numEstudante)
        {
            pos = i;
            i = quantEstudantes;
        }
    }

    return pos;
}
