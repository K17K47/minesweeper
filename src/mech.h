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
//Protótipos

void CriarTabuleiroUsr( tabuleiro_t * usr );
void ColocarBombas( tabuleiro_t * gabarito );
void AvaliarVizinhos( tabuleiro_t * gabarito );
void Revela( tabuleiro_t * gabarito, tabuleiro_t * usr, vec v  );
int ExecutaJogada( tabuleiro_t gabarito, tabuleiro_t * usr, jogada_t * jogada );

#endif
