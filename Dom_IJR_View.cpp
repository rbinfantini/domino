// Dom_IJR_View.cpp - Projeto Domino
// 09/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "Dom_IJR_View.h"
#include "Dom_IJR_Model.h"


int menuInicial(int jogoPausado)
{
    int opcao;
    system("cls");
    printf("===== PROJETO DOMINO =====\n\n");

if (jogoPausado)
{
    printf("1 - Retomar jogo\n");
    printf("2 - Iniciar novo jogo\n");
    printf("3 - Salvar jogo\n");
    printf("4 - Regras do Jogo\n");
} 

else 
{
    printf("1 - Iniciar jogo (2 jogadores)\n");
    printf("2 - Iniciar jogo (contra o computador)\n");
    printf("3 - Carregar jogo salvo\n");
    printf("4 - Regras do Jogo\n");
}

    printf("0 - Sair\n");
    printf("========================\n");
    printf("Selecionar opcao: ");
    scanf("%d", &opcao);
    return opcao;
}


void apresentarMesa()
{
    printf("======================== MESA ========================\n");
    if (qtmesa > 0)
    {
        printf("\t");
        for (int i = 0; i < qtmesa; i++)
        {
            printf("[%d|%d]", mesa[i].ladoE, mesa[i].ladoD);
        }
        printf("\n======================================================\n");
    }
    else
    {
        printf("\tA mesa esta vazia.\n");
        printf("======================================================\n");
    }
}


void apresentarMao(int jogatual)
{
    char statusJogador = (jogatual == 1) ? '1' : '2';
    int contadorDePecas = 0;
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == statusJogador)
        {
            printf("%d.[%d|%d] ", contadorDePecas + 1, pecas[i].lado1, pecas[i].lado2);
            contadorDePecas++;
        }
    }
    printf("\n");
}


char menuDeEscolha()
{
    char opcao;
    printf("\n---------- OPCOES DE JOGADA ----------\n");
    printf("J - Jogar (nas extremidades %d ou %d)\n", extremaE, extremaD);
    printf("C - Comprar\n");
    printf("P - Passar\n");
    printf("S - Interromper jogo\n");
    printf("------------------------------------\n");
    printf("Opcao: ");
    scanf(" %c", &opcao);
    return toupper(opcao);
}


int obterEscolhaPeca(int maxPecas)
{
    int escolha;
    do
    {
        printf("Escolha o numero da peca para jogar (1 a %d): ", maxPecas);
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > maxPecas)
        {
            printf("Escolha invalida.\n");
        }
    } while (escolha < 1 || escolha > maxPecas);
    return escolha - 1;
}


char obterLadoMesa()
{
    char lado;
    do
    {
        printf("Escolha o lado da Mesa (E para Esquerda, D para Direita): ");
        scanf(" %c", &lado);
        lado = toupper(lado);
        if (lado != 'E' && lado != 'D')
        {
            printf("Lado invalido.\n");
        }
    } while (lado != 'E' && lado != 'D');
    return lado;
}


void mensagemOpcaoInvalida()
{
    printf("Opcao invalida. Tente novamente.\n");
}


void anunciarJogador(int jogador)
{
    printf("\n\n-- Vez do Jogador %d --\n", jogador);
    printf("\nSua mao:\n");
}


void anunciarPrimeiroLance(int jogador)
{
    printf("O jogador %d fez o primeiro lance\n", jogador);
}

void anunciarVencedor(int jogador)
{
    system("cls");
    printf("======================== FIM DE JOGO ========================\n");
    if (jogador > 0)
    {
        if (jogador == 2 && modoDeJogo == 1) // Verifica se o vencedor e o jogador 2 e se estamos no modo contra o computador
        {
            printf("\n\tO COMPUTADOR VENCEU\n\n");
        }
        else // Para o jogador 1 ou para o jogador 2 no modo de 2 jogadores
        {
            printf("\n\tO JOGADOR %d VENCEU\n\n", jogador);
        }
    }
    else
    {
        printf("\n\tJOGO TRANCADO! Nao ha vencedor.\n\n");
    }
    printf("=============================================================\n");
}


void anunciarCompraDePeca(int lado1, int lado2)
{
    printf("Voce comprou a peca [%d|%d]\n", lado1, lado2);
}


void anunciarMensagem(const char* mensagem)
{
    printf("%s\n", mensagem);
}


void mostrarRegras()
{
    system("cls");
    printf("========================= REGRAS DO JOGO =========================\n\n");
    printf("- O conjunto de domino e formado por 28 pecas.\n");
    printf("- Cada jogador inicia com sete pecas obtidas aleatoriamente.\n");
	printf("- O jogo inicia-se com o jogador que tiver a peca seis-seis.\n");
    printf("- Caso ninguem tenha, comeca quem tiver o numero repetido mais alto.\n");
    printf("- Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas\n");
    printf("  que se encontram nas 2 extremidades da mesa.\n");
    printf("- Se um jogador nao puder jogar, devera comprar do monte.\n");
    printf("- O jogador so podera passar a vez se nao puder jogar e se nao houver mais pecas para comprar.\n");
    printf("- A partida termina quando um jogador colocar sua ultima peca na mesa (bater) ou quando o jogo ficar fechado.\n");
    printf("- Vence aquele que tiver menos pecas em seu poder.\n\n");
    printf("==================================================================\n");
    system("pause");
}
