#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int cabecalho();

void InicializaTabuleiro(int **tab){ // Primeiro tabuleiro a ser mostrado, impresso como 2x2
  int num=0, i=0;
  cabecalho ();
  while(i<3){
    printf("     %d", i); 
    i++;
  }
  printf("\n\n    |----|----|----|\n");

  for (int i=0; i<3; i++){   
    for (int j=0; j<3; j++){
      
      if (j==0)
        printf("%d   |", num); 
      printf("    |");      
    }
    num++;
    printf("\n");
    int cont = 0;
    if (i!=3){
      while (cont<3){
        if (cont==1 || cont==2)
          printf("----|");
        else if (cont==0)
          printf("    |----|");
        cont++;
      }
    }
    printf("\n");
  }
}

void AtualizaTabuleiro(int **tab, int p, int l, int c, int minL, int maxL, int minC, int maxC){//Atualiza a cada jogada realizada pelo jogador, sempre atualizando a peça inserida na jogada
  tab[l][c]= p;
  int num=0, i=0, aux;
  cabecalho ();  
  while(i<=maxC){
    if (i==0)
      printf("\t  %d", i); 
    else
      printf("    %d", i);     
    i++;
  }
  printf("\n\n    ");
  aux=maxC;

  while(aux>=0){
    if (aux==maxC)
      printf("|----|");
    else
      printf("----|");
    aux--;
  }
  printf("\n");

  while (l==minL){ // Expansao do tabuleiro caso o minimo de linhas seja atingido
    for (int i=maxL; i>=0; i--){
      for(int j=maxC; j>=0; j--){
        if (tab[i][j]!=' '){
          tab[i+1][j] = tab[i][j];
          tab[i][j]=' ';
        }
      }
    }
    minL++;
  }

  while (c==minC){ // Expansao do tabuleiro caso o minimo de colunas seja atingido
    for (int j=maxC; j>=0; j--){
      for(int i=maxL; i>=0; i--){
        if (tab[i][j]!=' '){
          tab[i][j+1] = tab[i][j];
          tab[i][j]=' ';
        }
      }
    }  
    minC++;    
  }

  for (l = 0; l <= maxL; l++){
    for (c = 0 ; c <= maxC; c++){
      if (c==0)
        printf("%d   |", num);
      if (tab[l][c]!=' '){
        int aux, contc = 0, cor;
        aux = tab[l][c];
        while (aux < 122){
          aux += 16;
        }
        contc = 0;
        while (aux != (122 + contc)){
          contc++;
        }
        cor = 41 + contc;
        printf (" \e[%dm%x\e[0m ", cor, tab[l][c]);
      }else
       printf("    ");
      if (c !=  maxC+1)
        printf ("|");      
    }
    num++;
    printf("\n");
    int cont = 0;
    if (i!=maxC){
      while(cont<maxC+1){
        if(cont==maxC+1|| cont!=0)
          printf("----|");
        if (cont==0)
          printf("    |----|");
        cont++;
      }
    }
    printf("\n");
  }
  printf("\n\n");
} 
