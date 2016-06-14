#include "dados.h"
#include "mech.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CriarTabuleiroUsr( tabuleiro_t * usr )
{
	int i, j; 
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

void CriarTabuleiroGabarito( tabuleiro_t * gabarito )
{
	int i, j; 
	vec v;
	for( j = 0; j < get_m( *gabarito ); j++ )
	{
		for( i = 0; i < get_n( *gabarito ); i++)
		{
			v.x = i;
			v.y = j;
			set_gabarito( gabarito, v, '*' );	
		}
	}
}

void ColocarBombas( tabuleiro_t * gabarito) //q = get_q( gabarito ) 
{
	unsigned x, y;
	
	srand(time(0));
	
	x = rand() % get_n( *gabarito );
	y = rand() % get_m( *gabarito );
	
	vec v;
	v.x = x;
	v.y = y;	

	if(get_gabarito( *gabarito, v ) == 'B')
	{
		ColocarBombas( gabarito );
	}
	else
	{
		set_gabarito( gabarito, v, 'B' );
	}
}

/*
colocar na main
for(i = 0; i < q; i++) //coloca bombas
		{
			ColocarBombas(info.m, info.n, info.data);
		}
*/

void AvaliarVizinhos( tabuleiro_t * gabarito ) //(int m, int n, char *data)
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
					if( y + j < 0 || x + i < 0 || y + j >= get_m( *gabarito ) || x + i >= get_n( *gabarito )) //pula indevidos/inexistentes
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

void Revela(tabuleiro_t * gabarito, tabuleiro_t * usr, vec v) //v = get_coord( jogada )	//( int m, int n, int x, int y, char* info, char * cort )
{
	int i = -1, j = -1;
	int x, y;	
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
			v.x = v.x + i;
			v.y = v.y + j;
			if( get_usr( *usr, v ) ==  get_gabarito( *gabarito, v ) ) //pula já revelados
			{
				continue;
			}
			else
			{
				set_usr( usr, v, get_gabarito( *gabarito, v ) )	;		
				if( get_gabarito( *gabarito, v ) == '0' )
				{
					v.x = v.x + i;
					v.y = v.y + j;
					Revela( gabarito, gabarito, v);
				}	
			}
		}	
	}
}

/*
colocar na main
if(jog.act == 'q' && tabuleiro de informações data.char[jog.y * info.m + jog.x] == '0')
	{
		Revela( info.m, info.n, jog.x, jog.y, info.data, cort.data );
	}
*/

int ExecutaJogada(tabuleiro_t dados, tabuleiro_t cortina, jogada_t) //(int m, int n, char *cort, char *info, char *act, int x, int y)
{
	int i, j;
	if(*act == 'q')
	{
		if(info[(y * m) + x] == 'B')
		{
			//perdeu jogo
			*act = 'x';
			return 0;	
		}
		if(info[(y * m) + x] != '0')
		{
			
			cort[(y * m) + x] = info[(y * m) + x];
			return 0;
		}
	}
	if(*act == 'f')
	{
		cort[y * m + x] = 'F';
		if(info[y * m + x] == 'B')
		{
			return 1;
		}
	}
	if(*act == 'd')
	{
		cort[y*m+x] = '?';
		return 0;
	}
	if(*act == 'z')
	{
		*act = 'r';
		return 0;
	}
	if(*act == 'x')
	{
		return 0;
	}
}

/*
Retornar esse valor para um contador(?)
*/