#include "mech.h"
#include "dados.h"
#include "ui.h"

int main()
{
	tabuleiro_t tab;
	jogada_t jog;
	int i, p = 0;

	do
	{
		opseguir( &tab, &i );
		inicializa_tab( &tab );

		CriarTabuleiroUsr( &tab );
		for(i = 0; i < get_q( tab ); i++) //colocar bombas
		{
			ColocarBombas( &tab );
		}
		AvaliarVizinhos( &tab );

		while( get_jogada( jog ) != 'x' && get_jogada( jog ) != 'r' )
		{
			imprimirTabuleiro( tab );
			lerJogada( &jog , tab );
			if( ( get_jogada( jog ) == 'v' ) && ( get_gabarito( tab, get_coord( jog ) ) == '0' ) )
			{
				Revela( &tab, get_coord( jog ) );
			}
			p = p + ExecutaJogada( &tab, &jog );
			if( p = get_q( tab ) )//caso em que o jogador marcou todas as minas
			{
				set_jogada( &jog, 'x');//fim de jogo - vitória
			}
		}

		fimDeJogo( p, tab, &jog );
		destroi_tab( &tab );

	}while( get_jogada( jog ) != 'x' );

	return 0;
}
