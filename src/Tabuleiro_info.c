typedef struct
{
	int m;
	int n;
	char *data;
} tab_t;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criar_tab( int m, int n, char *data )
{
	int i, j; 
	
	for( j = 0; j < n; j++)
	{
		for( i = 0; i < m; i++)
		{
			data[j * m + i] = '*';
		}
	}
}

void imprime_tab ( int m, int n, char *data)
{
	int i, j;
	for( j = 0; j < n; j++)
	{
		for( i = 0; i < m; i++)
		{
			printf("%c\t", data[j * m + i ]);
		}
		printf("\n");
	}
}

void p_bomb(int m, int n, char *data) 
{
	int x, y;
	x = rand() % m;
	y = rand() % n;
	
	if(data[y * m + x] == 'B')
	{
		p_bomb(m, n, data);
	}
	else
	{
		data[y * m + x] = 'B';
	}
}

void avalia_viz(int m, int n, char *data)
{
	int x, y, i, j, q;
	
	for( y = 0; y < n; y++)
	{
		for( x = 0; x < m; x++)
		{
			q = 0;
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
					if( y + j < 0 || x + i < 0 || y + j >= n || x + i >= m) // pula indevidos
					{
						continue;
					}
					if(data[( y + j ) * m + x + i] == 'B')
					{
						q = q + 1;
					}
				}	
			}
			data[y * m + x] = (char) q + '0'; //transformar q em char
		}
	}
}

int main()
{
	
	tab_t info;
	scanf("%i", &info.m);
	scanf("%i", &info.n);
	info.data = (char *) malloc (info.m * info.n * sizeof(char));
	criar_tab ( info.m, info.n, info.data); //cria tabuleiro

	int q, i;
	scanf("%i", &q);
	printf("\n");
	srand(time(0));
	for(i = 0; i < q; i++) //coloca bombas
	{
		p_bomb(info.m, info.n, info.data);
	}
	
	avalia_viz(info.m, info.n, info.data);	
		
	imprime_tab (info.m, info.n, info.data);
	
	return 0;
}
