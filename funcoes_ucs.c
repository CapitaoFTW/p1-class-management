#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_ucs.h"
#include "estruturas.h"

void inserirDadosUC(tipoUC vUC[MAX_UC], int *quantUC){

    int pos, codigoUC;

    printf("\n\tIntroduza os Dados da UC Nº %d\n", (*quantUC)+1);

    if (*quantUC < MAX_UC)
    {
        codigoUC=lerInteiro("\n Introduza o Código da UC",1,10000);
        pos=procurarUC(vUC,*quantUC,codigoUC);

        if (pos != -1)
        {
            printf("\n O Código que Inseriu já Pertence a uma UC\n\n A Voltar Para o Menu das UCs...\n");

        } else {

            vUC[*quantUC] = lerDadosUC();
            vUC[*quantUC].codigo = codigoUC;
            (*quantUC)++;
        }

    } else {

        printf("\n Impossível Inserir Mais Dados!");
    }
}

tipoUC lerDadosUC()
{
    tipoUC dadosUC;
    char opcao;

    lerString("\n Qual é a Designação da UC? ",dadosUC.designacao,MAX_STRING);

    printf("\n Qual o tipo de UC?\n\n 1 - Obrigatória\n 2 - Opcional\n");
    dadosUC.tipoUC=lerInteiro("\n Opção",1,2);

    dadosUC.semestre=lerInteiro("\n Semestre",1,6);

    printf("\n Qual o Regime da UC?\n\n 1 - Diurno\n 2 - Pós-Laboral\n");
    dadosUC.regime=lerInteiro("\n Opção",1,2);

    do
    {
        printf("\n A UC Tem Aulas T?\n\n S - Sim\n N - Não\n");
        opcao=lerSimNao("\n Opção -> ");

        if (opcao=='S')
        {
            dadosUC.quantT=lerInteiro("\n Quantidade de Aulas T Previstas",1,1000);
            dadosUC.duracaoT=lerInteiro(" Duração de Cada Aula T (em minutos)",1,500);

        } else {

            dadosUC.quantT=0;
            dadosUC.duracaoT=0;
        }

        printf("\n Tem Aulas TP?\n\n S - Sim\n N - Não\n");
        opcao=lerSimNao("\n Opção -> ");

        if (opcao=='S')
        {
            dadosUC.quantTP=lerInteiro("\n Quantidade de Aulas TP Previstas",1,1000);
            dadosUC.duracaoTP=lerInteiro(" Duração de Cada Aula TP (em minutos)",1,500);

        } else {

            dadosUC.quantTP=0;
            dadosUC.duracaoTP=0;
        }

        printf("\n Tem Aulas PL?\n\n S - Sim\n N - Não\n");
        opcao=lerSimNao("\n Opção -> ");

        if (opcao=='S')
        {
            dadosUC.quantPL=lerInteiro("\n Quantidade de Aulas PL Previstas",1,1000);
            dadosUC.duracaoPL=lerInteiro(" Duração de Cada Aula PL (em minutos)",1,500);

        } else {

            dadosUC.quantPL=0;
            dadosUC.duracaoPL=0;
        }

        if (dadosUC.quantT == 0 && dadosUC.quantTP == 0 && dadosUC.quantPL == 0)
        {
            printf("\n Pelo Menos um Tipo de Aula a UC Terá de Ter!\n Tente Novamente!\n");
        }

        dadosUC.quantAgendadas=0;
        dadosUC.quantADecorrer=0;
        dadosUC.quantTRealizadas=0;
        dadosUC.quantTPRealizadas=0;
        dadosUC.quantPLRealizadas=0;

    } while (dadosUC.quantT == 0 && dadosUC.quantTP == 0 && dadosUC.quantPL == 0);

    return dadosUC;
}

int procurarUC(tipoUC vUC[],int quantUC,int codigoUC)
{
    int i, pos=-1;

    for (i=0;i<quantUC;i++)
    {
        if (vUC[i].codigo == codigoUC)
        {
            pos = i;
            i = quantUC;
        }
    }

    return pos;
}

void alterarDadosUC(tipoUC vUC[MAX_UC], int *quantUC)
{
    char opcao;
    int codigoUC, pos, op1, op2;

    do
    {
        opcao = 'N';

        if (*quantUC == 0)
        {
            printf("\n Ainda não Inseriu Dados Nenhuns!\n");

        } else {

                codigoUC = lerInteiro("\n Introduza o Código da UC cujos Dados Deseja Alterar",1,1000);
                pos = procurarUC(vUC, *quantUC, codigoUC);

                if (pos == -1)
                {
                    printf("\n O Código que Inseriu não Pertence a Qualquer UC\n\n A Voltar Para o Menu das UCs...\n");

                } else {

                    printf("\n Que Dados Quer Alterar?\n\n 1 - Designação\n 2 - Tipo de UC\n 3 - Semestre\n 4 - Regime\n 5 - Dados das Aulas T\n 6 - Dados das Aulas TP\n 7 - Dados das Aulas PL\n");

                    op1=lerInteiro("\n Opção",1,7);

                    if (op1 == 1)
                    {
                        printf("\n De %s Para", vUC[pos].designacao);
                        lerString(" ",vUC[pos].designacao,MAX_STRING);
                    }

                    if (op1==2)
                    {
                        printf("\n Tipo de UC Novo\n\n1 - Obrigatória\n2 - Opcional\n");
                        vUC[pos].tipoUC=lerInteiro("\n Opção",1,2);
                    }

                    if (op1==3)
                    vUC[pos].semestre=lerInteiro("\n Novo Semestre",1,6);

                    if (op1==4)
                    {
                        printf("\n Regime Novo\n\n1 - Diurno\n2 - Pós-Laboral\n");
                        vUC[pos].regime=lerInteiro("\n Opção",1,2);
                    }

                    if (op1==5)
                    {
                        if (vUC[pos].quantT != 0)
                        printf("\n Alterar Que Dados das Aulas T?\n\n 1 - Quantidade\n 2 - Duração\n");
                        op2=lerInteiro("\n Opção",1,2);


                        if (op2==1 || vUC[pos].quantT == 0)
                        vUC[pos].quantT=lerInteiro("\n Nova Quantidade de Aulas T Previstas",1,1000);

                        if (op2==2 || vUC[pos].duracaoT == 0)
                        vUC[pos].duracaoT=lerInteiro(" Nova Duração de Cada Aula T (em minutos)",1,500);
                    }

                    if (op1==6)
                    {
                        if (vUC[pos].quantTP != 0)
                        printf("\n Alterar Que Dados das Aulas TP?\n\n 1 - Quantidade\n 2 - Duração\n");
                        op2=lerInteiro("\n Opção",1,2);

                        if (op2==1 || vUC[pos].quantTP == 0)
                        vUC[pos].quantTP=lerInteiro("\n Nova Quantidade de Aulas TP Previstas\n",1,1000);

                        if (op2==2 || vUC[pos].duracaoTP == 0)
                        vUC[pos].duracaoTP=lerInteiro(" Nova Duração de Cada Aula TP (em minutos)",1,500);
                    }

                    if (op1==7)
                    {
                        if (vUC[pos].quantPL != 0)
                        {
                            printf("\n Alterar Que Dados das Aulas PL?\n\n 1 - Quantidade\n 2 - Duração\n");
                            op2=lerInteiro("\n Opção",1,2);
                        }

                        if (op2==1 || vUC[pos].quantPL == 0)
                        vUC[pos].quantPL=lerInteiro("\n Nova Quantidade de Aulas PL Previstas",1,1000);

                        if (op2==2 || vUC[pos].duracaoPL == 0)
                        vUC[pos].duracaoPL=lerInteiro(" Nova Duração de Cada Aula PL (em minutos)",1,500);
                    }

                    printf("\n Quer Alterar mais Dados Nesta ou Noutra UC?\n\n S - Sim\n N - Não\n");
                    opcao = lerSimNao("\n Opção -> ");
                }
            }

        } while (opcao == 'S');
}

void listarDadosUC(tipoUC dadosUC[MAX_UC], tipoAula dadosAulas[], int quantUC)
{
    int i;

    if (quantUC==0)
    {
        printf("\n Ainda não Inseriu Dados Nenhuns!\n");
    }

    for (i=0;i<quantUC;i++)
    {
        escreverDadosUC(dadosUC[i], dadosAulas);
    }
}

void escreverDadosUC(tipoUC dadosUC, tipoAula dadosAulas[])
{
    int i, incremento, contadorNumAulas=0;

    printf("\n -+ Dados de %s [Código %d] +-\n\n",dadosUC.designacao,dadosUC.codigo);

    if (dadosUC.tipoUC==OBRIGATORIA)
    {
        printf(" Obrigatória");

    } else {

        printf(" Opcional");
    }

    printf("\n %dº Semestre\n Regime ", dadosUC.semestre);

    if (dadosUC.regime==DIURNO)
    {
        printf("Diurno");

    } else {

        printf("Pós-Laboral");
    }

    if (dadosUC.quantT != 0)
    {
        printf("\n Tem %d Aulas T Previstas de %d Minutos Cada ", dadosUC.quantT, dadosUC.duracaoT);
    }

    if(dadosUC.quantTRealizadas != 0)
    printf("e %d Aulas Deste tipo já se Realizaram", dadosUC.quantTRealizadas);

    if (dadosUC.quantTP != 0)
    {
        printf("\n Tem %d Aulas TP Previstas de %d Minutos Cada ", dadosUC.quantTP, dadosUC.duracaoTP);
    }

    if(dadosUC.quantTPRealizadas != 0)
    printf("e %d Aulas Deste tipo já se Realizaram", dadosUC.quantTPRealizadas);

    if (dadosUC.quantPL != 0)
    {
        printf("\n Tem %d Aulas PL Previstas de %d Minutos Cada ", dadosUC.quantPL, dadosUC.duracaoPL);
    }

    if(dadosUC.quantPLRealizadas != 0)
    printf("e %d Dessas Aulas já se Realizaram", dadosUC.quantPLRealizadas);

    if (dadosUC.quantAgendadas != 0)
    printf("\n\n -+ Aulas Agendadas -+\n\n");

    incremento=dadosUC.quantAgendadas;

    for (i=0;i<incremento;i++)
    {
        printf(" %dª:", contadorNumAulas+1);

        if (dadosAulas[i].codigoUC==dadosUC.codigo)
        {
            if (dadosAulas[i].tipoAula==T)
            printf(" Aula T");

            if (dadosAulas[i].tipoAula==TP)
            printf(" Aula TP");

            if (dadosAulas[i].tipoAula==PL)
            printf(" Aula PL");

            printf(", Agendada para o Dia %02d/%02d/%02d às %02dh%02d\n", dadosAulas[i].dataAula.dia, dadosAulas[i].dataAula.mes, dadosAulas[i].dataAula.ano, dadosAulas[i].horaInicio.horas, dadosAulas[i].horaInicio.minutos);

            contadorNumAulas++;

        } else {

            incremento++;
        }
    }

    printf("\n");
}

void escreverUCFichBin(tipoUC vUC[], int quantUC)
{
    FILE *ficheiroUC;

    ficheiroUC = fopen("UC.dat","wb");

    if (ficheiroUC == NULL)
    {
        printf("\nImpossível Abrir Ficheiro!\n");

    } else {

        fwrite (&quantUC, sizeof(int), 1, ficheiroUC);
        fwrite (vUC, sizeof(tipoUC), quantUC, ficheiroUC);

        printf("\n Dados Escritos com Sucesso!\n\n A Voltar ao Menu dos Ficheiros Binários...\n");

        fclose (ficheiroUC);
    }
}

void lerUCFichBin(tipoUC vUC[], int *quantUC)
{
    FILE *ficheiroUC;

    ficheiroUC = fopen("UC.dat","rb");

    if (ficheiroUC == NULL)
    {
        printf("\nImpossível Abrir Ficheiro!\n");

    } else {

        fread (&(*quantUC), sizeof(int), 1, ficheiroUC);
        fread (vUC, sizeof(tipoUC), *quantUC, ficheiroUC);

        printf("\n Dados Lidos com Sucesso!\n\n A Voltar ao Menu dos Ficheiros Binários...\n");

        fclose (ficheiroUC);
    }
}
