tabuleiro.o: tabuleiro.c
	gcc -o tabuleiro.o -c tabuleiro.c

verifica.o: verifica.c
	gcc -o verifica.o -c verifica.c

menu.o: menu.c
	gcc -o menu.o -c menu.c

pontuacao.o: pontuacao.c
	gcc -o pontuacao.o -c pontuacao.c

main.o: main.c
	gcc -o main.o -c main.c

main: main.o tabuleiro.o verifica.o menu.o pontuacao.o
	gcc -o main main.o tabuleiro.o verifica.o menu.o pontuacao.o

all: main

run: main
	./main
	
clean:
	rm *.o

  