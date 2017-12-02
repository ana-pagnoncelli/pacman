#include <stdio.h>
#include "library.h"
#include <conio2.h>
#include <windows.h>
#include <time.h>
#define NUM_FANTASMA 5

int main ()
{
    char matriz_lab [30][100];
    int direcao, coordX, coordY, direcaoT, cFx, cFy;
    int inicia_jogo;
    FANTASMA fantasma[NUM_FANTASMA];

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

        gerador_fantasma(fantasma);
        le_labirinto(matriz_lab);
        desenha_menu();

        do
        {
            movimenta_todos_fastasmas (fantasma);
            if(kbhit())
            {
                direcaoT = traduz_teclas();
                if(direcaoT != 9)
                    direcao = direcaoT;
            }
            move_pacman (&coordX, &coordY, direcao);
            Sleep (250);
        }
        while(coordX !=0);
    }



    gotoxy(35, 35);
    return 0;
}

