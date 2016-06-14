#ifndef DADOS_H_
#define DADOS_H_

//Protótipos

typedef struct {
unsigned m;
unsigned n;
unsigned q;
char* usr;
char* gabarito;
} tabuleiro_t;

typedef struct {
unsigned x;
unsigned y;
} vec;

typedef struct {
vec v;	//como escrever ? "v" ou "coord"
char opjogada
} jogada_t;

unsigned get_m(tabuleiro_t tab);
unsigned get_n(tabuleiro_t tab);
unsigned get_q(tabuleiro_t tab);
char get_usr(tabuleiro_t tab, vec v);
char get_gabarito(tabuleiro_t tab, vec v);
void set_m(tabuleiro_t*, unsigned m);
void set_n(tabuleiro_t*, unsigned n);
void set_q(tabuleiro_t*, unsigned q);
void set_usr(tabuleiro_t* tab, vec v,char usr);
void set_gabarito(tabuleiro_t* tab, vec v, char gabarito);
void inicializatab(tabuleiro_t* tab);
void destroitab(tabuleiro_t* tab);
char get_jogada(jogada_t tab);
void set_jogada(jogada_t* tab, char op);	//op = opção da jogada
vec get_coord (jogada_t jogada);
void set_coord (jogada_t jogada, unsigned x, unsigned y);

//Implementar

#endif

