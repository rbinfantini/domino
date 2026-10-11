// Dom_IJR_Model.h - Projeto Domino
// 09/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#ifndef DOM_IJR_MODEL_H
#define DOM_IJR_MODEL_H


struct Peca
	{
    int lado1;
    int lado2;
    char status; // Status da peca
	};


struct Mesa
	{
    int ladoE; 
    int ladoD;
	};


struct Jogo // Para salvar o jogo
{
    int qtmesaJogo;
    int jogador;
    int pecaD;
    int pecaE;
};


extern struct Peca pecas[28]; // Declara como 'extern' para que outros arquivos que incluam este .h 
extern struct Mesa mesa[28];  // saibam que a variavel existe e sera definida no Dom_IJR_Model.cpp
extern struct Jogo jogo;


extern int qtmesa;      // Quantidade de pecas na mesa
extern int jogatual;    // Indica o jogador da vez
extern int extremaD;    // Peca na extrema direita da mesa
extern int extremaE;    // Peca na extrema esquerda da mesa
extern int jogoEmPausa; // Indica se o jogo esta pausado
extern int modoDeJogo;  // 2 jogadores ou vs. computador


void iniciarPecas();        // Monta as 28 pecas do jogo
void embaralharPecas();     // Embaralha as pecas
void inicializarMesa();     // Prepara as pecas e limpa a mesa
void distribuirPecas();     // Distribui as pecas
int primeiroLance();        // Determina e executa a primeira jogada


int jogarPeca(int indicePecaNaMao, char ladoMesa);      // Joga uma peca na mesa
int comprarPeca(int jogador);                           // A funcao retorna o indice da peça comprada ou -1
int temJogadaPossivel(int jogador);                     // Verifica se ha jogadas possiveis
int contarPecasJogador(int jogador);                    // Retorna o numero de pacas na mao
int existemPecasDisponiveis();                          // Verifica se ha pecas para comprar
int indicePeca(int indiceNaMao, int jogador);           // Converte o indice da mao para o indice real do array de pecas
char analisarJogada(int indicePeca);                    // Indica em qual lado da mesa a jogada pode ser feita


#endif
