#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>
#define NUM_FANTASMA 5
#define BLUE 9
#define LINHA_LAB 31
#define COLUNA_LAB 101
#include <math.h>
#define PROBDIRECAOFANTASMA 0

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
    PARA,        // 4
    PAUSE       // 5
} DIRECOES;


typedef struct
{
    DIRECOES direcaoJog;
    COORDENADA pos;
    int vidas;
    int poder; // 1 == ativado - 0 == desativado
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

int move_pacman (FANTASMA fantasma [], PACMAN *jogador, int direcao, int direcaoAnt, char matriz_lab[LINHA_LAB][COLUNA_LAB], int *bolachas_especiais, int *bolachas_normais); //funciona
void atualiza_jogo (FANTASMA fantasma [], PACMAN *jogador, char matriz_lab [LINHA_LAB][COLUNA_LAB], int *bolachas_normais, int *bolachas_especiais, int direcao);
void SetConsoleSize(unsigned largura, unsigned altura); //funciona


void direcao_movimento_fantasma (FANTASMA *fantasma, char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador);
void move_fantasma (FANTASMA *fantasma, char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador); //funciona
void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB], COORDENADA pos_iniciais_fantasmas []);
void movimenta_todos_fastasmas (FANTASMA fantasma[], char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador);
int calcula_menor_distancia(PACMAN *jogador, FANTASMA *fantasma);
float calculo_da_distancia(int x_pac, int y_pac, int x_fant, int y_fant);


int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB]);
int testa_bifurcacao (int dir_fant, int xt, int yt, char matriz_lab [LINHA_LAB][COLUNA_LAB]);
void testa_se_pacman_comeu_fantasma (PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB], COORDENADA pos_iniciais_fantasmas []);
void testa_se_fantasma_comeu_pacman(PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB]);


void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void posicao_pacman(PACMAN *jogador, char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_normais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
int conta_bolachas_especiais (char matriz_lab[LINHA_LAB][COLUNA_LAB]);
void game_over ();
