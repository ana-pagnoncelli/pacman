#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>
#define NUM_FANTASMA 5
#define BLUE 9
#define LINHA_LAB 31
#define COLUNA_LAB 101

typedef struct
{
    int x;
    int y;
} COORDENADA;

typedef enum
{
    CIMA,       // 0
    DIREITA,    // 1
    ESQUERDA,   // 2
    BAIXO       // 3
} DIRECOES;


typedef struct
{
    DIRECOES direcaoJog;
    COORDENADA posicao;
    int vidas;
    int status;
}JOGADOR;

typedef struct
{
    COORDENADA pos;
}FANTASMA;


void desenha_menu(); //funciona
void entrada_jogo(); //funciona
int traduz_teclas(); //funciona
void move_pacman (int* cx, int*cy, int direcao); //funciona
void SetConsoleSize(unsigned largura, unsigned altura); //funciona
void move_fantasma (int *cx, int *cy); //funciona
int testa_parede (int x, int y);
void direcao_movimento_fantasma (int *x, int *y, int direcao);
void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void movimenta_todos_fastasmas (FANTASMA fantasma[]);
void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB]);
