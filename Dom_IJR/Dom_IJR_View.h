// Dom_IJR_View.h - Projeto Domino
// 23/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#ifndef DOM_IJR_VIEW_H
#define DOM_IJR_VIEW_H

// Funcoes de menus e mensagens
int menuInicial(int jogoPausado);                   // Exibe o menu principal, com opcoes diferentes se um jogo estiver pausado
char menuDeEscolha();                               // Exibe o menu de acoes durante a jogada (J, C, P, S)
void mensagemOpcaoInvalida();                       // Exibe uma mensagem de opcao invalida
void mostrarRegras();                               // Exibe a tela com as regras completas do jogo
void anunciarJogador(int jogador);                  // Anuncia o jogador da vez e prepara a exibicao da sua mao
void anunciarPrimeiroLance(int jogador);            // Anuncia qual jogador realizou a primeira jogada
void anunciarVencedor(int jogador);                 // Exibe a tela de fim de jogo com o resultado
void anunciarCompraDePeca(int lado1, int lado2);    // Informa ao jogador qual peca ele acabou de comprar
void anunciarMensagem(const char* mensagem);        // Exibe uma mensagem generica na tela

// Apresentacao de dados
void apresentarMesa();                              // Desenha a mesa com as pecas ja jogadas
void apresentarMao(int jogatual);                   // Mostra na tela todas as pecas que o jogador atual possui

// Funcoes de entrada do usuario
int obterEscolhaPeca(int maxPecas);                 // Pede ao usuario para escolher uma peca da sua mao e valida a entrada
char obterLadoMesa();                               // Pede ao usuario para escolher um lado da mesa (Esquerda ou Direita)

#endif
