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
    BAIXO,      // 3
    PARA        // 4
} DIRECOES;


typedef struct
{
    DIRECOES direcaoJog;
    COORDENADA pos;
    int vidas;
    int status;
    int score;
}PACMAN;

typedef struct
{
    COORDENADA pos;
    int dir_fant;
}FANTASMA;


void desenha_menu(); //funciona
void entrada_jogo(); //funciona
int traduz_teclas(); //funciona

int move_pacman (PACMAN *jogador, int direcao, int direcaoAnt, char matriz_lab[LINHA_LAB][COLUNA_LAB], int *bolachas_especiais, int *bolachas_normais); //funciona
void SetConsoleSize(unsigned largura, unsigned altura); //funciona


int direcao_movimento_fantasma (int *x, int *y, int *direcao, char matriz_lab [LINHA_LAB][COLUNA_LAB]);
void move_fantasma (int *cx, int *cy, int *direcao, char matriz_lab [LINHA_LAB][COLUNA_LAB]); //funciona
void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void movimenta_todos_fastasmas (FANTASMA fantasma[], char matriz_lab [LINHA_LAB][COLUNA_LAB]);


int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB]);



void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void posicao_pacman(PACMAN *jogador, char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_normais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_especiais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void testa_se_fantasma_comeu_pacman(PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void game_over ();
