#include "mech.h"
#include "dados.h"
#include "ui.h"

int main()
{
	tabuleiro_t tab;
	jogada_t jog;
	vec v;
	int i, p = 0;
	
	do
	{
		//menu
		inicializa_tab( &tab );
		CriarTabuleiroUsr( &tab )
		for(i = 0; i < get_q( tab ); i++) //colocar bombas
		{
			ColocarBombas( &tab );
		}		
		AvaliarVizinhos( &tab );
		while( get_jogada( jogada ) != 'x' && get_jogada( jogada ) != 'r' )
		{
			imprimirTabuleiro( tab );
			Lerjogada( &jog , tab );
			if( ( get_jogada( jogada ) == 'v' ) && ( get_gabarito( tab, get_coord( jogada ) ) == '0' ) )
			{
				Revela( &tab, get_coord( jogada ) );
			}
			p = p + ExecutaJogada( &tab, &jogada );
			if( p = get_q( tab ) )//caso em que o jogador marcou todas as minas
			{
				set_jogada( &jog, 'x');//fim de jogo - vitória
			}
		}
		destroi_tab( &tab );
	}while( get_jogada( jogada ) != 'x' );

	//imprimir pontuação
	//e se ele quiser jogar novamente?

	return 0;
}
