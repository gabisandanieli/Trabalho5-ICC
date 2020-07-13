int VerificaPeca(int qtdeJog, int jogp[qtdeJog][6], int jogador, int p, int cheat);
void ZerarPeca(int qtdeJog, int jogp[qtdeJog][6], int jogador, int p, int cheat);
void Verificamxmn (int l, int c, int mxl, int mxc, int mnl, int mnc);
int VerificaAdjacente(int l, int c, int mxl, int mxc, int mnl, int mnc, int **tab);
int VerificaJogadaLados(int auxL, int auxC, int l, int c, int **tab, int aux1L, int aux1C);
int VerificaFora(int l, int c, int **tab, int maxL, int maxC, int minL, int minC);
int VerificaFormCor (int **tab, int l, int c, int p, int minC, int minL, int maxC, int maxL);
int repor (int i, int qtdeJog, int jogp[qtdeJog][6], int pecas[107], int contfim);
int trocarPeca (int jogador, int qtdeJog, int jogp[qtdeJog][6], int pecas[107], int cheat, int p);
