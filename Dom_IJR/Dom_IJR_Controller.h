// Dom_IJR_Controller.h - Projeto Domino
// 23/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#ifndef DOM_IJR_CONTROLLER_H
#define DOM_IJR_CONTROLLER_H


void iniciarPrograma();                             // Inicia o programa e gerencia o menu principal
void prepararJogo();                                // Prepara um novo jogo: cria, embaralha e distribui as pecas
void iniciarJogo();                                 // Inicia e controla o loop principal de uma partida
void executarJogadaComputador();                    // Executa a logica de decisao para a jogada do computador

void trocarJogador();                               // Alterna entre o jogador 1 e 2
int processarJogada(char opcao, int* pJogoAtivo);   // Processa a acao do jogador e retorna 1 se o turno deve passar
int verificarFimDeJogo();                           // Verifica se o jogo terminou por vitoria ou bloqueio


void salvarJogo();                                  // Salva o estado atual do jogo em um arquivo
void carregarJogo();                                // Carrega um jogo salvo de um arquivo

#endif
