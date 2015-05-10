#include <stdio.h>
#include <stdlib.h>
#include <math.c>

int TLB[8][9]; //Define el TLB

void muestraTLB () {
  int i,j;

  printf("TLB\n");
  for (i=0; i<8; i++) {
       printf("|%3u|", TLB[i][0]);
       for (j=1; j<9; j++) {
            printf("|%d|", TLB[i][j]);         
       }
       printf("\n");
  }
}

void cargaTLB() {
  int i,j;

  for (i=0; i<8; i++) {
       TLB[i][0] = i+1;
       for (j=1; j<9; j++) {
            TLB[i][j] = 0;         
       }
  }
}

void referenciaTLB(int c) {
  int i,j;
  int FP = 0;
  int cont = 0;
  int cont2 = 100000;

  for (j=7; j>0; j--) {
       for (i=0; i<8; i++) {
            TLB[i][j+1] = TLB[i][j];         
       }
  }

  for (i=0; i<8; i++) {
       TLB[i][1] = 0;
       if (TLB[i][0] == c) {
           TLB[i][1] = 1;
           FP = 1;
       }
  }

  //Hay un Fallo de página, se debe sustituir una página
  if (FP == 0) {
     for (i = 0; i < 8; i++) {
        for (j = 7; j > 1; j--) {
           cont += pow(TLB[i][j], 7 - i);
           cont2 += pow(TLB[i][j], 7 - i);
        }
     }
  }
}


int main(void){
    FILE *fp;
    int c;
    int i, j;

    if ((fp = fopen("Paginas.txt", "r")) != 0){
       //Carga el TLB inicial
       cargaTLB();

       muestraTLB();            

       while((fscanf(fp, "%d", &c)) != EOF){
          printf("\n%d\n",c);
          //Referenciar la página
          //Correr los bits
          referenciaTLB(c);
          muestraTLB ();
       }

       fclose(fp);
   }
   return(0);
}
