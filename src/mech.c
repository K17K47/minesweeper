#include "mech.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CriarTabuleiroUsr( tabuleiro_t * usr, jogada_t * jog )
{
	unsigned i, j;
	vec v;
	for( j = 0; j < get_m( *usr ); j++ )
	{
		for( i = 0; i < get_n( *usr ); i++)
		{
			v.x = i;
			v.y = j;
			set_usr( usr, v, '*' );
		}
	}
}

void ColocarBombas( tabuleiro_t * gabarito )
{
	unsigned x, y;

	srand( time( 0 ) );

	x = rand() % get_n( *gabarito );
	y = rand() % get_m( *gabarito );

	vec v;
	v.x = x;
	v.y = y;

	if( get_gabarito( *gabarito, v ) == 'B')
	{
		ColocarBombas( gabarito );
	}
	else
	{
		set_gabarito( gabarito, v, 'B' );
	}
}

/*
Na main
for(i = 0; i < get_q( gabarito ); i++)
		{
			ColocarBombas( &gabarito );
		}		
*/

void AvaliarVizinhos( tabuleiro_t * gabarito )
{
	int x, y, i, j, b;
	vec v;
	char a;
	for( y = 0; y < get_m( *gabarito ); y++)
	{
		for( x = 0; x < get_n( *gabarito ); x++)
		{
			v.x = x;
			v.y = y;
			b = 0;
			if( get_gabarito( *gabarito, v ) == 'B') //pula elementos com bombas
			{
				continue;
			}
			for( i = -1; i < 2; i++ )
			{
				for( j = -1; j < 2; j++ )
				{
					if( i==0 && j==0 ) //pula o próprio elemento
					{
						continue;
					}
					if( y + j < 0 || x + i < 0 || y + j >= get_m( *gabarito ) || x + i >= get_n( *gabarito ) ) //pula indevidos/inexistentes
					{
						continue;
					}
					v.x = x + i;
					v.y = y + j;
					if( get_gabarito( *gabarito, v ) == 'B')
					{
						b = b + 1;
					}
				}
			}
			v.x = x;
			v.y = y;
			a = (char) b + '0'; //transformar q em char
			set_gabarito( gabarito, v, a );
		}
	}
}

void Revela(tabuleiro_t * gabarito, tabuleiro_t * usr, vec v) //v = get_coord( jogada )
{
	int i = -1, j = -1;
	int x, y;
	x = (int) v.x;
	y = (int) v.y;
	if( get_gabarito( *gabarito, v ) != '0') //garante nulidade
	{
		return;
	}
	for( i = -1; i < 2; i++ )
	{
		for( j = -1; j < 2; j++ )
		{
			if( y + j < 0 || x + i < 0 || y + j >= get_m( *gabarito ) || x + i >= get_n( *gabarito ) ) // pula indevidos/inexistentes
			{
				continue;
			}
			v.x = x + i;
			v.y = y + j;
			if( get_usr( *usr, v ) ==  get_gabarito( *gabarito, v ) ) //pula já revelados
			{
				continue;
			}
			else
			{
				set_usr( usr, v, get_gabarito( *gabarito, v ) ); //revela realmente
				if( get_gabarito( *gabarito, v ) == '0' )
				{
					v.x = x + i;
					v.y = y + j;
					Revela( gabarito, usr, v);
				}
			}
		}
	}
}

/*
Na main
if( ( get_jogada( jogada ) == 'v' ) && ( get_gabarito( gabarito, get_coord( jogada ) ) == '0' ) )
{
	Revela( &gabarito, &usr, get_coord( jogada ) );
}
*/

int ExecutaJogada( tabuleiro_t gabarito, tabuleiro_t * usr, jogada_t * jogada )
{
	int i, j;
	if( get_jogada( *jogada ) == 'v' )
	{
		if( get_gabarito( gabarito, get_coord( *jogada ) ) == 'B' )//perdeu jogo
		{
			set_jogada( jogada, 'x');
			return 0;	
		}
		else( get_gabarito( gabarito, v ) != '0' )
		{
			set_usr( usr, get_coord( *jogada ), get_gabarito( gabarito, get_coord( *jogada ) ) ); 
			return 0;
		}
	}
	if( get_jogada( *jogada ) == 'm' )
	{
		set_usr( usr, get_coord( *jogada ),'M' );
		if( get_gabarito( gabarito, get_coord( *jogada ) ) == 'B' )
		{
			return 1;
		}
	}
	if( get_jogada( *jogada ) == 'd')
	{
		set_usr( usr, get_coord( *jogada ),'D' );
		return 0;
	}
	if( get_jogada( *jogada ) == 'r' )
	{
		return 0;
	}
	if( get_jogada( *jogada ) == 'x' )
	{
		return 0;
	}
}

/*
Retornar esse valor para um contador(?)
*/
