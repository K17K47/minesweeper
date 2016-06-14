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

