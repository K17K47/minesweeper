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
		//inicializar tabuleiros
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
		}
		//destruir tabuleiros

	}while( get_jogada( jogada ) != 'x' );
	

	//imprimir pontuação
	//e se ele quiser jogar novamente?

	return 0;
}
