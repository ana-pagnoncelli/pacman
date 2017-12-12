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
    int direcao, direcaoT, direcaoAnt;
    int inicia_jogo;
    FANTASMA fantasma[NUM_FANTASMA];
    int linha,coluna, encontrado = 0;
    PACMAN jogador;
    int bolachas_normais = 0, bolachas_especiais = 0, i;

    jogador.vidas = 2;
    jogador.score = 0;

    /*
    Seto a posicao deles inicial para uma direcao qualquer,
    para que somente mude depois quando encontrarem um obstaculo.
    Se a primeira dada for um obstaculo ja muda.
    */

    for(i = 0; i <NUM_FANTASMA; i ++)
    {
        fantasma[i].dir_fant = 3;
    }

    SetConsoleSize(120, 40);

    desenha_menu();
    entrada_jogo();
    inicia_jogo = getch();


    if(inicia_jogo == 13)
    {

        system("cls");

        le_labirinto(matriz_lab);
        bolachas_normais = conta_bolachas_normais(matriz_lab);
        bolachas_especiais = conta_bolachas_especiais(matriz_lab);
        printa_labirinto(matriz_lab);
        gerador_fantasma(fantasma, matriz_lab);
        posicao_pacman(&jogador, matriz_lab);
        desenha_menu();
        gotoxy(32, 1);
        textbackground(BLUE);
        printf("%d", jogador.vidas);
        textbackground(BLACK);

        do
        {
            if(jogador.poder == 1)
            {
                clock_t start, end = 0;

                start = clock ();

                do
                {
                    movimenta_todos_fastasmas (fantasma, matriz_lab, &jogador);
                    //testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);

                    for (i = 0; i<2; i++)
                    {
                        if(kbhit())
                        {
                            direcaoT = traduz_teclas();
                            if(direcaoT != 9)
                                direcao = direcaoT;
                        }

                        if((move_pacman (fantasma, &jogador, direcao, direcaoAnt, matriz_lab, &bolachas_especiais, &bolachas_normais)) == 1)
                        {
                            direcaoAnt = direcao;
                        }
                        else
                        {
                            move_pacman(fantasma, &jogador, direcaoAnt, direcao, matriz_lab, &bolachas_especiais, &bolachas_normais);
                        }
                    }
                    //testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);

                    end = clock ();
                    Sleep (200);
                }
                while((end - start < 5000));
                jogador.poder = 0;
            }
            else
            {
                movimenta_todos_fastasmas (fantasma, matriz_lab, &jogador);
                //testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);


                if(kbhit())
                {
                    direcaoT = traduz_teclas();
                    if(direcaoT != 9)
                        direcao = direcaoT;
                }

                if((move_pacman (fantasma, &jogador, direcao, direcaoAnt, matriz_lab, &bolachas_especiais, &bolachas_normais)) == 1)
                {
                    direcaoAnt = direcao;
                }
                else
                {
                    move_pacman(fantasma, &jogador, direcaoAnt, direcao, matriz_lab, &bolachas_especiais, &bolachas_normais);
                }

                //testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);


                Sleep (100);
            }

        }
        while(jogador.vidas != 0);


    }

    gotoxy(35, 35);
    return 0;
}
/* Dependendo de quantas vezes a mais a função do pacman vai se repetir a mais em relacao a do fantasma
o sleep deve ser aumentado em função deste numero, pois senao da ideia de que o pacman aumentou a velocidade
em vez de os fantasmas diminuirem a deles*/
