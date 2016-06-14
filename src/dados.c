#include "dados.h"

unsigned get_m(tabuleiro_t tab)
{
	return tab.m;
}

unsigned get_n(tabuleiro_t tab)
{
	return tab.n;
}

unsigned get_q(tabuleiro_t tab)
{
	return tab.q;
}

char get_usr(tabuleiro_t tab, vec v)
{
	return tab.usr[tab.m*v.x + v.y];
}

char get_gabarito(tabuleiro_t tab, vec v)
{
	return tab.gabarito[tab.m*v.x + v.y];
}

void set_m(tabuleiro_t* tab, unsigned m)
{
	tab->m=m;
}

void set_n(tabuleiro_t* tab, unsigned n)
{
	tab->n=n;
}

void set_q(tabuleiro_t* tab, unsigned q)
{
	tab->q=q;
}

void set_usr(tabuleiro_t* tab, vec v,char usr)
{
	tab->usr[tab->m*v.x + v.y]=usr;
}

void set_gabarito(tabuleiro_t* tab, vec v, char gabarito)
{
	tab->gabarito[tab->m*v.x + v.y]=gabarito;
}

void inicializa_tab(tabuleiro_t* tab)
{
	tab->usr = malloc (m*n);
	tab->gabarito = malloc (m*n);
}
void destroi_tab(tabuleiro_t* tab)
{
	free(tab->user);
	free(tab->gabarito);
}

char get_jogada(jogada_t jogada)
{
	return jogada.opjogada;
}

void set_jogada(jogada_t* jogada, char op);	//op = opção
{
	jogada->opjogada=op;
}

vec get_coord (jogada_t jogada)
{
	return jogada.vec;
}

void set_coord (jogada_t jogada, unsigned x, unsigned y)
{
	jogada->v->x=x;
	jogada->v->y=y;
}





















