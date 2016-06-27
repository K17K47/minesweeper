#include "ui.h"
#include "dados.h"
#include <stdio.h>
#include <stdio_ext.h>

void imprimirTabuleiro ( tabuleiro_t tab ) {

   int i , j ;
   vec v ;

	printf("     1"); // Da linha 11 a 24 do código, imprimo a primeira linha númerica (linha coordenadas) 

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

	for ( i = 1 ; i <= get_m(tab)*2 + 1 ; i++ )
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
			if( i <= 18)
			{
				printf(" %d |",i/2) ;
				for ( j = 1; j <= get_n(tab) ; j++ )
				{
					v.x = j - 1;
					v.y = i/2 - 1;
					printf (" %c |",get_usr(tab,v)) ;
         	}
        		printf(" %d\n", i/2);
			}
			else if( i <= 198 )
			{
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
}
   



void lerJogada ( jogada_t* jog , tabuleiro_t tab ) {

   unsigned x , y ;
   char op;

  
   char tmp ;

   do{
      printf("Digite a coordenada e a opção de jogada (Exemplo : 5 5 v) \n Caso queria reniciar digite( 1 1 r) \n Caso queria sair digite (1 1 s)\n");
      __fpurge(stdin);
      tmp = scanf("%u%u %c",&x,&y,&op);                                        
      if(tmp != 3 || !(x>0 && x<=get_n(tab)) || !(y>0 && y<=get_m(tab))){
         printf("Jogada inválida!\n");
         tmp = 0;
      }
      x--;
      y--;
   }while((tmp != 3) || !( op == 'v' || op == 'm' || op == 'd' || op == 'r' || op== 's'));

   set_coord ( jog , x,  y);
   set_jogada( jog , op);
 
 /*
   printf(" Digite a coordenada e a opção de jogada : " );
   scanf("%u%u",&x,&y);
   while( getchar() != '\n' );
   op=getchar();
   while( getchar() != '\n' );
   x = x - 1 ;
   y = y - 1 ;

   if(( !(x <= get_n(tab) ) || !(y <= get_m(tab) ) ) &&
      ( !(op == 'v') || !(op == 'm') || !( op == 'd' ))) {

      printf(" Erro na coordenada e na opção de jogada.Digite novamente : ") ;
      scanf("%u%u",&x,&y);
      
      while( getchar() != '\n' );
      op=getchar();
      while( getchar() != '\n' );

   }

   while ( !(x <= get_n(tab)) || !(y <= get_m(tab)) ){

      printf(" Erro na coordenada.Digite novamente : " );
      scanf("%u%u",&x,&y);
      while( getchar() != '\n' );

   }
   while ( !( op == 'v' || op == 'd' || op == 'm' ) ) {

      printf(" Erro na opção de jogo.Digite novamente : " );

      op=getchar();
      while( getchar() != '\n' );
   }

   set_coord ( jog , x,  y);
   set_jogada( jog , op);
*/}

int menu () {
   int op ;
   char tmp ;
   printf("\t\t\t Bem-Vindo ao Campo Minado \n\n Para efetuar uma jogada será necessario digitar \n uma coordenada ( x , y ) e uma opção de jogada ( Caracter ) \n \n" );
   printf("As opcoes de jogada são : 'v' para marcar a casa como vazia \n \t\t\t   'm' para marcar como minada \n \t\t\t   'd' para marcar como dúvida \n \n ") ;
   printf("Digite 1 ou 2 , numero da opção que voce gostaria de seguir : \n " ) ;
   printf("\t 1.Iniciar o jogo \n \t 2.Sair do jogo \n" ) ;
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
	      	printf("Para iniciar o jogo é preciso digitar o tamanho do tabuleiro ( linhas X colunas ) e o número de bombas (Exemplo : 10 10 2 ) :");
	      	//while((tmp=getchar())!=EOF && tmp!='\n');
		__fpurge(stdin);      	
		tmp = scanf("%u%u%u",&m,&n,&q);
		if(tmp != 3 || !(0 < q && q < m*n) || (m*n > 1000000) )//Sem restrição, números negativos seriam convertidos para unsigned grandes e haveria falha de segmentação
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

      printf("Erro de opção.Tente novamente :" ) ;
      opseguir( p , i) ;
     __fpurge(stdin);
   }
}

void fimDeJogo( int i , tabuleiro_t tab  ) {

   printf (" Fim de jogo \n Resultado: \n" ) ;
   if( i == get_q( tab ) ){
      printf(" Parabéns ! Você Venceu ! Marcou todas as bombas  \n\n " ) ;

   } else {
      printf(" Você perdeu ! Você marcou %d de %u bombas  \n\n", i , get_q(tab) ) ;

   }


}

