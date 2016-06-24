/*
 *
 * Header: ui.h
 *
 * Protótipos das funções da interface de usuário
 *
 */

#ifndef UI_H_
#define UI_H_

#include "dados.h"

void imprimirTabuleiro ( tabuleiro_t tab );
void lerJogada ( jogada_t* jog , tabuleiro_t tab );

#endif
