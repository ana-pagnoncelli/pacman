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
    else if(tecla == 'X')
        return PARA;
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

int move_pacman (PACMAN *jogador, int direcao, int direcaoAnt, char matriz_lab[LINHA_LAB][COLUNA_LAB], int *bolachas_especiais, int *bolachas_normais)
{
    int xt, yt; //x e y temporarios.
    int certo = 0;

    if(direcao == PARA)
    {
        textbackground(YELLOW);
        putchxy(jogador->pos.x, jogador->pos.y, 'C');
        textbackground(BLACK);
        certo = 1;
    }

    else
    {
        xt = jogador->pos.x;
        yt = jogador->pos.y;

        textbackground(BLACK);

        atualiza_jogo (jogador, matriz_lab, bolachas_normais, bolachas_especiais);

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
            putchxy(jogador->pos.x, jogador->pos.y, ' ');
            jogador->pos.x = xt;
            jogador->pos.y = yt;
            certo = 1;
        }

        textbackground(YELLOW);
        putchxy(jogador->pos.x, jogador->pos.y, 'C');
        textbackground(BLACK);
    }
    gotoxy(1,1);
    return certo;

}

void atualiza_jogo (PACMAN *jogador, char matriz_lab [LINHA_LAB][COLUNA_LAB], int *bolachas_normais, int *bolachas_especiais)
{
    int continua_jogo;

    if(matriz_lab[jogador->pos.y - 3][jogador->pos.x - 3] == 'o') //cada vez que come uma bolachinha poe um espaço branco na matriz
        {
            matriz_lab[jogador->pos.y - 3][jogador->pos.x - 3] = ' ';//senao o fantasma desenha de novo.
            jogador->score = 10 + jogador->score;
            gotoxy(12, 1);
            textbackground(BLUE);
            printf("%d", jogador->score);
            textbackground(BLACK);
            bolachas_normais --;
        }

        if(matriz_lab[jogador->pos.y - 3][jogador->pos.x - 3] == '*' )
        {
            matriz_lab[jogador->pos.y - 3][jogador->pos.x - 3] = ' ';
            jogador->score = 50 + jogador->score;
            gotoxy(12, 1);
            textbackground(BLUE);
            printf("%d", jogador->score);
            textbackground(BLACK);
            bolachas_especiais --;
        }

        if(bolachas_especiais == 0 && bolachas_normais == 0)
       {
           system("cls");
           printf("vc ganhou, otario.");
            continua_jogo = getch();
        }
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


void move_fantasma (FANTASMA *fantasma, char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador)
{
    int x, y;

    x = fantasma->pos.x ;
    y = fantasma->pos.y;




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

    direcao_movimento_fantasma(fantasma, matriz_lab, jogador);

    textbackground(RED);
    putchxy(fantasma->pos.x, fantasma->pos.y, 'W');
    textbackground(BLACK);

}


int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    if(x>103 || y>32 || x <= 2 || y <= 3 || matriz_lab[y-3][x-3] == '#')
        return 0;

    else
        return 1;
}


void direcao_movimento_fantasma (FANTASMA *fantasma, char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador)
{
    int xt = fantasma->pos.x, yt = fantasma->pos.y, sorteia_decisao;

    switch(fantasma->dir_fant)
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
    if(testa_parede(xt, yt, matriz_lab) == 1)//so pode entrar aqui quando esse teste der true, e o de outra direçao existente, q seja contraria a essa tbm
    {
        fantasma->pos.x = xt;
        fantasma->pos.y = yt;
    }
    else //so sorteia uma nova direcao pro fantasma se tiver uma parede ou uma bifurcação
    {
    sorteia_decisao = rand() %2;
    if(sorteia_decisao == 0)
    {
       fantasma->dir_fant = rand() %4 ;
    }
    else
    {
        fantasma->dir_fant = calcula_menor_distancia(jogador, fantasma);
    }

    direcao_movimento_fantasma (fantasma, matriz_lab, jogador);
    }
}

float calculo_da_distancia(int x_pac, int y_pac, int x_fant, int y_fant)
{
    float resultado;

    resultado = (sqrt ((pow((x_pac - x_fant), 2)) - (pow((y_pac - y_fant), 2))));

    return resultado;
}

int calcula_menor_distancia(PACMAN *jogador, FANTASMA *fantasma)
{
    int direcao;
    float distancia;


    direcao = CIMA;
    fantasma->pos.y --; //tenta calcular CIMA, ja supondo que e a menor
    distancia = calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y );

    fantasma->pos.y ++;//retorna ao original pra testar a proxima direcao

    fantasma->pos.x++; //tenta calcular DIREITA, ver se é menor que CIMA.

    if(distancia > calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y ))
    {
        distancia = calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y );
        direcao = DIREITA;
    }

    fantasma->pos.x --; //retorna ao original novamente pra testar a proxima

    fantasma->pos.y ++; //tenta ver se BAIXO, é menor que os anteriores

    if(distancia > calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y ))
    {
        distancia = calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y );
        direcao = BAIXO;
    }

    fantasma->pos.y --; //retorna ao valor original novamente para testar a ultima

    fantasma->pos.x --; //testa se a ESQUERDA é a menor que as anteriores

    if(distancia > calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y ))
    {
        distancia = calculo_da_distancia(jogador->pos.x, jogador->pos.y, fantasma->pos.x, fantasma->pos.y );
        direcao = ESQUERDA;
    }

    fantasma->pos.x ++;

    return direcao; //retorna a direcao final.
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

void movimenta_todos_fastasmas (FANTASMA fantasma[], char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador)
{
    int i;
    srand(time(NULL));

    for(i = 0; i<NUM_FANTASMA; i++)
    {
        move_fantasma (&fantasma[i], matriz_lab, jogador);
    }
}

/*
Salva o labirinto.txt em em uma matriz.
*/
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
/*
Printa o labirinto que foi salvo na matriz, ao mesmo tempo colorindo as paredes e bolachas e tirando os W e C da tela,
para que quando a funcao for chamada novamente nao printe eles.
*/
void printa_labirinto(char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna;

    for(linha = 0; linha < LINHA_LAB; linha ++)
    {
        gotoxy(3, 3 + linha);
        for(coluna = 0; coluna < COLUNA_LAB; coluna ++)
        {
            if(matriz_lab[linha][coluna] != 'W' && matriz_lab[linha][coluna] != 'C')
            {
                if(matriz_lab[linha][coluna] == '#')
                {
                    textcolor(BLUE);
                }
                printf("%c", matriz_lab[linha][coluna]);
                textcolor(WHITE);
            }
            else
            {
                textcolor(BLACK);
                printf("%c", matriz_lab[linha][coluna]);
                textcolor(WHITE);
            }

        }
    }
}

/*
Conta a quantidade de bolachas normais no mapa, passando um for pela matriz toda.
Quando acaba, devolve o valor para a main.
*/
int conta_bolachas_normais (char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna, bolachas_normais = 0;

    for(linha = 0; linha < LINHA_LAB; linha ++)
    {
        for(coluna = 0; coluna < COLUNA_LAB; coluna ++)
        {
            if(matriz_lab[linha][coluna] == 'o');
            bolachas_normais ++;
        }
    }

    return bolachas_normais;
}

/*
Conta a quantidade de bolachas especiais no mapa, passando um for pela matriz toda.
Quando acaba, devolve o valor para a main.
*/

int conta_bolachas_especiais (char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int linha, coluna, bolachas_especiais = 0;

    for(linha = 0; linha < LINHA_LAB; linha ++)
    {
        for(coluna = 0; coluna < COLUNA_LAB; coluna ++)
        {
            if(matriz_lab[linha][coluna] == '*');
            bolachas_especiais ++;
        }
    }

    return bolachas_especiais;
}

/*
Recebe um jogador e os cinco fantasmas, testando um por um se estao na mesma posicao que o jogador.
Caso estejam o pacman perde uma vida, aprecendo uma mensagem na tela. Se for a ultima vida do pacman, chama a função
game_over e o while da função main fica falso, acabando o jogo. Se tiver ainda vidas, apertando enter vc continua
partindo da posicao inicial, setada pela chamada da funcao posicao_pacman.
*/
void testa_se_fantasma_comeu_pacman(PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int i, continua_jogo = 0;

    for(i = 0; i < NUM_FANTASMA; i++)
    {
        if(jogador -> pos.y == fantasma[i].pos.y && jogador -> pos.x == fantasma[i].pos.x) //testa se estao na mesma posicao
        {
            system("cls");
            jogador->vidas --; //atualiza a quantidade de vidas

            if(jogador->vidas == 0) //testa se era a ultima vida do pacman
            {
                game_over (); //se era acabou o jogo
            }
            else //senao continua
            {

                gotoxy(50, 15);
                textbackground(YELLOW);
                textcolor(BLACK);
                printf("VC MORREU, TEM MAIS %d VIDAS.", jogador->vidas);
                desenha_menu();
                textbackground(BLACK);
                textcolor(WHITE);

                continua_jogo = getch();
                if(continua_jogo == 13)
                {
                    printa_labirinto(matriz_lab);
                    posicao_pacman(jogador, matriz_lab); //seta o pacman na posicao inicial
                    textbackground(BLUE);
                    gotoxy(32, 1);
                    printf("%d", jogador->vidas);
                    textbackground(BLACK);
                }
            }
        }
    }

}

void game_over ()
{
    gotoxy(50, 15);
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("ACABOU.");
    textbackground(BLACK);
    textcolor(WHITE);
}

