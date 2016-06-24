/*
 *
 * Header: mech.h
 *
 * Protótipos das funções da mecânica de jogo
 *
 */

#ifndef MECH_H_
#define MECH_H_

#include "dados.h"

void CriarTabuleiroUsr( tabuleiro_t * usr );
void ColocarBombas( tabuleiro_t * gabarito );
void AvaliarVizinhos( tabuleiro_t * gabarito );
void Revela( tabuleiro_t * gabarito, vec v  );
void ExecutaJogada( tabuleiro_t* gabarito, jogada_t * jogada, int * p );

#endif
