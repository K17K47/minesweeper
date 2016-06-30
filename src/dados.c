#include "dados.h"
#include <stdlib.h>

unsigned get_m(tabuleiro_t tab) // acessa uma struct tabuleiro_t e retorna o valor de m (numero de linhas do tabuleiro)
{
	return tab.m;
}

unsigned get_n(tabuleiro_t tab) // acessa uma struct tabuleiro_t e retorna o valor de n (numero de colunas do tabuleiro)
{
	return tab.n;
}

unsigned get_q(tabuleiro_t tab) // acessa uma struct tabuleiro_t e retorna o valor de q (numero de minas que contera o tabuleiro)
{
	return tab.q;
}

char get_usr(tabuleiro_t tab, vec v) // acessa uma struct tabuleiro (vista pelo usuario, ou seja, o tabuleiro fechado) e retorna a informacao contida em uma casa em especifico, sendo ela denotada pelo vec v, que contem as coordenadas da casa do tabuleiro
{
	return tab.usr[tab.m*v.x + v.y];
}

char get_gabarito(tabuleiro_t tab, vec v) // acessa uma struct tabuleiro (dessa vez, o tabuleiro aberto, armazenado na memoria do programa) e retorna a informacao contida em uma casa em especifico, por exemplo uma bomba ou uma casa vazia com n bombas a sua volta, sendo ela denotada pelo vec v, que contem as coordenadas da casa do tabuleiro
{
	return tab.gabarito[tab.m*v.x + v.y];
}

void set_m(tabuleiro_t* tab, unsigned m) // determina um valor para m, na struct tabuleiro_t
{
	tab->m=m;
}

void set_n(tabuleiro_t* tab, unsigned n) // determina um valor para n, na struct tabuleiro_t
{
	tab->n=n;
}

void set_q(tabuleiro_t* tab, unsigned q) // determina um valor para q, na struct tabuleiro_t
{
	tab->q=q;
}

void set_usr(tabuleiro_t* tab, vec v,char usr) // determina a informacao que estara contida em uma das casas do tabuleiro que pode ser visto pelo usuario, por exemplo, um marcador de bomba
{
	tab->usr[tab->m*v.x + v.y]=usr;
}

void set_gabarito(tabuleiro_t* tab, vec v, char gabarito) // determina a informacao que estara contida em uma das casas do tabuleiro gabarito, aquele armazenado na memoria do programa e que contem as informacoes sobre as bombas, por exemplo
{
	tab->gabarito[tab->m*v.x + v.y]=gabarito;
}

void inicializa_tab(tabuleiro_t* tab) // aloca memoria para ambos os tabuleiros
{
	tab->usr = malloc (tab->m*tab->n);
	tab->gabarito = malloc (tab->m*tab->n);
}
void destroi_tab(tabuleiro_t* tab) // libera a memoria usada pelos tabuleiros
{
	free(tab->usr);
	free(tab->gabarito);
}

char get_jogada(jogada_t jogada) // apartir de uma struct jogata_t, retorna a opcao da jogada do usuario
{
	return jogada.opjogada;
}

void set_jogada(jogada_t* jogada, char op)	// determina a jogada a ser feita, onde op e a opcao de jogada
{
	jogada->opjogada=op;
}

vec get_coord (jogada_t jogada) // acessa a struct jogada_t e retorna o vet v correspondente, que contem as coordenadas da jogada
{
	return jogada.v;
}

void set_coord (jogada_t* jogada, unsigned x, unsigned y) // determina (set) a coordenada de uma jogada
{
	jogada->v.x=x;
	jogada->v.y=y;
}





















