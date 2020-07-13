#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "menu.h"
#include "tabuleiro.h"
#include "verifica.h"
#include "pontuacao.h"

//typedef struct Jogador{
  //char nome[100];
//} dados_Jogador;

int main(void) {
  int **tab; 

  tab = (int **) malloc(100 * sizeof(int*));
  if (tab == NULL){
    printf("Memoria insuficiente\n");
    exit(1);
  }

  //printf("\33[H\33[2J"); //Para limpar a tela

  for (int i = 0 ; i < 100 ; i++){
    tab[i] = (int *) malloc(100 * sizeof(int)); 
    if (tab[i] == NULL){
      printf("Memoria insuficiente\n");
      exit(1);
    }
    for (int j = 0 ; j < 100 ; j++)
      tab[i][j] = ' ';
  }

  int mnl = 2, mxl = 0, mnc = 2, mxc = 0;
  int qtdeJog, cheat;
  
  int pecas[107], cont = 0, peca = 42, pe, cor, aux, contc = 0, jogp[qtdeJog][6];
  
  for (int p = 0; p <= 107; p++){
    pecas[p] = peca;
    if ((p+1) % 3 == 0){
      peca++;
      cont++;
    }
    if (cont == 6){
      cont = 0;
      peca +=10;
    }
  }

  cheat = menu();
  cabecalho();
  int jogador=1, l, c, p, minL=0, minC=0, maxL=2, maxC=2, x=1, cont1=0, auxL, auxC, aux1L, aux1C, res, contfim=108, contfimj = 0;

  
  printf("\tQual a quantidade de jogadores: ");
  while (scanf("%d", &qtdeJog) == 0 || qtdeJog > 18){
    printf("Comando invalido. Digite novamente: ");
    setbuf(stdin, NULL);
  }

  int pontos[qtdeJog];
  for (int i=0; i<qtdeJog; i++)
    pontos[i]=0;
  
  /*dados_Jogador dj;
  getchar();
  for (int i=0; i<qtdeJog; i++){
    printf("Nome do jogador %d: ", i+1);
    fgets(dj.nome, 100, stdin);
  }*/

 // printf("\33[H\33[2J"); //Para limpar a tela
  
  InicializaTabuleiro(tab);
  putchar('\n');

  for(int i = 0; i < qtdeJog; i++){
    for(int j = 0; j < 6; j++){
      do{
        pe = rand() % 107;
      }while (pecas[pe] == -1);
      jogp[i][j] = pecas[pe];
      pecas[pe] = -1;
      aux = jogp[i][j];
      while (aux < 122)
        aux += 16;
      contc = 0;
      while (aux != (122 + contc))
        contc++;
      cor = 41 + contc;
    }
    putchar('\n');
    putchar('\n');
  }
  contfim -= (6 * qtdeJog);  

  int flag=0, menu;
  while (x==1){   
    menu = menu2(qtdeJog, jogp, jogador, cheat, p, pecas , pontos);

    if (menu == 1){
      printf("\nPeca: ");
      scanf("%x", &p);
      while(VerificaPeca(qtdeJog, jogp, jogador, p, cheat)==0){
        printf("Peça indisponível. Digite novamente: ");
        scanf("%x", &p);
      }

      printf("Linha: ");
      scanf("%d", &l);
      printf("Coluna: ");
      scanf("%d", &c);

      if (cont1==0 && flag==0){
        while(l<0 || l>2 || c<0 || c>2){
          printf("\nVocê não pode jogar nessa posição!!!");
          printf("\nDigite novamente a peca: ");
          scanf("%x", &p);
          while(VerificaPeca(qtdeJog, jogp, jogador, p, cheat)==0){
            printf("Peça indisponível. Digite novamente: ");
            scanf("%x", &p);
          }
          printf("\nDigite novamente a linha: ");
          scanf("%d", &l);
          printf("Digite novamente a coluna: ");
          scanf("%d", &c);
        }
        
        flag = 1;
      }
      
      if (cont1==1){
        if (VerificaAdjacente(l, c, mxl, mxc, mnl, mnc, tab)==0 || VerificaFormCor (tab, l, c, p, minC, minL, maxC, maxL)==0 || VerificaFora(l, c, tab, maxL, maxC, minL, minC) == 0){
          printf("\nVocê não pode jogar nessa posição!!!\n");
          menu=1;
        }else{
          auxL=l;
          auxC=c;
          
        }
      }

      if (cont1>=2){
		printf("AAAAAA\n");
        if (VerificaJogadaLados(auxL, auxC, l, c, tab, aux1L, aux1C) == 0 || VerificaAdjacente(l, c, mxl, mxc, mnl, mnc, tab) == 0 || VerificaFormCor (tab, l, c, p, minC, minL, maxC, maxL)==0 || VerificaFora(l, c, tab, maxL, maxC, minL, minC) == 0){
          printf("\nVocê não pode jogar nessa posição!!!");
          menu=1;
        }else{
          auxL=l;
          auxC=c;
        }
      }
    
      if ((VerificaPeca(qtdeJog, jogp, jogador, p, cheat)==1 && VerificaAdjacente(l, c, mxl, mxc, mnl, mnc, tab)==1 && VerificaFormCor (tab, l, c, p, minC, minL, maxC, maxL)==1 && VerificaJogadaLados(auxL, auxC, l, c, tab, aux1L, aux1C) == 1 || VerificaFora(l, c, tab, maxL, maxC, minL, minC) == 1) || cont1==0){
        ZerarPeca(qtdeJog, jogp, jogador, p, cheat);
        if (l > mxl)
          mxl = l;
        if (c > mxc)
          mxc = c;
        if (l < mnl)
          mnl = l;
        if (c < mnc)
          mnc = c;
        if (l==minL){
          mxl++;
          mnl++;
        }
        if (c==minC){
          mxc++;
          mnc++;
        }
      }

      if (cont1==0){
        auxL=l;
        auxC=c;
        aux1L = l;
        aux1C = c;
      }
      if (l==maxL)
        maxL++;
      if (c==maxC)
        maxC++;    
      if (l==maxL && c==maxC){
        maxL++;
        maxC++;
      }
      if (l==minL){
        maxL++;
        aux1L++;
        auxL++;
      }   
      if (c==minC){
        aux1C++;
        auxC++;
        maxC++;
      }
      AtualizaTabuleiro(tab, p, l, c, minL, maxL, minC, maxC);
      cont1++;
      
    }else if (menu==3){
      if (contfim > 0){
        repor(jogador, qtdeJog, jogp, pecas, contfim);
      }
      if (contfim==0){
        for (int i=0; i<qtdeJog; i++){
          for (int j=0; j<6; j++){
            contfimj++;
            if (contfimj==6){
              pontos[i]+=6;
            }
          }
          contfimj = 0;
        }
        if (fim(qtdeJog, pontos)){
          x=0;
          exit(1);
        }
      }
      pontuacao (mxl, mxc, mnl, mnc, l, c, qtdeJog, jogador, pontos, tab);
      mnc = maxC;
      mxc = 0;
      mnl = maxL;
      mxl = 0;
      cont1 = 0;

      jogador++; 

      if (jogador>qtdeJog){
        jogador=1;
      }
    } 
  }  
  for (int i=0; i<100; i++) // Free no malloc
    free(tab[i]);
  free(tab);
}