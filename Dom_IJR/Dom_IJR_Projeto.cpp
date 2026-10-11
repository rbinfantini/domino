// Dom_IJR_Projeto.cpp - Projeto Domino
// 09/09/2025 - Grupo IJR
// Igor Elias
// Joao Batistella da Costa
// Rafael Barros Infantini


#include <stdlib.h>
#include <time.h>
#include <stdio.h>


// A ordem dos #include e importante
// Arquivos de implementacao do Model e Controller
#include "Dom_IJR_Model.cpp"
#include "Dom_IJR_Controller.cpp"


int main()
{
	srand(time(NULL)); // Prepara o gerador de numeros aleatorios
	iniciarPrograma(); // Chama a funcao principal do Controller

	return 0;
}
