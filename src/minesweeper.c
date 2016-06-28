#include "mech.h"
#include "dados.h"
#include "ui.h"

int main()
{
	tabuleiro_t tab;
	jogada_t jog;
	int i, p;

	do
	{
		opseguir( &tab, &i ); // Chama menu principal.
		if( i == 0 )
		{
			break; // Opção de sair do jogo no menu principal.
		}

		inicializa_tab( &tab ); // Reserva espaço na memória para o tabuleiro.

		CriarTabuleiroUsr( &tab ); // Preparação do tabuleiro mostrado ao usuário e tabuleiro "gabarito".
		ColocarBombas( &tab );		
		AvaliarVizinhos( &tab );

		p = 0; // Inicializa contador de bombas marcadas.
		set_jogada( &jog, 'd'); // Atribui valor à opção de jogada permitindo entrar no laço das jogadas.

		while( !( get_jogada( jog ) == 's' || get_jogada( jog ) == 'r' ) )
		{
			imprimirTabuleiro( tab ); // Mostra tabuleiro ao usuário.
			lerJogada( &jog , tab ); // Recebe jogada do usuário.
			if( ( get_jogada( jog ) == 'v' ) && ( get_gabarito( tab, get_coord( jog ) ) == '0' ) ) // Caso em que jogador marcou casa que continha zero como vazia.
			{
				Revela( &tab, get_coord( jog ) ); // Função específica para revelar zeros e seus vizinhos.
			}
			ExecutaJogada( &tab, &jog, &p ); // Função que avalia e executa jogadas possíveis.
			if( p == get_q( tab ) ) // Caso em que o jogador marcou todas as minas.
			{
				set_jogada( &jog, 'r'); // Fim de jogo - vitória, 'r' permite que ele jogue novamente.
			}
		}

		fimDeJogo( p, tab ); // Imprime mensagem de fim de jogo.
		destroi_tab( &tab ); // Libera espaço na memória usado pelo tabuleiro.

	}while( get_jogada( jog ) != 's' );

	return 0;
}
