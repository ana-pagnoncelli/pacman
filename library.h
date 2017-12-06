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
    COORDENADA pos;
    int vidas;
    int status;
    int score;
}PACMAN;

typedef struct
{
    COORDENADA pos;
}FANTASMA;


void desenha_menu(); //funciona
void entrada_jogo(); //funciona
int traduz_teclas(); //funciona
int move_pacman (PACMAN *jogador, int direcao, int direcaoAnt, char matriz_lab[LINHA_LAB][COLUNA_LAB]); //funciona
void SetConsoleSize(unsigned largura, unsigned altura); //funciona
void move_fantasma (int *cx, int *cy, char matriz_lab [LINHA_LAB][COLUNA_LAB]); //funciona
int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB]);
void direcao_movimento_fantasma (int *x, int *y, int direcao, char matriz_lab [LINHA_LAB][COLUNA_LAB]);
void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void movimenta_todos_fastasmas (FANTASMA fantasma[], char matriz_lab [LINHA_LAB][COLUNA_LAB]);
void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void posicao_pacman(PACMAN *jogador, char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_normais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_especiais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void testa_se_fantasma_comeu_pacman(PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void game_over ();
