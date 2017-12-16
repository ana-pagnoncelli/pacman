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
    COORDENADA pos_iniciais_fantasmas [NUM_FANTASMA];
    int rep_pacman, rep_fant = 0;

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
        gerador_fantasma(fantasma, matriz_lab, pos_iniciais_fantasmas);
        posicao_pacman(&jogador, matriz_lab);
        desenha_menu();
        gotoxy(32, 1);
        textbackground(BLUE);
        printf("%d", jogador.vidas);
        textbackground(BLACK);
        bolachas_normais = 1;
        bolachas_especiais = 1;

        do
        {
            rep_fant = 0;

            if(jogador.poder == 1) //faz isso apenas quando o poder esta ativado
            {
                clock_t start, end = 0;

                start = clock ();

                do
                {
                    if(rep_fant == 2)
                    {
                        movimenta_todos_fastasmas (fantasma, matriz_lab, &jogador);
                        testa_se_pacman_comeu_fantasma(&jogador, fantasma, matriz_lab, pos_iniciais_fantasmas);
                        rep_fant = 0;
                    }

                    rep_fant ++;

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
                    testa_se_pacman_comeu_fantasma(&jogador, fantasma, matriz_lab, pos_iniciais_fantasmas);

                    end = clock ();
                    Sleep (100);
                }
                while((end - start < 5000));
                jogador.poder = 0;
            }



            else //senao sempre executa a funcao normal
            {
               if(kbhit())
                {
                    direcaoT = traduz_teclas();
                    if(direcaoT != 9)
                        direcao = direcaoT;
                }

                if(direcao == PAUSE) //testa se o jogo esta pausado, se n estiver roda normalmente
                {
                    gotoxy(20, 18);
                    textbackground(YELLOW);
                    //textcolor(BLACK);
                    printf("JOGO PAUSADO, PRESSIONE QUALQUER TECLA DE MOVIMENTACAO PARA CONTINUAR.");
                    textbackground(BLACK);
                    textcolor(WHITE);
                    while(direcao == PAUSE)
                    {
                        if(kbhit())
                        {
                            direcaoT = traduz_teclas();
                            if(direcaoT != 9)
                                direcao = direcaoT;
                        }
                    }

                    printa_labirinto(matriz_lab);
                }

                else
                {
                    movimenta_todos_fastasmas (fantasma, matriz_lab, &jogador);
                    testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);

                    if((move_pacman (fantasma, &jogador, direcao, direcaoAnt, matriz_lab, &bolachas_especiais, &bolachas_normais)) == 1)
                    {
                        direcaoAnt = direcao;
                    }
                    else
                    {
                        move_pacman(fantasma, &jogador, direcaoAnt, direcao, matriz_lab, &bolachas_especiais, &bolachas_normais);
                    }

                    testa_se_fantasma_comeu_pacman (&jogador, fantasma, matriz_lab);
                }



                Sleep (100);
            }

        }
        while(jogador.vidas > 0 && (bolachas_especiais > 0 || bolachas_normais > 0));


    }

    gotoxy(35, 35);
    return 0;
}
