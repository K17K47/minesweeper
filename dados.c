#include "dados.h"
#include <stdlib.h>

unsigned get_m(tabuleiro_t tab) // (linhas 4 a 7) - a funcão acessa uma struct tabuleiro_t e retorna o valor de m (número de linhas do tabuleiro)
{
	return tab.m;
}

unsigned get_n(tabuleiro_t tab) // (linhas 9 a 12) - a funcão acessa uma struct tabuleiro_t e retorna o valor de n (número de colunas do tabuleiro)
{
	return tab.n;
}

unsigned get_q(tabuleiro_t tab) // (linhas 14 a 17) - a funcão acessa uma struct tabuleiro_t e retorna o valor de q (número de minas que conterá o tabuleiro)
{
	return tab.q;
}

char get_usr(tabuleiro_t tab, vec v) // (linhas 19 a 22) - a funcão acessa uma struct tabuleiro (vista pelo usuário, ou seja, o tabuleiro fechado) e retorna a informacão contida em uma casa em específico, sendo ela denotada pelo vec v, que contém as coordenadas da casa do tabuleiro
{
	return tab.usr[tab.m*v.x + v.y];
}

char get_gabarito(tabuleiro_t tab, vec v) // (linhas 24 a 27) - a funcão acessa uma struct tabuleiro (dessa vez, o tabuleiro aberto, armazenado na memória do programa) e retorna a informacão contida em uma casa em específico, por exemplo uma bomba ou uma casa vazia com n bombas a sua volta, sendo ela denotada pelo vec v, que contém as coordenadas da casa do tabuleiro
{
	return tab.gabarito[tab.m*v.x + v.y];
}

void set_m(tabuleiro_t* tab, unsigned m) // (linhas 29 a 32) - uma funcào que determina um valor para m, na struct tabuleiro_t
{
	tab->m=m;
}

void set_n(tabuleiro_t* tab, unsigned n) // (linhas 34 a 37) - uma funcào que determina um valor para n, na struct tabuleiro_t
{
	tab->n=n;
}

void set_q(tabuleiro_t* tab, unsigned q) // (linhas 39 a 42) - uma funcào que determina um valor para q, na struct tabuleiro_t
{
	tab->q=q;
}

void set_usr(tabuleiro_t* tab, vec v,char usr) // (linhas 44 a 47) - uma funcão para determinar a informacão que estará contida em uma das casas do tabuleiro que pode ser visto pelo usuário, por exemplo, um marcador de bomba
{
	tab->usr[tab->m*v.x + v.y]=usr;
}

void set_gabarito(tabuleiro_t* tab, vec v, char gabarito) // (linhas 49 a 52) - uma funcão para determinar a informacão que estará contida em uma das casas do tabuleiro gabarito, aquele armazenado na memória do programa e que contém as informacões sobre as bombas, por exemplo
{
	tab->gabarito[tab->m*v.x + v.y]=gabarito;
}

void inicializa_tab(tabuleiro_t* tab) // (linhas 54 a 58) - uma funcão que aloca memória para ambos os tabuleiros
{
	tab->usr = malloc (tab->m*tab->n);
	tab->gabarito = malloc (tab->m*tab->n);
}
void destroi_tab(tabuleiro_t* tab) // (linhas 59 a 63) - uma funcão que libera a memória usada pelos tabuleiros
{
	free(tab->usr);
	free(tab->gabarito);
}

char get_jogada(jogada_t jogada) // (linhas 65 a 68) - uma funcão que, apartir de uma struct jogata_t, retorna a opcão da jogada do usuário
{
	return jogada.opjogada;
}

void set_jogada(jogada_t* jogada, char op)	// (linhas 70 a 73) - uma funcão que determina a jogada a ser feita, onde op é a opcão de jogada
{
	jogada->opjogada=op;
}

vec get_coord (jogada_t jogada) // (linhas 75 a 78) - uma funcão que acessa a struct jogada_t e retorna o vet v correspondente, que contém as coordenadas da jogada
{
	return jogada.v;
}

void set_coord (jogada_t* jogada, unsigned x, unsigned y) // (linhas 80 a 84) - uma funcão que determina (set) a coordenada de uma jogada
{
	jogada->v.x=x;
	jogada->v.y=y;
}





















