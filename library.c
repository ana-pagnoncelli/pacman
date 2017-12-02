#include <stdio.h>
#include "library.h"
#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <string.h>


void desenha_menu()
{
    int i;

    for(i = 1; i<105; i++)
    {
        textbackground(BLUE);
        putchxy(i, 1,' ');
        putchxy(i, 34,' ');
    }
    for(i = 1; i<35; i++)
    {
        putchxy(1, i,' ');
        putchxy(104, i,' ');
    }

    gotoxy(5, 1);
    printf("Score:");
    gotoxy(25, 1);
    printf("Vidas:");
    textbackground(BLACK);

}

void entrada_jogo()
{
    gotoxy(50, 15);
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("START:");
    textbackground(BLACK);
    textcolor(WHITE);
}

int traduz_teclas ()
{
    int tecla;
    tecla = getch();
    tecla = toupper (tecla);
    if(tecla == 'W')
        return CIMA; //0
    else if(tecla == 'D')
        return DIREITA; //1
    else if(tecla == 'S')
        return BAIXO; //2
    else if(tecla == 'A')
        return ESQUERDA; //3
    else
        return 9; //default
}

void move_pacman (int *cx, int *cy, int direcao)
{
    int xt = *cx, yt = *cy;

    textbackground(BLACK);
    putchxy(*cx, *cy, ' ');

    switch(direcao)
    {
    case CIMA:
        yt --;
        break;
    case DIREITA:
        xt ++;
        break;
    case BAIXO:
        yt++;
        break;
    case ESQUERDA:
        xt--;
        break;
    }
    if(testa_parede(xt, yt) == 1)
    {
        *cx = xt;
        *cy = yt;
    }
    textbackground(YELLOW);
    putchxy(*cx, *cy, 'C');
    textbackground(BLACK);
}

void SetConsoleSize(unsigned largura, unsigned altura) //aumenta tamanho da tela, funcao do moodle
{
    SMALL_RECT r;
    COORD c;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    c.X = largura;
    c.Y = altura;
    SetConsoleScreenBufferSize(stdoutHandle, c);

    r.Left = 0;
    r.Top = 0;
    r.Right = largura - 1;
    r.Bottom = altura - 1;
    SetConsoleWindowInfo(stdoutHandle, 1, &r);
}


void move_fantasma (int *cx, int *cy)
{
    int direcao;


    direcao = rand() %4 ;

    textbackground(BLACK);
    putchxy(*cx, *cy, ' ');

    direcao_movimento_fantasma(cx, cy, direcao);

    textbackground(RED);
    putchxy(*cx, *cy, 'W');
    textbackground(BLACK);

}



int testa_parede (int x, int y)
{
    if(x>100 || y>30 || x <= 1 || y <= 1)
        return 0;

    else
        return 1;
}


void direcao_movimento_fantasma (int *x, int *y, int direcao)
{
    int xt = *x, yt = *y;

    switch(direcao)
    {
    case CIMA:
        yt --;
        break;
    case DIREITA:
        xt ++;
        break;
    case BAIXO:
        yt++;
        break;
    case ESQUERDA:
        xt--;
        break;
    }
    if(testa_parede(xt, yt) == 1)
    {
        *x = xt;
        *y = yt;
    }
    else
    {
        switch(direcao)
        {
        case CIMA:
            direcao_movimento_fantasma (x, y, DIREITA);
            break;
        case DIREITA:
            direcao_movimento_fantasma (x, y, BAIXO);
            break;
        case BAIXO:
            direcao_movimento_fantasma (x, y, ESQUERDA);
            break;
        case ESQUERDA:
            direcao_movimento_fantasma (x, y, CIMA);
            break;
        }
    }
}

void gerador_fantasma (FANTASMA fantasma[])
{

    fantasma[0].pos.x = 5;
    fantasma[0].pos.y = 2;
    fantasma[1].pos.x = 15;
    fantasma[1].pos.y = 5;
    fantasma[2].pos.x = 35;
    fantasma[2].pos.y = 10;
    fantasma[3].pos.x = 55;
    fantasma[3].pos.y = 15;
    fantasma[4].pos.x = 75;
    fantasma[4].pos.y = 20;

}

void movimenta_todos_fastasmas (FANTASMA fantasma[])
{
    int i;
    srand(time(NULL));

    for(i = 0; i<NUM_FANTASMA; i++)
    {
        move_fantasma (&fantasma[i].pos.x, &fantasma[i].pos.y);
    }
}

void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna;
    FILE* arq;

    arq = fopen("labirinto.txt", "r");

    for(linha = 0; linha <= LINHA_LAB; linha ++)
    {
        for(coluna = 0; coluna <= COLUNA_LAB; coluna ++)
        {
            matriz_lab[linha][coluna] = fgetc(arq);
        }

        matriz_lab[linha][coluna] = '\0';
        gotoxy(3, 3+linha);
        puts(matriz_lab[linha]);
    }

    fclose(arq);
}
