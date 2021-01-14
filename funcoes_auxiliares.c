#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "funcoes_auxiliares.h"
#include "constantes.h"

tipoData lerData(int semestre)
{
    tipoData data;

    data.ano=lerInteiro("\n Ano",MIN_ANO,MAX_ANO);

    if (semestre==1 || semestre==3 || semestre==5)
    {
        do
        {
            printf(" Mes (9 a 2) -> ");
            scanf("%d", &data.mes);

            limpaBufferStdin();

            if ((data.mes < SETEMBRO && data.mes > FEVEREIRO) || data.mes < 0 || data.mes > DEZEMBRO)
            {
                printf("\n Numero Invalido. Insira Novamente!\n\n");
            }

        } while ((data.mes < SETEMBRO && data.mes > FEVEREIRO) || data.mes < 0 || data.mes > DEZEMBRO);

    }

    if (semestre==2 || semestre==4 || semestre==6)
    {
        data.mes=lerInteiro(" Mes",MARCO,JUNHO);
    }

    if (data.mes==ABRIL || data.mes==JUNHO || data.mes==SETEMBRO || data.mes==NOVEMBRO)
    {
        data.dia=lerInteiro(" Dia",1,DIAS30);

    } else {

        if(data.mes==FEVEREIRO)
        {
            if(data.ano%4==0)
            {
                data.dia=lerInteiro(" Dia",1,MAX_DIA_FEVEREIRO_BISSEXTO);

            } else {

                data.dia=lerInteiro(" Dia",1,MAX_DIA_FEVEREIRO);
            }

        } else {

            data.dia=lerInteiro(" Dia",1,DIAS31);
        }
    }

    return data;
}

void lerHora(tipoUC *dadosUC, tipoAula *dadosAula)
{
    do
    {
        dadosAula->horaFim.horas=0;
        dadosAula->horaFim.minutos=0;

        if (dadosUC->regime==DIURNO)
        {
            dadosAula->horaInicio.horas=lerInteiro(" Horas",MIN_DIURNO,MAX_DIURNO);
            dadosAula->horaInicio.minutos=lerInteiro(" Minutos",MIN_MINUTOS,MAX_MINUTOS);

        } else {

            dadosAula->horaInicio.horas=lerInteiro(" Horas",MAX_DIURNO,MAX_POSLABORAL);
            dadosAula->horaInicio.minutos=lerInteiro(" Minutos",MIN_MINUTOS,MAX_MINUTOS);
        }

        if (dadosAula->tipoAula==T)
        {
            dadosAula->horaFim.minutos = dadosAula->horaInicio.minutos+dadosUC->duracaoT;

            while (dadosAula->horaFim.minutos >= UMA_HORA_EM_MINUTOS)
            {
                dadosAula->horaFim.minutos-=UMA_HORA_EM_MINUTOS;
                dadosAula->horaFim.horas++;
            }

            dadosAula->horaFim.horas+=dadosAula->horaInicio.horas;
        }

        if (dadosAula->tipoAula==TP)
        {
            dadosAula->horaFim.minutos = dadosAula->horaInicio.minutos+dadosUC->duracaoTP;

            while (dadosAula->horaFim.minutos >= UMA_HORA_EM_MINUTOS)
            {
                dadosAula->horaFim.minutos-=UMA_HORA_EM_MINUTOS;
                dadosAula->horaFim.horas++;
            }

            dadosAula->horaFim.horas+=dadosAula->horaInicio.horas;
        }

        if (dadosAula->tipoAula==PL)
        {
            dadosAula->horaFim.minutos = dadosAula->horaInicio.minutos+dadosUC->duracaoPL;

            while (dadosAula->horaFim.minutos >= UMA_HORA_EM_MINUTOS)
            {
                dadosAula->horaFim.minutos-=UMA_HORA_EM_MINUTOS;
                dadosAula->horaFim.horas++;
            }

            dadosAula->horaFim.horas+=dadosAula->horaInicio.horas;
        }

        if (dadosUC->regime==DIURNO && dadosAula->horaFim.horas>MAX_DIURNO)
        {
            printf("\n Tem de Introduzir uma Hora Inicial que, Acrescentando a Duracao da Aula, nao Ultrapasse a Hora Maxima do Regime Diurno!\n");
        }

        if (dadosUC->regime==POS_LABORAL && dadosAula->horaFim.horas>MAX_POSLABORAL)
        {
            printf("\n Tem de Introduzir uma Hora Inicial que, Acrescentando a Duracao da Aula, nao Ultrapasse a Hora Maxima do Regime Pos-Laboral!\n");
        }

    } while ((dadosUC->regime==DIURNO && dadosAula->horaFim.horas>MAX_DIURNO) || (dadosUC->regime==POS_LABORAL && dadosAula->horaFim.horas>MAX_POSLABORAL));
}

char lerSimNao(char mensagem[MAX_STRING])
{
    setlocale(LC_ALL, "Portuguese");

    char caracter;

    do
    {
        printf("%s ", mensagem);
        scanf (" %c", &caracter);
        limpaBufferStdin();

        caracter=toupper(caracter);

        if (caracter != 'S' && caracter != 'N')
        {
                printf("\n Introducao Invalida! Insira Novamente!\n");
        }

    } while (caracter != 'S' && caracter != 'N');

    return caracter;
}

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;

    do
    {
        printf("%s (%d a %d) -> ", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

        if (controlo == 0)
        {
            printf("\n Devera Inserir um Numero Inteiro!\n");

        } else {

            if (numero < minimo || numero > maximo)
            {
                printf("\n Numero Invalido. Insira Novamente!\n");
            }
        }

    } while (numero < minimo || numero > maximo || controlo == 0);

    return numero;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;

    do
    {
        printf("%s (%.2f a %.2f) -> ", mensagem, minimo, maximo);

        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("\n Devera Inserir um Numero Decimal (Float) \n");

        } else {

            if (numero < minimo || numero > maximo)
            {
                printf("\n Numero Invalido. Insira Novamente!\n");
            }

        }

    } while (numero < minimo || numero > maximo || controlo ==0);

    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf(" Nao Foram Introduzidos Caracteres! Apenas Carregou no ENTER \n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    } while (tamanhoString == 1);

    if (vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres

    } else {

        vetorCaracteres[tamanhoString-1] = '\0'; 	//Elimina o \n da string armazenada em vetor
    }
}

void limpaBufferStdin(void)
{
    char chr;

    do
    {
        chr = getchar();

    } while (chr != '\n' && chr != EOF);
}
