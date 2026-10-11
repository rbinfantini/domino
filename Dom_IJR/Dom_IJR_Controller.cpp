// Dom_IJR_Controller.cpp - Projeto Domino
// 09/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "Dom_IJR_Controller.h"
#include "Dom_IJR_Model.h"
#include "Dom_IJR_View.cpp"


void iniciarPrograma()
{
    int opcao;
    do
    {
        opcao = menuInicial(jogoEmPausa);

        if (jogoEmPausa)
        {
            switch (opcao)
            {
                case 1: // Retornar ao jogo
                    iniciarJogo();
                    break;
                case 2: // Iniciar novo jogo
                    prepararJogo();
                    break;
                case 3: // Salva o jogo
                    salvarJogo();
                    break;
                case 4: // Regras do jogo
                    mostrarRegras();
                    break;
            }
        } else {
            switch (opcao)
            {
                case 1: // Jogador vs Jogador
            		modoDeJogo = 2;
            		prepararJogo();
           	 		break;
                case 2: // Jogador vs Computador
            		modoDeJogo = 1;
            		prepararJogo();
            		break;
            	case 3:
            		carregarJogo();
            		break;
                case 4:
                    mostrarRegras();
                    break;
            }
        }
    } while (opcao != 0);
}


void prepararJogo()
{
    jogoEmPausa = 0;
    iniciarPecas();
    inicializarMesa();
    embaralharPecas();
    distribuirPecas();

    int primeiro = primeiroLance();
    system("cls");
    anunciarPrimeiroLance(primeiro);
    apresentarMesa();
    system("pause");

    iniciarJogo();
}


void trocarJogador()
{
    jogatual = (jogatual == 1) ? 2 : 1;
}


int processarJogada(char opcao, int* pJogoAtivo)
{
    switch (opcao)
    {
        case 'J':
        {
            int indiceNaMao;
            int indiceReal;
            char lado;
            int numPecasNaMao = contarPecasJogador(jogatual);

            indiceNaMao = obterEscolhaPeca(numPecasNaMao);
            indiceReal = indicePeca(indiceNaMao, jogatual);

            char ladoPossivel = analisarJogada(indiceReal);

            if (ladoPossivel == 'A')
            {
                lado = obterLadoMesa();
            }
            else if (ladoPossivel == 'E' || ladoPossivel == 'D')
            {
                lado = ladoPossivel;
            }
            else
            {
                anunciarMensagem("Jogada invalida! Esta peca nao encaixa em nenhum lado.");
                return 0;
            }

            if (jogarPeca(indiceReal, lado))
            {
                anunciarMensagem("Jogada realizada com sucesso!");
                return 1;
            }
            break;
        }
        case 'C':
        {
            int indicePecaComprada = comprarPeca(jogatual);
            if (indicePecaComprada != -1)
            {
                anunciarCompraDePeca(pecas[indicePecaComprada].lado1, pecas[indicePecaComprada].lado2);
            }
            else
            {
                anunciarMensagem("Nao ha mais pecas para comprar!");
            }
            return 0; // Comprar uma peca nao passa o turno
            break;
        }
        case 'P':
        {
            if (temJogadaPossivel(jogatual))
            {
                anunciarMensagem("Voce tem uma jogada possivel, nao pode passar!");
                return 0;
            }
            else if (existemPecasDisponiveis())
            {
                anunciarMensagem("Voce precisa comprar pecas antes de passar!");
                return 0;
            }
            else
            {
                anunciarMensagem("Jogador passou a vez.");
                return 1; // Passar a vez passa o turno
            }
            break;
        }
         case 'S':
            *pJogoAtivo = 0;
            jogoEmPausa = 1;
            anunciarMensagem("Jogo interrompido.");
            return 0;
    }
    return 0;
}


int verificarFimDeJogo()
{
    if (contarPecasJogador(jogatual) == 0)
    {
        anunciarVencedor(jogatual);
        return 0; // Jogo terminou
    }

    if (!existemPecasDisponiveis() && !temJogadaPossivel(1) && !temJogadaPossivel(2))
    {
        anunciarVencedor(0); // Jogo trancado
        return 0; // Jogo terminou
    }

    return 1; // Jogo não terminou
}


void salvarJogo()
{
    FILE *fpPecas, *fpMesa, *fpJogo;


    jogo.qtmesaJogo = qtmesa;
    jogo.jogador = jogatual;
    jogo.pecaE = extremaE;
    jogo.pecaD = extremaD;


    if ((fpPecas = fopen("pecas.dat", "w")) == NULL ||
        (fpMesa = fopen("mesa.dat", "w")) == NULL ||
        (fpJogo = fopen("jogo.dat", "w")) == NULL)
    {
        anunciarMensagem("Erro ao salvar o jogo");
        return;
    }


    fwrite(&pecas, sizeof(struct Peca), 28, fpPecas);
    fwrite(&mesa, sizeof(struct Mesa), 28, fpMesa);
    fwrite(&jogo, sizeof(struct Jogo), 1, fpJogo);


    fclose(fpPecas);
    fclose(fpMesa);
    fclose(fpJogo);

    anunciarMensagem("Jogo salvo");
    system("pause");
}


void carregarJogo()
{
    FILE *fpPecas, *fpMesa, *fpJogo;


    if ((fpPecas = fopen("pecas.dat", "r")) == NULL ||
        (fpMesa = fopen("mesa.dat", "r")) == NULL ||
        (fpJogo = fopen("jogo.dat", "r")) == NULL)
    {
        anunciarMensagem("Jogo nao encontrado");
        system("pause");
        return;
    }

    
    fread(&pecas, sizeof(struct Peca), 28, fpPecas);
    fread(&mesa, sizeof(struct Mesa), 28, fpMesa);
    fread(&jogo, sizeof(struct Jogo), 1, fpJogo);


    fclose(fpPecas);
    fclose(fpMesa);
    fclose(fpJogo);


    qtmesa = jogo.qtmesaJogo;
    jogatual = jogo.jogador;
    extremaE = jogo.pecaE;
    extremaD = jogo.pecaD;
  
    
    anunciarMensagem("Jogo carregado. Retomando partida...");
    system("pause");


    jogoEmPausa = 1; 
    iniciarJogo();
}

void executarJogadaComputador()
{

    while (1)
    {
        int indicePecaParaJogar = -1;
        int maoComputador[7];
        int pecasNaMao = 0;

        char statusComputador = '2';
        for (int i = 0; i < 28; i++)
        {
            if (pecas[i].status == statusComputador)
            {
                if (analisarJogada(i) != 'N')
                {
                    indicePecaParaJogar = i;
                    break;
                }
            }
        }

        // Se encontrou uma peca para jogar
        if (indicePecaParaJogar != -1)
        {
            char lado = analisarJogada(indicePecaParaJogar);
            if (lado == 'A') // Escolhe a direita por padrao
            {
                lado = 'D';
            }

            printf("O computador joga a peca [%d|%d] no lado %c.\n", pecas[indicePecaParaJogar].lado1, pecas[indicePecaParaJogar].lado2, lado);
			jogarPeca(indicePecaParaJogar, lado);
            break;
        }
        else // Nao encontrou peca para jogar
        {
            if (existemPecasDisponiveis())
            {
                int pecaCompradaIdx = comprarPeca(2); // Computador compra
                anunciarMensagem("O computador comprou uma peca.");
            }
            else
            {
                anunciarMensagem("O computador nao tem jogadas e nao ha pecas para comprar. Passou a vez.");
                break;
            }
        }
    }
}


void iniciarJogo()
{
    int jogoAtivo = 1;
    if (!jogoEmPausa)
    {
        trocarJogador();
    }


    do
    {
        system("cls");
        anunciarJogador(jogatual);
        apresentarMesa();

        int deveTrocar = 0;

        // Se for a vez do computador
        if (modoDeJogo == 1 && jogatual == 2)
        {
            apresentarMao(1);
            executarJogadaComputador();
            deveTrocar = 1;
        }
        else
        {
            apresentarMao(jogatual);
            char opcao = menuDeEscolha();
            deveTrocar = processarJogada(opcao, &jogoAtivo);
        }

        if (!jogoAtivo)
        {
            break;
        }

        if (verificarFimDeJogo() == 0)
        {
            jogoAtivo = 0;
        }
        else if (deveTrocar == 1)
        {
            trocarJogador();
        }

        if (jogoAtivo)
        {
            printf("\n");
            system("pause");
        }

    } while (jogoAtivo);
    system("pause");
}