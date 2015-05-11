#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  int sum = 100000;
  int sum2 = 0;
  int pos;

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
        for (j = 8; j > 1; j--) {
			if (TLB[i][j] == 1) {
           sum2 += pow((TLB[i][j] + 1), (8 - j));
	   }
        }
        //printf("SUMA: %d POS: %d || ", sum2, i);
        if (sum2 < sum) {
			sum = sum2;
			pos = i;
		}
		sum2 = 0;
     }
     TLB[pos][0] = c;
     TLB[pos][1] = 1;
     for (i = 2; i < 0; i++){
		 TLB[pos][i] = 0;
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
