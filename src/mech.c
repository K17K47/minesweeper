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
			set_usr( tab, v, '*' ); // Atribui o '*' ao elemento de cada coordenada, criando a "cortina" vista pelo usu�rio.
		}
	}
}

void ColocarBombas( tabuleiro_t * tab )
{
	srand( (unsigned)time( NULL ) ); // Alimenta o gerador de n�meros pseudo-aleat�rios com o tempo.

	int i = 0;
	vec v;

	do
	{
		v.x = rand() % get_n( *tab );
		v.y = rand() % get_m( *tab ); // Gera coordenadas rand�micas.

		while( get_gabarito( *tab, v ) == 'B') // Verifica se as coordenadas geradas j� n�o possuem bombas.
		{
			v.x = rand() % get_n( *tab );
			v.y = rand() % get_m( *tab ); // Gera novas coordenadas at� obter um elemnto sem bomba.
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
			for( i = -1; i < 2; i++ ) // Percorre as duas colunas vizinhas e a pr�pria coluna do elemento
			{
				for( j = -1; j < 2; j++ ) // Percorre as duas linha vizinhas e a pr�pria linha do elemento
				{
					if( i==0 && j==0 ) // Pula o pr�prio elemento.
					{
						continue;
					}
					if( y + j < 0 || x + i < 0 || y + j >= get_m( *tab ) || x + i >= get_n( *tab ) ) // Pula indevidos.
					{
						continue;
					}
					v.x = x + i;
					v.y = y + j; // Seleciona elemento vizinho ao (x,y) - escolhido na linha de c�digo 55 e 56.
					if( get_gabarito( *tab, v ) == 'B')
					{
						b = b + 1; // Incrementa contador de bombas.
					}
				}
			}
			v.x = x;
			v.y = y; // Seleciona novamenteo elemento (x,y).
			a = (char) b + '0'; // Transformar o contador em char.
			set_gabarito( tab, v, a ); // Atribui ao elemento (x,y) o n�mero (char) do contador.
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
	for( i = -1; i < 2; i++ ) // Percorre as duas colunas vizinhas e a pr�pria coluna do elemento.
	{
		for( j = -1; j < 2; j++ ) // Percorre as duas linhas vizinhas e a pr�pria linha do elemento.
		{
			if( y + j < 0 || x + i < 0 || y + j >= get_m( *tab ) || x + i >= get_n( *tab ) ) // Pula indevidos.
			{
				continue;
			}
			v.x = x + i;
			v.y = y + j; // Seleciona elemento vizinho ao (x,y).
			if( ( get_usr( *tab, v ) ==  get_gabarito( *tab, v ) ) || ( get_usr( *tab, v ) == ' ') ) // Pula j� revelados.
			{
				continue;
			}
			else
			{
				set_usr( tab, v, get_gabarito( *tab, v ) ); // Revela vizinhos.
				if( get_gabarito( *tab, v ) == '0' )
				{
					set_usr( tab, v, ' ' ); // Atribui espa�o vazio aos nulos.
					Revela( tab, v); // Uso recursivo da fun��o Revela no vizinho nulo.
				}
			}
		}
	}
}

void ExecutaJogada( tabuleiro_t * tab, jogada_t * jogada, int * p )
{
	if( get_jogada( *jogada ) == 'v' ) // Caso usu�rio tenha marcado casa como vazia.
	{
		if( get_gabarito( *tab, get_coord( *jogada ) ) == 'B' ) 
		{
			set_jogada( jogada, 'r'); // Leva usu�rio ao menu inicial se cair em uma bomba. 
			return;
		}
		else if( get_gabarito( *tab, get_coord( *jogada ) ) != '0' ) // Revela o n�mero diferente de zero.
		{
			set_usr( tab, get_coord( *jogada ), get_gabarito( *tab, get_coord( *jogada ) ) );
			return;
		}
	}

	if( get_jogada( *jogada ) == 'm' ) // Caso usu�rio tenha marcado casa como minada.
	{
		if( get_usr( *tab, get_coord( *jogada ) ) == 'M' ) // Caso usu�rio j� tenha marcado casa como minada e queira desmarc�-la.
		{
			set_usr( tab, get_coord( *jogada ),'*' );	
		}
		else if( get_usr( *tab, get_coord( *jogada ) ) == get_gabarito( *tab, get_coord( *jogada ) ) )
		{
			return;
		}	
		else
		{
			set_usr( tab, get_coord( *jogada ), 'M' ); // Passa ao tabuleiro mostrado a marca��o.
			if( get_gabarito( *tab, get_coord( *jogada ) ) == 'B' ) // Incrementa contador de bombas marcadas.
			{
				*p = *p + 1;
				return;
			}		
		}	
	}
	
	if( get_jogada( *jogada ) == 'd') // Caso usu�rio tenha marcado casa como duvidosa.
	{
		if( get_usr( *tab, get_coord( *jogada ) ) == '?' ) // Caso usu�rio j� tenha marcado casa como duvidosa e queira desmarc�-la.
		{
			set_usr( tab, get_coord( *jogada ),'*' );	
		}	
		else if( get_usr( *tab, get_coord( *jogada ) ) == get_gabarito( *tab, get_coord( *jogada ) ) )
		{
			return;
		}		
		else
		{			
			set_usr( tab, get_coord( *jogada ),'?' ); // Passa ao tabuleiro mostrado a marca��o.
			return;
		}
	}

	if( get_jogada( *jogada ) == 'r' ) // Caso usu�rio queira reiniciar o jogo.
	{
		return;
	}

	if( get_jogada( *jogada ) == 's' ) // Caso usu�rio queira sair do jogo.
	{
		return;
	}
}
