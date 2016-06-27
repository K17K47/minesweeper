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
		opseguir( &tab, &i );
		if( i == 0 )
		{
			break; //opção de sair do jogo
		}

		inicializa_tab( &tab );

		CriarTabuleiroUsr( &tab );
		ColocarBombas( &tab );		
		AvaliarVizinhos( &tab );

		p = 0;
		set_jogada( &jog, 'd');

		while( !( get_jogada( jog ) == 's' || get_jogada( jog ) == 'r' ) )
		{
			imprimirTabuleiro( tab );
			lerJogada( &jog , tab );
			if( ( get_jogada( jog ) == 'v' ) && ( get_gabarito( tab, get_coord( jog ) ) == '0' ) )
			{
				Revela( &tab, get_coord( jog ) );
			}
			ExecutaJogada( &tab, &jog, &p );
			if( p == get_q( tab ) ) //caso em que o jogador marcou todas as minas
			{
				set_jogada( &jog, 'r'); //fim de jogo - vitória, 'r' permite que ele jogue novamente
			}
		}

		fimDeJogo( p, tab );
		destroi_tab( &tab );

	}while( get_jogada( jog ) != 's' );

	return 0;
}
