#include "mech.h"
#include "dados.h"
#include "ui.h"

int main()
{
	tabuleiro_t gabarito;
	tabuleiro_t usr;
	jogada_t jog;
	vec v;
	int i, p = 0;
	
	do
	{
		//menu
		inicializa_tab( &gabarito );
		inicializa_tab( &usr );
		for(i = 0; i < get_q( gabarito ); i++) //colocar bombas
		{
			ColocarBombas( &gabarito );
		}		
		AvaliarVizinhos( &gabarito );
		while( get_jogada( jogada ) != 'x' && get_jogada( jogada ) != 'r' )
		{
			imprimirTabuleiro( usr );
			Lerjogada( &jog , usr );
			if( ( get_jogada( jogada ) == 'v' ) && ( get_gabarito( gabarito, get_coord( jogada ) ) == '0' ) )
			{
				Revela( &gabarito, &usr, get_coord( jogada ) );
			}
			p = p + ExecutaJogada( gabarito, &usr, &jogada );
			if( p = get_q( gabarito ) )//caso em que o jogador marcou todas as minas
			{
				set_jogada( &jog, 'x');//fim de jogo - vitória
			}
		}
		destroi_tab( &gabarito );
		destroi_tab( &usr );

	}while( get_jogada( jogada ) != 'x' );

	//imprimir pontuação
	//e se ele quiser jogar novamente?

	return 0;
}
