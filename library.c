#include <stdio.h>
#include "library.h"
#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <string.h>

/*Basicamente desenha as bordas do menu. Sendo elas maiores que as dimensões do jogo.*/

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

/* Desenha uma entrada, onde vc tem a opcao de começar e futuramente as teclas de movimento
o que cada uma faz, etc. */

void entrada_jogo()
{
    gotoxy(50, 15);
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("START:");
    textbackground(BLACK);
    textcolor(WHITE);
}

/*Recebe atraves do kbhit uma tecla e define o que ela significa,
a principio serve só para a movimentação do pacman.*/

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

/*Recebe um jogador e uma matriz, a partir disso procura na matriz a posicao em
que o pacman(a letra 'C') se encontra e quando acha passa a posição para o jogador. */

void posicao_pacman(PACMAN *jogador, char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int encontrado = 0, linha = 0, coluna = 0;

    while(encontrado == 0 && linha < LINHA_LAB)
    {
        while(encontrado == 0 && coluna < COLUNA_LAB)
        {
            if(matriz_lab[linha][coluna] == 'C')
            {
                jogador->pos.x = coluna + 3;
                jogador->pos.y = linha + 3;
                textbackground(YELLOW);
                putchxy(coluna + 3, linha + 3, 'C');
                encontrado = 1;
            }
            coluna ++;
        }
        coluna = 0;
        linha ++;
    }

}

/*Recebe um jogador (para ter acesso as posicoes setadas no posicao_pacman e para modifica-lo
atraves de ponteiros, para a proxima posicao), uma direção (recebida atraves do kbhit na main
e traduzida pelo traduz_teclas) e a matriz (para passarmos para o testa parede para ver se na proxima
posição do pacman vai ter parede ou nao). Basicamente vai excluindo o pacman da posicao antiga e
desenhando na nova SE POSSIVEL.*/

void move_pacman (PACMAN *jogador, int direcao, char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int xt, yt;

    xt = jogador->pos.x;
    yt = jogador->pos.y;

    textbackground(BLACK);


    if(matriz_lab[yt-3][xt-3] == 'o' || matriz_lab[yt-3][xt-3] == '*' ) //cada vez que come uma bolachinha poe um espaço branco na matriz
    {
       matriz_lab[yt-3][xt-3] = ' '; //senao o fantasma desenha de novo.
    }

    putchxy(jogador->pos.x, jogador->pos.y, ' ');

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
    textbackground(BLACK);
    if(testa_parede(xt, yt, matriz_lab) == 1)
    {
        jogador->pos.x = xt;
        jogador->pos.y = yt;
    }
    textbackground(YELLOW);
    putchxy(jogador->pos.x, jogador->pos.y, 'C');
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


void move_fantasma (int *cx, int *cy, char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    int direcao, x, y;

    x = *cx ;
    y = *cy ;

    direcao = rand() %4 ;

    textbackground(BLACK);

    if(matriz_lab[y-3][x-3] == 'o' ) //quando o fantasma passa por cima dos espaços q contem bolachinhas
    {
        putchxy(x, y, 'o'); //desenha elas de novo

    }
    if(matriz_lab[y-3][x-3] == '*')
    {
        putchxy(x, y, '*');
    }

    if(matriz_lab[y-3][x-3] == ' ' || matriz_lab[y-3][x-3] == 'W')
    {
        putchxy(x, y, ' ');
    }

    direcao_movimento_fantasma(cx, cy, direcao, matriz_lab);

    textbackground(RED);
    putchxy(*cx, *cy, 'W');
    textbackground(BLACK);

}



int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    if(x>103 || y>32 || x <= 2 || y <= 3 || matriz_lab[y-3][x-3] == '#')
        return 0;

    else
        return 1;
}


void direcao_movimento_fantasma (int *x, int *y, int direcao, char matriz_lab [LINHA_LAB][COLUNA_LAB])
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
    if(testa_parede(xt, yt, matriz_lab) == 1)
    {
        *x = xt;
        *y = yt;
    }
    else
    {
        switch(direcao)
        {
        case CIMA:
            direcao_movimento_fantasma (x, y, DIREITA, matriz_lab);
            break;
        case DIREITA:
            direcao_movimento_fantasma (x, y, BAIXO, matriz_lab);
            break;
        case BAIXO:
            direcao_movimento_fantasma (x, y, ESQUERDA, matriz_lab);
            break;
        case ESQUERDA:
            direcao_movimento_fantasma (x, y, CIMA, matriz_lab);
            break;
        }
    }
}

void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB])
{

    int linha = 0, coluna = 0, encontrado, i;

    encontrado = 0;
    i = 0;

    while(encontrado < 5 && linha < LINHA_LAB)
    {
        while(encontrado < 5 && coluna < COLUNA_LAB)
        {
            if(matriz_lab[linha][coluna] == 'W')
            {
                fantasma[i].pos.x = coluna + 3;
                fantasma[i].pos.y = linha + 3;
                textbackground(RED);
                putchxy(coluna + 3, linha + 3, 'W');
                encontrado ++;
                i++;
            }
            coluna ++;
        }
        coluna = 0;
        linha ++;
    }

}

void movimenta_todos_fastasmas (FANTASMA fantasma[], char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    int i;
    srand(time(NULL));

    for(i = 0; i<NUM_FANTASMA; i++)
    {
        move_fantasma (&fantasma[i].pos.x, &fantasma[i].pos.y, matriz_lab);
    }
}

void le_labirinto (char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna;
    FILE* arq;

    arq = fopen("labirinto.txt", "r");

    for(linha = 0; linha < LINHA_LAB; linha ++)
    {
        for(coluna = 0; coluna < COLUNA_LAB; coluna ++)
        {
            matriz_lab[linha][coluna] = fgetc(arq);
        }

        matriz_lab[linha][coluna] = '\0';
    }

    fclose(arq);
}
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna;

    for(linha = 0; linha < LINHA_LAB; linha ++)
    {
        gotoxy(3, 3 + linha);
        for(coluna = 0; coluna < COLUNA_LAB; coluna ++)
        {
            printf("%c", matriz_lab[linha][coluna]);
        }
    }
}

void conta_bolacha ()
{

}
