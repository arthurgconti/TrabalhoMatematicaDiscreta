#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define probNegar 1
#define probCaptura 45

void azulEnviarMsg();
void vermelhoEnviarMsg();
int probabilidade();
void azulNegandoCapturado();
void startTimestamp();
void azulConfirmandoCapturado();
long long int randomizarTempo();

int mensVerm = 5, mensAzul = 10, resultado = 0, sinalizador = 0, capturado = 0, rejeitado = 0, seed;
long long int tempo = 0, inicio;


int main()
{
    int horas, minutos, segundos, horas_seg = 3600;
    startTimestamp(&tempo);
    inicio = tempo;
    srand(seed);

    while ((sinalizador == 0) && (mensVerm > 0) && (mensAzul > 0))
    {
        (mensVerm)--;
        tempo += randomizarTempo();

        printf("O mensageiro vermelho foi enviado \n");

        if (probabilidade(probCaptura) == 1) //O mensageiro vermelho chegar
        {
            rejeitado = 0;
            printf("O mensageiro vermelho chegou no azul \n");
            while ((sinalizador == 0) && (rejeitado == 0) && (mensAzul > 0) && (mensVerm > 0)) //Enquanto o sinalizador não tiver sido disparado (mens azul chegou) ou mens azul chegou e foi rejeitado
            {

                azulEnviarMsg();

                switch (resultado)
                {
                case 1:
                {
                    (tempo) += randomizarTempo(); //Depois mudar para numero random entre 3600 e 4200!
                    sinalizador++;
                    break;
                }

                case 2:
                {
                    (tempo) += randomizarTempo(); //Depois mudar para numero random entre 3600 e 4200!
                    rejeitado++;
                    break;
                }

                case 3:
                {
                    capturado++;
                    void azulConfirmandoCapturado();
                    break;
                }

                default:
                {
                    azulNegandoCapturado();
                    break;
                }
                }
            }
        }

        else
        {
            printf("O mensageiro vermelho foi capturado\n");
            tempo += 12601;
        }
    }

    printf("------------------------------------------\n");
    if (sinalizador > 0)
    {
        printf("Ganharam!!\n");
    }
    else
    {
        printf("Perderam \n");
    }

    printf("------------------------------------------");
    printf("\nMensageiros restantes - Vermelho: %d, Azul: %d", mensVerm, mensAzul);
    printf("\nInicio da troca de mensagem: %lld\nTermino da troca de mensagem: %lld", inicio, tempo);
    double tempoGasto = difftime((time_t)tempo, (time_t)inicio);

    horas = (tempoGasto / horas_seg); //resultado da hora
    minutos = (tempoGasto - (horas_seg * horas)) / 60;
    segundos = (tempoGasto - (horas_seg * horas) - (minutos * 60));
    printf("\nTempo total gasto: %dh:%dm:%ds", horas, minutos, segundos);
    printf("\n------------------------------------------\n");
    printf("Seed utilizada: %d",seed);
    printf("\n------------------------------------------\n");

    return 0;
}

void startTimestamp(long long int *tempo)
{
    time_t segundos;
    segundos = time(NULL);
    *tempo = segundos;
    seed = segundos;
}
void azulEnviarMsg()
{
    mensAzul--;

    if (probabilidade(probNegar) == 1) // Azul aceita
    {
        if (probabilidade(probCaptura) == 1) // Mensageiro chega
        {
            resultado = 1; // caso prob 45 ==1 e prob 1 == 1
            printf("O mensageiro azul chegou no vermelho\n");
        }

        else
        {
            resultado = 3; // caso prob 45 == 0  e prob 1 == 0 mensageiro foi capturado
            printf("O mensageiro azul foi capturado\n");
        }
    }

    else
    {
        if (probabilidade(probCaptura) == 1) // Mensageiro chega mas azul nao aceita
        {
            resultado = 2; // prob 45 == 1 e prob 1 == 0, mensageiro chega mas nao aceitaram
            printf("Azul negou o pedido, e o mensageiro chegou no vermelho \n");
        }
        else
        {

            resultado = 4; //  prob 45 == 0 e prob 1 == 0 mensageiro foi capturado
            // printf("Azul negou o pedido, e o mensageiro foi capturado \n");
        }
    }
}

int probabilidade(int porcentagem)
{
    int nAleatorio = rand() % 100;

    switch (porcentagem)
    {
        case 1:
        {
            if (nAleatorio > porcentagem) //numero aleatorio > 1 , logo azul aceita
                return 1;                 //deu bão, aceitaram
            else
                return 0;
            break;
        }

        default:
        {
            if (nAleatorio < porcentagem) //numero aleatorio < 45 , logo capturado
                return 1;                 //deu bão, nao foram capturados
            else
                return 0;
            break;
        }
    }
}

long long int randomizarTempo()
{
    return (3600 + rand() % (4200 + 1 - 3600));
}

void azulNegandoCapturado()
{

    while ((probabilidade(probCaptura) == 0) && (mensAzul > 0) && (mensVerm > 0))
    {
        tempo += 4201; //Depois mudar para 4201 SEGUNDOS!  pois eles esperam 70 min e 1 segundo pra enviar outro quando captura
        printf("O mensageiro azul negando o pedido foi capturado\n");
        mensAzul--;
        capturado++;

        if (capturado == 3)
        {
            mensVerm--;
            capturado = 0;
            printf("\n Deu 210 minutos vermelho mandou mais um\n");
        }
    }

    printf("O mensageiro azul negando o pedido chegou no exercito vermelho\n");
    rejeitado++;
}

void azulConfirmandoCapturado()
{

    while ((probabilidade(probCaptura) == 0) && (mensAzul > 0) && (mensVerm > 0))
    {
        tempo += 4201; //Depois mudar para 4201 SEGUNDOS!  pois eles esperam 70 min e 1 segundo pra enviar outro quando captura
        printf("O mensageiro azul CONFIRMANDO o pedido foi capturado\n");
        (mensAzul)--;
        capturado++;

        if (capturado == 3)
        {
            (mensVerm)--;
            capturado = 0;
            printf("\n Deu 210 minutos verm mandou mais um");
        }
    }
}