/*###############################################################################
# Universidade de Brasilia														#
#	Trabalho 7 da disciplina de Introducao ao Desenvolvimento de Jogos			#
#	Aluno: Fernando Sobral Nobrega				Matricula: 15/0034911			#
#	OS: Windows 10 Pro															#
#	IDE: Visual Studio 2017														#
###############################################################################*/


#include "Game.h"
#include "TitleState.h"
#include "StageState.h"
#include "EndState.h"

int main(int argc, char* argv[]) {
	Game::GetInstance().Push(new TitleState);			// Seta o primeiro estado de jogo como sendo TitleState
	Game::GetInstance().Run();							// Comeca a rodar o jogo
	return 0;
}