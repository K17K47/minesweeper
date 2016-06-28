#include "mech.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CriarTabuleiroUsr( tabuleiro_t * tab )
{
	unsigned i, j;
	vec v;
	for( j = 0; j < get_m( *tab ); j++ ) // Percorre todas as linhas.
	{
		for( i = 0; i < get_n( *tab ); i++) // Percorre todas as colunas de cada linha.
		{
			v.x = i;
			v.y = j;
			set_usr( tab, v, '*' ); // Atribui o '*' ao elemento de cada coordenada, criando a "cortina" vista pelo usu·rio.
		}
	}
}

void ColocarBombas( tabuleiro_t * tab )
{
	srand( (unsigned)time( NULL ) ); // Alimenta o gerador de n˙meros pseudo-aleatÛrios com o tempo.

	int i = 0;
	vec v;

	do
	{
		v.x = rand() % get_n( *tab );
		v.y = rand() % get_m( *tab ); // Gera coordenadas randÙmicas.

		while( get_gabarito( *tab, v ) == 'B') // Verifica se as coordenadas geradas j· n„o possuem bombas.
		{
			v.x = rand() % get_n( *tab );
			v.y = rand() % get_m( *tab ); // Gera novas coordenadas atÈ obter um elemnto sem bomba.
		}

		set_gabarito( tab, v, 'B' ); // Atribui bomba ao elemento escolhido.
		i = i + 1; // Incrementa contador de bombas.
	}while( i < get_q( *tab ) );
}

void AvaliarVizinhos( tabuleiro_t * tab )
{
	int x, y, i, j, b;
	vec v;
	char a;
	for( y = 0; y < get_m( *tab ); y++) // Percorre todas as linhas.
	{
		for( x = 0; x < get_n( *tab ); x++) // Percorre todas as colunas de cada linha.
		{
			v.x = x;
			v.y = y; // Seleciona coordenadas da linha e coluna presentes.
			b = 0;
			if( get_gabarito( *tab, v ) == 'B') // Pula elementos com bombas.
			{
				continue;
			}
			for( i = -1; i < 2; i++ ) // Percorre as duas colunas vizinhas e a prÛpria coluna do elemento
			{
				for( j = -1; j < 2; j++ ) // Percorre as duas linha vizinhas e a prÛpria linha do elemento
				{
					if( i==0 && j==0 ) // Pula o prÛprio elemento.
					{
						continue;
					}
					if( y + j < 0 || x + i < 0 || y + j >= get_m( *tab ) || x + i >= get_n( *tab ) ) // Pula elementos indevidos ou inexistentes.
					{
						continue;
					}
					v.x = x + i;
					v.y = y + j; // Seleciona elemento vizinho ao (x,y) - escolhido na linha de cÛdigo 55 e 56.
					if( get_gabarito( *tab, v ) == 'B')
					{
						b = b + 1; // Incrementa contador de bombas.
					}
				}
			}
			v.x = x;
			v.y = y; // Seleciona novamenteo elemento (x,y).
			a = (char) b + '0'; // Transformar o contador em char.
			set_gabarito( tab, v, a ); // Atribui ao elemento (x,y) o n˙mero (char) do contador.
		}
	}
}

void Revela( tabuleiro_t * tab, vec v ) // Na main, usa-se v = get_coord( jogada ).
{
	int i = -1, j = -1;
	int x, y;
	x = (int) v.x;
	y = (int) v.y;
	if( get_gabarito( *tab, v ) != '0') // Garante nulidade do elemento.
	{
		return;
	}
	for( i = -1; i < 2; i++ ) // Percorre as duas colunas vizinhas e a prÛpria coluna do elemento.
	{
		for( j = -1; j < 2; j++ ) // Percorre as duas linhas vizinhas e a prÛpria linha do elemento.
		{
			if( y + j < 0 || x + i < 0 || y + j >= get_m( *tab ) || x + i >= get_n( *tab ) ) // Pula elementos indevidos ou inexistentes.
			{
				continue;
			}
			v.x = x + i;
			v.y = y + j; // Seleciona elemento vizinho ao (x,y).
			if( get_usr( *tab, v ) ==  get_gabarito( *tab, v ) ) // Pula vizinhos j· revelados.
			{
				continue;
			}
			else
			{
				set_usr( tab, v, get_gabarito( *tab, v ) ); // Revela vizinhos.
				if( get_gabarito( *tab, v ) == '0' ) // Caso vizinho tambÈm seja nulo, recorre-se ao uso recursivo da funÁ„o Revela.
				{
					v.x = x + i;
					v.y = y + j;
					Revela( tab, v);
				}
			}
		}
	}
}

/*
Na main
if( ( get_jogada( jogada ) == 'v' ) && ( get_gabarito( gabarito, get_coord( jogada ) ) == '0' ) )
{
	Revela( &tab, get_coord( jogada ) );
}
*/

void ExecutaJogada( tabuleiro_t * tab, jogada_t * jogada, int * p )
{
	if( get_jogada( *jogada ) == 'v' ) // Caso usu·rio tenha marcado casa como vazia.
	{
		if( get_gabarito( *tab, get_coord( *jogada ) ) == 'B' ) // Se casa marcada vazia contiver bomba, opÁ„o de jogada  marcada para levar usu√°rio ao menu inicial. 
		{
			set_jogada( jogada, 'r');
			return;
		}
		else if( get_gabarito( *tab, get_coord( *jogada ) ) != '0' ) // Se casa marcada vazia contiver n√∫mero diferente de zero, revela o n√∫mero.
		{
			set_usr( tab, get_coord( *jogada ), get_gabarito( *tab, get_coord( *jogada ) ) );
			return;
		}
	}
	if( get_jogada( *jogada ) == 'm' ) // Caso usu√°rio tenha marcado casa como minada.
	{
		set_usr( tab, get_coord( *jogada ),'M' ); // Passa ao tabuleiro mostrado a marca√ß√£o.
		if( get_gabarito( *tab, get_coord( *jogada ) ) == 'B' ) // Se casa realmente contiver bomba, incrementa contador de bombas marcadas.
		{
			*p = *p + 1;
			return;
		}
	}
	if( get_jogada( *jogada ) == 'd') // Caso usu√°rio tenha marcado casa como duvidosa.
	{
		set_usr( tab, get_coord( *jogada ),'?' ); // Passa ao tabuleiro mostrado a marcaÁ„o.
		return;
	}
	if( get_jogada( *jogada ) == 'r' ) // Caso usu√°rio queira reiniciar o jogo.
	{
		return;
	}
	if( get_jogada( *jogada ) == 's' ) // Caso usu√°rio queira sair do jogo.
	{
		return;
	}
}
