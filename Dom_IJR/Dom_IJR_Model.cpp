// Dom_IJR_Model.cpp - Projeto Domino
// 09/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#include <stdlib.h>
#include <stdio.h>


#include "Dom_IJR_Model.h"


struct Peca pecas[28];
struct Mesa mesa[28];
struct Jogo jogo;

int qtmesa = 0;
int jogatual = 0;
int extremaE;
int extremaD;
int jogoEmPausa = 0;
int modoDeJogo = 0;

void iniciarPecas()
{
    int contador = 0;
    for (int i = 0; i <= 6; i++)
    {
        for (int j = i; j <= 6; j++)
        {
            pecas[contador].lado1 = i;
            pecas[contador].lado2 = j;
            pecas[contador].status = 'D'; // D de Disponivel
            contador++;
        }
    }
}


void inicializarMesa()
{
    for (int i = 0; i < 28; i ++)
    {
        mesa[i].ladoE = -1; // Usa -1 para espaco vazio
        mesa[i].ladoD = -1;
    }
    qtmesa = 0;
}


void embaralharPecas()
{
    for (int i = 0; i < 28; i++)
    {
        int r = rand() % 28;
        struct Peca temp = pecas[i];
        pecas[i] = pecas[r];
        pecas[r] = temp;
    }
}


void distribuirPecas()
{
    for (int i = 0; i <= 6; i++)
    {
        pecas[i].status = '1';
    }
    for (int i = 7; i < 14; i++)
    {
        pecas[i].status = '2';
    }
}


int primeiroLance()
{
    int indicePeca = -1;
    int maiorCarroca = -1;
    int maiorSoma = -1;

    for (int i = 0; i < 14; i++)
    {
        if (pecas[i].lado1 == pecas[i].lado2)
        {
            if (pecas[i].lado1 > maiorCarroca)
            {
                maiorCarroca = pecas[i].lado1;
                indicePeca = i;
            }
        }
    }

    if (indicePeca == -1)
    {
        for (int i = 0; i < 14; i++)
        {
            int soma = pecas[i].lado1 + pecas[i].lado2;
            if (soma > maiorSoma)
            {
                maiorSoma = soma;
                indicePeca = i;
            }
        }
    }

    mesa[0].ladoE = pecas[indicePeca].lado1;
    mesa[0].ladoD = pecas[indicePeca].lado2;
    extremaE = pecas[indicePeca].lado1;
    extremaD = pecas[indicePeca].lado2;
    pecas[indicePeca].status = 'M';
    qtmesa = 1;

    if (indicePeca >= 0 && indicePeca < 7)
    {
        jogatual = 1;
    }
    else
    {
        jogatual = 2;
    }
    return jogatual;
}


int indicePeca(int indiceNaMao, int jogador)
{
    char statusJogador = (jogador == 1) ? '1' : '2';
    int contadorMao = 0;
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == statusJogador)
        {
            if (contadorMao == indiceNaMao)
            {
                return i;
            }
            contadorMao++;
        }
    }
    return -1;
}


int jogarPeca(int indicePecaReal, char ladoMesa)
{
    struct Peca p = pecas[indicePecaReal];
    int ladoPecaParaConectar = -1;
    int ladoOposto = -1;

    if (ladoMesa == 'E')
    {
        if (p.lado1 == extremaE)
        {
            ladoPecaParaConectar = p.lado1;
            ladoOposto = p.lado2;
        }
        else if (p.lado2 == extremaE)
        {
            ladoPecaParaConectar = p.lado2;
            ladoOposto = p.lado1;
        }
        else
        {
            return 0; // Jogada invalida
        }
        for (int i = qtmesa; i > 0; i--)
        {
            mesa[i] = mesa[i - 1];
        }
        mesa[0].ladoE = ladoOposto;
        mesa[0].ladoD = ladoPecaParaConectar;
        extremaE = ladoOposto;
    }
    else // Jogar na Direita
    {
        if (p.lado1 == extremaD)
        {
            ladoPecaParaConectar = p.lado1;
            ladoOposto = p.lado2;
        }
        else if (p.lado2 == extremaD)
        {
            ladoPecaParaConectar = p.lado2;
            ladoOposto = p.lado1;
        }
        else
        {
            return 0; // Jogada invalida
        }
        mesa[qtmesa].ladoE = ladoPecaParaConectar;
        mesa[qtmesa].ladoD = ladoOposto;
        extremaD = ladoOposto;
    }

    pecas[indicePecaReal].status = 'M';
    qtmesa++;
    return 1; // Sucesso
}


int comprarPeca(int jogador)
{
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == 'D')
        {
            pecas[i].status = (jogador == 1) ? '1' : '2';
            return i;
        }
    }
    return -1;
}


int temJogadaPossivel(int jogador)
{
    char statusJogador = (jogador == 1) ? '1' : '2';
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == statusJogador)
        {
            if (pecas[i].lado1 == extremaE || pecas[i].lado2 == extremaE ||
                pecas[i].lado1 == extremaD || pecas[i].lado2 == extremaD)
            {
                return 1; // Tem jogada
            }
        }
    }
    return 0; // Nao tem jogada
}


int contarPecasJogador(int jogador)
{
    int contador = 0;
    char statusJogador = (jogador == 1) ? '1' : '2';
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == statusJogador)
        {
            contador++;
        }
    }
    return contador;
}


int existemPecasDisponiveis()
{
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == 'D')
        {
            return 1; // Existem
        }
    }
    return 0; // Acabaram
}


char analisarJogada(int indicePeca)
{
    int lado1 = pecas[indicePeca].lado1;
    int lado2 = pecas[indicePeca].lado2;

    int encaixaE = (lado1 == extremaE || lado2 == extremaE);
    int encaixaD = (lado1 == extremaD || lado2 == extremaD);

    if (encaixaE && encaixaD)
    {
        if (extremaE == extremaD) return 'E';
        return 'A'; // Ambos
    }
    if (encaixaE)
    {
        return 'E'; // Esquerda
    }
    if (encaixaD)
    {
        return 'D'; // Direita
    }
    return 'N'; // Nenhuma
}