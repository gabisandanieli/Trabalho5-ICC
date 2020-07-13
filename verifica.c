#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int cabecalho();

int VerificaPeca(int qtdeJog, int jogp[qtdeJog][6], int jogador, int p, int cheat){ // Verifica se a peca está contida no repositorio de pecas doe determinado jogador variando de acordo com o cheat mode
  if (p!=0){
    for(int i=0; i<qtdeJog; i++){
      for (int j=0; j<6; j++){
        if (cheat==0){
          if (jogador==i+1){
            if (p==jogp[i][j])
              return 1;
          }
        }
        if (cheat==1){
          if (p==jogp[i][j])
              return 1;
        }        
      }
    }
  }else
    return 0;
  return 0;
}

void ZerarPeca(int qtdeJog, int jogp[qtdeJog][6], int jogador, int p, int cheat){ // Caso a peca tenha sido jogada e atualizada no tabuleiro, ela é zerada e retirada na impressao de tela
  int i, j, flag=0;
  for(i=0; i<qtdeJog; i++){
      for (j=0; j<6; j++){
        if (cheat==0){
          if (flag==0){
            if (jogador==i+1){
              if (p==jogp[i][j]){
                jogp[i][j]=0;
                flag=1;
                break;
              }
            }
          }
        }else{
          if (flag==0){
            if (p==jogp[i][j]){
              jogp[i][j]=0;
              flag=1;
              break;
            }
          }
        }
      }
    }
}

void Verificamxmn (int l, int c, int mxl, int mxc, int mnl, int mnc){ // Irá atualizar os valores dos mínimos e dos máximos a cada jogada 
    
  if (l > mxl){
    mxl = l;
  }
  if (c > mxc){
    mxc = c;
  }
  if (l < mnl){
    mnl = l;
  }
  if (c < mnc){
    mnc = c;
  }
}

int VerificaAdjacente(int l, int c, int mxl, int mxc, int mnl, int mnc, int **tab){ // Verifica se as pecas sao adjacentes, isto e, se elas estao uma do lado da outra
  if (tab[l][c]==' '){
    if ((l == (mxl + 1) || l == (mnl - 1) || l == mxl || l == mnl) && (c == (mxc + 1) || c == (mnc - 1) || c == mxc || c == mnc)){
      return 1;
    }
  }
  else
    return 0;
  return 0;
}

int VerificaJogadaLados(int auxL, int auxC, int l, int c, int **tab, int aux1L, int aux1C){ // Verifica se o padrão das jogadas são de linha (mesma linha) ou coluna (mesma coluna)
  if (tab[l][c]==' '){ 
    if (auxC==c && aux1C==c && auxL!=l && aux1L!=l)
      return 1;
    if (auxL==l && aux1L==l && auxC!=c && aux1C!=c)
      return 1;
  }else
    return 0;
  return 0;  
}

int VerificaFora(int l, int c, int **tab, int maxL, int maxC, int minL, int minC){ // Verifica a existencia de pecas ao redor da linha e da coluna inserida -> isso ocorre a partir da segunda jogada já que, na primeira, o tabuleiro ainda está vazio
  if (l == minL){
    if (tab [l+1][c] == ' ' && tab [l][c-1] == ' ' && tab [l][c+1] == ' '){
      return 0;
    }
    else
      return 1;
  }
  else if (l == maxL){
    if (tab[l-1][c] == ' ' && tab [l][c-1] == ' ' && tab [l][c+1] == ' '){
      return 0;
    }
    else
      return 1;
  }
  else if (c == minC){
    if (tab[l-1][c] == ' ' && tab [l+1][c] == ' ' && tab [l][c+1] == ' '){
      return 0;
    }
    else
      return 1;
  }
  else if (c == maxC){
    if (tab[l-1][c] == ' ' && tab [l+1][c] == ' ' && tab [l][c-1] == ' '){
      return 0;
    }
    else
      return 1;
  }
  else
    return 0;
  return 1;
}

int VerificaFormCor (int **tab, int l, int c, int p, int minC, int minL, int maxC, int maxL){ // Verifica os padrões de formato e de cores das peças
  int auxp = p, i = 16, contcor = 0, contpd=1, contform = 0,  e1, e2, d1, d2, c1, c2, b1, b2;

  // POR FORMATO
  // ESQUERDA
  if (c != minC){
    e1 = tab[l][c-1];
    if (e1 == ' ')
      contform++;
    else{
      e2 = tab[l][c-2];
      if (e2 == ' '){
        if ((int)e1/10 == (int)p/10 && (e1 < 58 || e1 > 63) && (e1 < 106 || e1 > 111)){
          contform++;
            
        }else if (e1 >= 58 && e1 <= 63 && p >= 58 && p <= 63)
          contform++;

        else if (e1 >= 106 && e1 <= 111 && p >= 106 && p <= 111)
          contform++;
      }

      else{
        if ((int)e1/10 == (int)e2/10 && (e1 < 58 || e1 > 63) && (e1 < 106 || e1 > 111)){
          if ((int)p/10 == (int)e2/10)
            contform++;
        }

        else if (e1 >= 58 && e1 <= 63 && e2 >= 58 && e2 <= 63){
          if (p >= 58 && p <= 63)
            contform++;
        }

        else if (e1 >= 106 && e1 <= 111 && e2 >= 106 && e2 <= 111){
          if (p >= 106 && p <= 111)
            contform++;
        }
      }
    }
  } else
    contform++;

  //DIREITA

  if (c != maxC){
    d1 = tab[l][c+1];

    if (d1 == ' ')
      contform++;
    else{
      d2 = tab[l][c+2];
      if (d2 == ' '){
        if ((int)d1/10 == (int)p/10 && (d1 < 58 || d1 > 63) && (d1 < 106 || d1 > 111))
          contform++;

        else if (d1 >= 58 && d1 <= 63 && p >= 58 && p <= 63)
          contform++;

        else if (d1 >= 106 && d1 <= 111 && p >= 106 && p <= 111)
          contform++;
      }

      else{
        if ((int)d1/10 == (int)d2/10 && (d1 < 58 || d1 > 63) && (d1 < 106 || d1 > 111)){
          if ((int)p/10 == (int)d2/10)
            contform++;
        }

        else if (d1 >= 58 && d1 <= 63 && d2 >= 58 && d2 <= 63){
          if (p >= 58 && p <= 63)
            contform++;
        }

        else if (d1 >= 106 && d1 <= 111 && d2 >= 106 && d2 <= 111){
          if (p >= 106 && p <= 111)
            contform++;
        }
      }
    }
  } else
    contform++;

  // CIMA
    
  if (l != minL){
    c1 = tab[l-1][c];
      
    if (c1 == ' ')
      contform++;
    else{
      c2 = tab[l-2][c];
      if (c2 == ' '){
        if ((int)c1/10 == (int)p/10 && (c1 < 58 || c1 > 63) && (c1 < 106 || c1 > 111))
          contform++;
          
        else if (c1 >= 58 && c1 <= 63 && p >= 58 && p <= 63)
          contform++;
          
        else if (c1 >= 106 && c1 <= 111 && p >= 106 && p <= 111)
          contform++;          
      }

      else{
        if ((int)c1/10 == (int)c2/10 && (c1 < 58 || c1 > 63) && (c1 < 106 || c1 > 111)){
          if ((int)p/10 == (int)c2/10)
            contform++;
        }

        else if (c1 >= 58 && c1 <= 63 && c2 >= 58 && c2 <= 63){
          if (p >= 58 && p <= 63)
            contform++;
        }

        else if (c1 >= 106 && c1 <= 111 && c2 >= 106 && c2 <= 111){
          if (p >= 106 && p <= 111)
            contform++;
        }
      }
    }
  } else
    contform++;

  // BAIXO

  if (l != maxL){
    b1 = tab[l+1][c];

    if (b1 == ' ')
      contform++;
    else{
      b2 = tab[l+2][c];
      if (b2 == ' '){
        if ((int)b1/10 == (int)p/10 && (b1 < 58 || b1 > 63) && (b1 < 106 || b1 > 111))
          contform++;

        else if (b1 >= 58 && b1 <= 63 && p >= 58 && p <= 63)
          contform++;

        else if (b1 >= 106 && b1 <= 111 && p >= 106 && p <= 111)
          contform++;
      }

      else{
        if ((int)b1/10 == (int)b2/10 && (b1 < 58 || b1 > 63) && (b1 < 106 || b1 > 111)){
          if ((int)p/10 == (int)b2/10)
            contform++;
        }

        else if (b1 >= 58 && b1 <= 63 && b2 >= 58 && b2 <= 63){
          if (p >= 58 && p <= 63)
            contform++;
        }

        else if (b1 >= 106 && b1 <= 111 && b2 >= 106 && b2 <= 111){
          if (p >= 106 && p <= 111)
            contform++;
        }
      }
    }
  } else
    contform++;
  
  //POR COR
  //ESQUERDA  
  if (tab[l][c] == ' '){
    if (c != minC){
      e1 = tab[l][c-1];
      
      if (e1 == ' ')
        contcor++;
      else{
        e2 = tab[l][c-2];
        if (e2 == ' '){
          if (e1 > p){
            while (p < e1)
              p += i;
          }
          else if (p > e1){
            while (e1 < p)
              e1 += i;
          }
          if (p == e1)
            contcor++;
        
        } else if (e1 > e2 && e2 != ' '){
          while (e2 < e1)
            e2 += i;
          if (e2 == e1){
            if (e1 > p){
              while (p < e1)
                p += i;
            }
            if (p > e1){
              while (e1 < p)
                e1 += i;
            }
            if (p == e1)
              contcor++;
          }
        }
        if (e2 > e1 && e1 != ' '){
          while (e1 < e2)
            e1 += i;                  
          if (e1 == e2){
            if (e2 > p){
              while (p < e2)
                p += i;
            }            
            if (p > e2){
              while (e2 < p)
                e2 += i;
            }           
            if (p==e2)
              contcor++;
          }      
        }
      }
    }else 
      contcor++;

    //DIREITA
    if (c != maxC){
      d1 = tab[l][c+1];

      if (d1 == ' ')
        contcor++;
      else{
        d2 = tab[l][c+2];
        if (d2 == ' '){
          if (d1 > p){
            while (p < d1)
              p += i;
          } else if (p > d1 && d2 != ' '){
            while (d1 < p)
              d1 += i;
          }
          if (p == d1)
            contcor++;          
        }

        if (d1 > d2){
          while (d2 < d1)
            d2 += i;
          if (d2 == d1){
            if (d1 > p){
              while (p < d1)
                p += i;
            }
            if (p > d1){
              while (d1 < p)
                d1 += i;
            }
            if (p==d1)
              contcor++;
          }
        }

        if (d2 > d1 && d1 != ' '){
          while (d1 < d2)
            d1 += i;
          if (d1 == d2){
            if (d2 > p){
              while (p < d2)
                p += i;
            }
            if (p > d2){
              while (d2 < p)
                d2 += i;
            }
            if (p==d2)
              contcor++;
          }
        }
      }
    } else
      contcor++;
      
    // CIMA
    if (l != minL){
      c1 = tab[l-1][c];
      
      if (c1 == ' ')
        contcor++;
      else{
        c2 = tab[l-2][c];  
        if (c2 == ' '){
          if (c1 > p){
            while (p < c1)
              p += i;
          }
          else if (p > c1){
            while (c1 < p)
              c1 += i;
          }
          if (p == c1)
            contcor++; 
        }

        else if (c1 > c2 && c1 != ' '){
          while (c2 < c1)
            c2 += i;
          if (c2 == c1){
            if (c1 > p){
              while (p < c1)
                p += i;
            }
            if (p > c1){
              while (c1 < p)
                c1 += i;
            }
            if (p==c1)
              contcor++;
          }
        }

        else if (c2 > c1 && c1 != ' '){
          while (c1 < c2)
            c1 += i;
          if (c1 == c2){
            if (c2 > p){
              while (p < c2)
                p += i;
            }
            if (p > c2){
              while (c2 < p)
                c2 += i;
            }
            if (p==c2)
              contcor++;
          }
        }
      }
    } else
      contcor++;

    // BAIXO
    if (l != maxL){
      b1 = tab[l+1][c];

      if (b1 == ' ')
        contcor++;
      else{
        b2 = tab[l+2][c];
        if (b2 == ' '){
          if (b1 > p){
            while (p < b1)
              p += i;
          }
          if (p > b1){
            while (b1 < p)
              b1 += i;
          }
          if (p == b1)
            contcor++;      
        }

        if (b1 > b2 && b2 != ' '){
          while (b2 < b1)
            b2 += i;
          if (b2 == b1){
            if (b1 > p){
              while (p < b1)
                p += i;
            }
            if (p > b1){
              while (b1 < p)
                b1 += i;
            }
            if (p==b1)
              contcor++;
          }
        }

        if (b2 > b1 && b1 !=  ' '){
          while (b1 < b2)
            b1 += i;
          if (b1 == b2){
            while (p < b2)
              p += i;
            if (b2 > p){
              while (p < b2)
                p += i;
            }
            if (p > b2){
              while (b2 < p)
                b2 += i;
            }
          }
        }
      }
    } else 
      contcor++;

    int prx;
    //MESMA PEÇA
    //ESQUERDA
    if (c != minC){
      for (prx = 1; tab [l][c-prx] != ' '; prx++){
        if (tab [l][c-prx] == auxp)
          contpd = 0;
      }
    }
    //DIREITA
    if (c != maxC){
      for (prx = 1; tab [l][c+prx] != ' '; prx++){
        if (tab [l][c+prx] == auxp)
          contpd = 0;
      }
    }
    //CIMA
    if (l != minL){
      for (prx = 1; tab [l-prx][c] != ' '; prx++){
        if (auxp == tab [l-prx][c])
          contpd = 0;
      }
    }
    //BAIXO
    if (l != maxL){
      for (prx = 1; tab [l+prx][c] != ' '; prx++){
        if (tab [l+prx][c] == auxp)
          contpd = 0;
      }
    }

    if ((contcor == 4 || contform == 4) && contpd != 0)
      return 1;
    else
      return 0;
  } else
    return 0;
  return 0;
}

int repor (int i, int qtdeJog, int jogp[qtdeJog][6], int pecas[107], int contfim){
  int pe;

  for(int j = 0; j < 6; j++){
    if (jogp[i-1][j] == 0){
      do{
        pe = rand() % 107;
      }while (pecas[pe] == -1);

      jogp[i-1][j] = pecas[pe];
      pecas[pe] = -1;
      contfim--;
    } 
  }
  return 1;
}

int trocarPeca (int jogador, int qtdeJog, int jogp[qtdeJog][6], int pecas[107], int cheat, int p){
  int pe, j = 0;

  printf("Qual peca deseja trocar?");
  scanf ("%x", &p);
  while(VerificaPeca(qtdeJog, jogp, jogador, p, cheat)==0){
    printf("Peça indisponível. Digite novamente: ");
    scanf ("%x", &p);
  }

  while (jogp [jogador-1][j] != p)
    j++;

  do{
    pe = rand() % 107;
  }while (pecas[pe] == -1);

  jogp[jogador-1][j] = pecas[pe];
  pecas[pe] = -1;
  
  do{
    pe = rand() % 107;
  }while (pecas[pe] != -1);

  pecas[pe] = p;
  return 1;
}

