#include "ui.h"
#include "dados.h"

void imprimirTabuleiro(tabuleiro_t tab){
   int i, j;
   vec v;

   for( j = 0; j < get_n(tab)+ 1; j++) {
      if(j) printf("\t%i",j);
      v.x=j;
      for( i = 0; i < get_m(tab); i++){
         v.y=i;
         if(j) printf("     \t/%c/", get_usr(tab,v)  );
         if(!j) printf("\t\t%i",i+1);
      }
      printf("\n");
   }
}



void Lerjogada ( jogada_t*jog , tabuleiro_t tab ) {

 unsigned x , y ;
 char op ;

 printf(" Digite a coordenada e a opcao de jogada " );
 scanf("%u%u",&x,&y);
 op=getchar();
   while( getchar() != ’\n’ );
 

 if( ( !(x <= get_n(tab) || !(y <= get_m(tab) ) && ( !(op == v) || !(op == m) || !( op == d )  ) ) {

    printf(" Erro na coordenada e na opcao de jogada. Digite novamente ") ;
    scanf("%u%u",&x,&y);
    op=getchar();
     while( getchar() != ’\n’ );

}
  while ( !(x <= get_n(tab) || !(y <= get_m(tab)  ){

      printf(" Erro na coordenada . digite novamente " );
      scanf("%u%u",&x,&y);
        while( getchar() != ’\n’ );
     
}
  while ( !(op == v) || !(op == m) || !( op == d ) ) {
       
      printf(" Erro na opao de jogo . digite novamente " );
      
      op=getchar();
        while( getchar() != ’\n’ );
}

  set_coord ( jog , x,  y);
  set_jogada( jog , op);
      
   
}
