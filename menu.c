#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main();
int cabecalho();

int trocarPeca(int jogador, int qtdeJog, int jogp[qtdeJog][6], int pecas[107], int cheat, int p);

int menu (){
  int opcao, op, cheat = 0;
  cabecalho ();

  printf("\t\t\t\e[0;107m\e[1;90m----- MODO DE JOGO -----\e[0m\n\n\n");
  printf("\t\t\t1 - Jogar\n");
  printf("\t\t\t2 - Sair\n");

  printf("\n\t\t\t------------------------");
  printf("\n\t\t\tOpcao: ");
  scanf("%d", &opcao);
  while (opcao < 1 || opcao > 2){
    printf("\nErro, digite novamente: ");
    scanf("%d",&opcao);
  }

  switch (opcao){
    case 1:
      cabecalho ();

      printf("  \e[0;107m\e[1;90m----- DESEJA UTILIZAR O MODO CHEAT? -----\e[0m\n\n\n");
      printf("\t\t\t1 - Sim\n");
      printf("\t\t\t2 - Nao\n");
      printf("\t\t\t3 - Voltar\n");
      printf("\n\t\t\t------------------------");
      printf("\n\t\t\tOpcao: ");
      scanf("%d", &op);

      while (op < 1 || op >3){
        printf("\nErro, digite novamente: ");
        scanf("%d",&op);
      }

      if (op == 1)
        return 1;
      else if (op == 2)
        return 0;
      else if(op == 3)
        main();
    break;

    case 2:
      exit(1);
    break;
    
  }
  return 0;
}

int cabecalho (){
  //printf("\33[H\33[2J"); //Para limpar a tela 
  putchar('\n');

  printf("\e[1;90m=============================================\e[0m\n");
  printf("\t\t\t\t\t\e[1;91mQ\e[1;96mW\e[1;93mI\e[1;90mR\e[1;94mK\e[1;92mL\e[1;95mE\e[0m\n");
  printf("\e[1;90m=============================================\e[0m\n\n\n");
  return 1;
}

int menu2(int qtdeJog, int jogp[qtdeJog][6], int jogador, int cheat, int p, int pecas[107], int pontos[qtdeJog]){
  int res;
  int contc = 0, aux = 0, cor=0;
  //dados_Jogador dj;

  for(int i = 0; i < qtdeJog; i++){
    printf("Jogador %d - (%d pontos): ", i+1, pontos[i]);
    for(int j = 0; j < 6; j++){
      if (jogp[i][j]!=0){
        aux = jogp[i][j];
        while (aux < 122)
          aux += 16;
        contc = 0;
        while (aux != (122 + contc))
          contc++;
        cor = 41 + contc;
        printf ("|\e[%dm%x\e[0m|", cor, jogp[i][j]);
      }
    }
    putchar('\n');
    putchar('\n');
  }
  
  printf("\nVez do jogador %d : ", jogador);

  contc = 0;
  aux = 0;
   cor=0;
    for (int i=0; i<qtdeJog; i++){
      for (int j=0; j<6; j++){
          if (jogp[i][j]!=0){
            if (jogador==i+1){
              aux = jogp[i][j];
              while (aux < 122)
                aux += 16;
              contc = 0;
              while (aux != (122 + contc))
                contc++;           
              cor = 41 + contc;
              printf("|\e[%dm%x\e[0m|", cor, jogp[i][j]);
            }
          }
      }
    }
  printf("\n");
  printf("  \n\e[0;107m\e[1;90m----- Opções: -----\e[0m\n\n\n");
  printf("1 - Jogar\n");
  printf("2 - Trocar\n");
  printf("3 - Passar\n");

  printf("\n------------------------");
  printf("\nOpcao: ");
  while (scanf("%d", &res) == 0){
    printf("Comando invalido. Digite novamente: ");
    setbuf(stdin, NULL);
  }
  switch(res){
    case 1:
      return 1;
      break;
    case 2: 
      trocarPeca(jogador, qtdeJog, jogp, pecas, cheat, p);
      return 3;
      break;
    case 3:
      return 3;
      break;
    default:
      printf("Operacao Invalida\n");
  }
}