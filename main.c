#include <stdio.h>
#include "library.h"
#include <conio2.h>
#include <windows.h>
#include <time.h>
#define NUM_FANTASMA 5
#define LINHA_LAB 31
#define COLUNA_LAB 101

int main ()
{
    char matriz_lab [LINHA_LAB][COLUNA_LAB];
    int direcao, coordX, coordY, direcaoT, cFx, cFy;
    int inicia_jogo;
    FANTASMA fantasma[NUM_FANTASMA];
    int linha,coluna, encontrado = 0;
    PACMAN jogador;

    SetConsoleSize(120, 40);


    coordX = 50;
    coordY = 15;
    cFx = 20;
    cFy = 10;

    desenha_menu();
    entrada_jogo();
    inicia_jogo = getch();


    if(inicia_jogo == 13)
    {

        system("cls");

        le_labirinto(matriz_lab);
        // printa_labirinto(matriz_lab);
        gerador_fantasma(fantasma, matriz_lab);
        posicao_pacman(&jogador, matriz_lab);

        desenha_menu();

        do
        {
            movimenta_todos_fastasmas (fantasma, matriz_lab);

            if(kbhit())
            {
                direcaoT = traduz_teclas();
                if(direcaoT != 9)
                    direcao = direcaoT;
            }
            move_pacman (&jogador, direcao, matriz_lab);
            Sleep (250);
        }
        while(coordX !=0);


    }

    gotoxy(35, 35);
    return 0;
}

