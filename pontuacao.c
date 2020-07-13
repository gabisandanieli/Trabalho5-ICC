#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int cabecalho();

int pontuacao (int mxl, int mxc, int mnl, int mnc, int l, int c, int qtdeJog, int jogador, int pontos[qtdeJog], int **tab){// Verifica todas as ocasiões para a contagem de pontos quando o jogador passa a vez
  int pts = 0, ptscima = 0, ptsbaixo = 0, ptsesq = 0, ptsdir = 0, flagpri = 0;

  for (int i=0; i<qtdeJog; i++){
    pontos[i]=0;
    
  }
  
  //PEÇA COLOCADA
  if (mnl == mxl && mnc == mxc && (tab [l][c-1] != ' ' || tab [l][c+1] != ' ' || tab [l-1][c] != ' ' || tab [l+1][c] != ' '))
    flagpri = 1;

  for (int auxl = mnl; auxl <= mxl; auxl++){
    for (int auxc = mnc; auxc <= mxc; auxc++){
      if (flagpri == 0)
        pts++;

      //ESQUERDA
      if ((mxc != mnc && c == mnc) || mxl != mnl || (mnl == mxl && mnc == mxc)){
        if (tab [l][c-1] != ' '){
          for (int prx = 0; tab [l][c-prx] != ' '; prx++){
            pts++;
            ptsesq++;
          }
        }
      }

      //DIREITA
      if ((mxc != mnc && c == mxc) || mxl != mnl || (mnl == mxl && mnc == mxc)){
        if (tab [l][c+1] != ' '){
          for (int prx = 0; tab [l][c+prx] != ' '; prx++){
            pts++;
            ptsdir++;
          }
        }
      }

      //CIMA
      if ((mxl != mnl && l == mnl) || mxc != mnc || (mnl == mxl && mnc == mxc)){
        if (tab [l-1][c] != ' '){
          for (int prx = 0; tab [l-prx][c] != ' '; prx++){
            pts++;
            ptscima++;
          }
        }
      }

      //BAIXO
      if ((mxl != mnl && l == mxl) || mxc != mnc || (mnl == mxl && mnc == mxc)){
        if (tab [l+1][c] != ' '){
          for (int prx = 0; tab [l+prx][c] != ' '; prx++){
            pts++;
            ptsbaixo++;
          }
        }
      }
    }
  }
  
  if (ptsesq == 5)
    pts += 6;  
  if (ptsdir == 5)
    pts += 6;
  if (ptscima == 5)
    pts += 6;
  if (ptsbaixo == 5)
    pts += 6;
  if (ptsdir + ptsesq + (mxc - mnc + 1) == 6)
    pts += 6;    
  if (ptsbaixo + ptscima + (mxl - mnl + 1) == 6)
    pts += 6;

  putchar('\n');
  putchar('\n');

  
  for (int i=0; i<qtdeJog; i++){
    if (jogador==i+1){
      pontos [jogador-1] += pts;
    }
    
  }
  
  return 1;
}

int fim(int qtdeJog, int pontos[qtdeJog]){
  int aux=0, venc, i;
  for (i=0; i<qtdeJog; i++){
    if (pontos[i]>aux){
      aux = pontos[i];
      venc = i;
    }else{
      aux=aux;
    }
  }
  printf("O jogador %d venceu!!!", venc);
  return 1;
}