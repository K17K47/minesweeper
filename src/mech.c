#include "dados.h"
#include "mech.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CriarTabuleiroUsr( tabuleiro_t usr )
{
	int i, j; 
	for( j = 0; j < get_m( gabarito ); j++ )
	{
		for( i = 0; i < get_n( gabarito ); i++)
		{
			set_usr( &usr, j , i, '*' );	
		}
	}
}

void CriarTabuleiroGabarito( tabuleiro_t gabarito )
{
	int i, j; 
	for( j = 0; j < get_m( gabarito ); j++ )
	{
		for( i = 0; i < get_n( gabarito ); i++)
		{
			set_gabarito( &gabarito, j , i, '*' );	
		}
	}
}

void ColocarBombas( tabuleiro_t gabarito, q ) //q = get_q(gabarito) 
{
	int x, y;
	srand(time(0));
	
	x = rand() % get_n( gabarito );
	y = rand() % get_m( gabarito );
	
	if(data[y * m + x] == 'B')
	{
		ColocarBombas(m, n, data);
	}
	else
	{
		data[y * m + x] = 'B';
	}
}

/*
colocar na main
for(i = 0; i < q; i++) //coloca bombas
		{
			ColocarBombas(info.m, info.n, info.data);
		}
*/

void AvaliarVizinhos(tabuleiro_t) //(int m, int n, char *data)
{
	int x, y, i, j, b;
	for( y = 0; y < n; y++)
	{
		for( x = 0; x < m; x++)
		{
			b = 0;
			if(data[y * m + x] == 'B') //pula elementos com bombas
			{
				continue;
			}
			for(i = -1; i < 2; i++)
			{
				for(j= -1; j < 2; j++)
				{
					if(i==0 && j==0) //pula o próprio elemento
					{
						continue;
					}
					if( y + j < 0 || x + i < 0 || y + j >= n || x + i >= m) // pula indevidos/inexistentes
					{
						continue;
					}
					if(data[( y + j ) * m + x + i] == 'B')
					{
						b = b + 1;
					}
				}	
			}
			data[y * m + x] = (char) q + '0'; //transformar q em char
		}
	}
}

void Revela(tabuleiro_t dados, tabuleiro_t cortina, jogada_t) //( int m, int n, int x, int y, char* info, char * cort )
{
	int i = -1, j = -1;
	if(info[y * m + x] != '0')//garante nulidade
	{
		return;
	}
	for(i = -1; i < 2; i++)
	{
		for(j = -1; j < 2; j++)
		{
			if( y + j < 0 || x + i < 0 || y + j >= n || x + i >= m) // pula indevidos/inexistentes
			{
				continue;
			}
			if(cort[( y + j ) * m + x + i] == info[( y + j ) * m + x + i]) //pula já revelados
			{
				continue;
			}
			else
			{
				cort[( y + j ) * m + x + i] = info[( y + j ) * m + x + i];
				if(info[( y + j ) * m + x + i] == '0')
				{
					revela( m, n, x + i, y + j, info, cort);
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