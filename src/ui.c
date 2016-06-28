#include "ui.h"
#include "dados.h"
#include <stdio.h>
#include <stdio_ext.h>

void imprimirTabuleiro ( tabuleiro_t tab ) { // está função escrita basedo na construção do próprio tabuleiro. Por isso alguns printf's imprimem alguns espaços se nao o tabuleiro ficaria desalinhado.

   int i , j ;
   vec v ;

	printf("     1"); // Da linha 11 a 24 do código, imprimo a primeira linha númerica (linha coordenadas).

   for(j = 2 ; j <= get_n(tab) ; j++)
	{
      if( j < 10 )
      {
			printf("   %d",j);
		}
		if( j > 9 )
		{
			printf("  %d",j);
		}
	}
	printf("\n");

	for ( i = 1 ; i <= get_m(tab)*2 + 1 ; i++ )  // da linhas 26 a 36, imprimo as linhas impares como +---+ .
   {
		if ( i%2 == 1 )
      {
			printf("   +");
			for ( j = 1; j <= get_n(tab) ; j++)
         {
				printf("---+");
         }
			printf("\n");
		}
      else {
			if( i <= 18)                           // da linhas 37 ate 62 , imprimo as barras | , coluna coordenada e o carater dentro das casas.
			{
				printf(" %d |",i/2) ;
				for ( j = 1; j <= get_n(tab) ; j++ )
				{
					v.x = j - 1;
					v.y = i/2 - 1;
					printf (" %c |",get_usr(tab,v)) ;
         	}
        		printf(" %d\n", i/2);                   // o uso dos if's é por causa de que numero maior que 9 ou 99 ocupara mais espaço deixando o tabuleiro desalinhado.
			}
			else if( i <= 198 )
			{                                                 // me preocupei em imprimir o tabuleiro  no máximo 100 x 100 , pois maior que isso nao ficaria comfortável para o usuario jogar no terminal.
				printf("%d |",i/2) ;
				for ( j = 1; j <= get_n(tab) ; j++ )
				{
					v.x = j - 1;
					v.y = i/2 - 1;
					printf (" %c |",get_usr(tab,v));
         	}
         	printf(" %d\n", i/2);
			}
		}
	}

	printf("     1");
                                                      // imprimo a última linhas numérica ( linha coordenada ).
   for(j = 2 ; j <= get_n(tab) ; j++)
	{
      if( j < 10 )                                   // uso do if  é pelo mesmo motivo do anterior.
      {
			printf("   %d",j);
		}
		if( j > 9 )
		{
			printf("  %d",j);
		}
	}
	printf("\n");   // está função foi escrita basedo na construção do próprio tabuleiro.Por isso foi necessário ter alguns printf's que imprimem alguns espaços , pois se não o tabuleiro ficaria desalinhado.
}


void lerJogada ( jogada_t* jog , tabuleiro_t tab ) {

   unsigned x , y ;
   char op;
   char tmp ;

   do{
      printf("Digite uma coordenada e um opção de jogada (Exemplo : 5 5 v) \nCaso queria reniciar, digite (1 1 r) \nCaso queria sair, digite (1 1 s)\n");
      __fpurge(stdin);     // limpando o buffer.
      tmp = scanf("%u%u %c",&x,&y,&op);
      if(tmp != 3 || !(x>0 && x<=get_n(tab)) || !(y>0 && y<=get_m(tab))){     // verificando se a leitura do scanf foi bem-sucedida e se a jogada é válida( se a coordenada está de fato no tabuleiro.
         printf("Jogada inválida!\n");
         tmp = 0;
      }
      x--;
      y--;
   }while((tmp != 3) || !( op == 'v' || op == 'm' || op == 'd' || op == 'r' || op== 's'));  // No caso 'r' é para reniciar e 's' é para sair do jogo. 

   set_coord ( jog , x,  y);
   set_jogada( jog , op);

}

int menu () {        // função menu.
   int op ;
   char tmp ;
   printf("\t\t\t Bem-Vindo ao Campo Minado \n\n Para efetuar uma jogada será necessario digitar \n uma coordenada ( Número da Coluna , Número da Linha ) e uma opção de jogada ( Caracter ) \n \n" );
   printf(" As opcões de jogada são : 'v' para marcar a casa como vazia \n \t\t\t   'm' para marcar como minada \n \t\t\t   'd' para marcar como dúvida \n \n ") ;
   printf("Digite 1 ou 2 , número da opção que você gostaria de seguir : \n " ) ;
   printf("\t1.Iniciar o jogo \n \t2.Sair do jogo \n" ) ;
   tmp = scanf("%d", &op) ;
   __fpurge(stdin);

   return op ;
}

void opseguir ( tabuleiro_t* p , int *i) {
   unsigned m , n , q;
   int op;
   op = menu();
   char tmp = 0;

   if( op == 1 ){

	   do{
	      printf("Para iniciar o jogo é preciso digitar o tamanho do tabuleiro ( Colunas X Linhas ) e o número de bombas (Exemplo : 10 10 2) :");
		   __fpurge(stdin);
		   tmp = scanf("%u%u%u",&m,&n,&q);
		   if(tmp != 3 || !(0 < q && q < m*n) || (m > 100) || (n > 100) )// Condição para montar o jogo / Sem restrição, números negativos seriam convertidos para unsigned grandes e haveria falha de segmentação.
		   {
	         	   printf("Dimensão inválida !\n");
	      	      tmp = 0;
		   }
	   }while((tmp != 3));

      set_m(p,m);
      set_n(p,n);
      set_q(p,q);
      *i = 1;

      return;
   }else if(op == 2){
      *i = 0;

      return;
   }else{

      printf("Erro de opção.Tente novamente :" );
      opseguir( p , i);      // chamando novamente a função caso o usuário nao digite 1 ou 2 .
      __fpurge(stdin);
   }
}

void fimDeJogo( int i , tabuleiro_t tab  ) { // está função apresenta ao usuário o resultado.

   printf (" Fim de jogo \n Resultado: \n" );
   if( i == get_q( tab ) ){
      printf(" Parabéns ! Você Venceu ! Marcou todas as bombas  \n\n " ) ;

   } else {
      printf(" Você perdeu ! Você marcou %d de %u bombas  \n\n", i , get_q(tab) ) ; // numero de bombas marcadas.

   }

}
