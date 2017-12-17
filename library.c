#include "library.h"

/*
    Basicamente desenha as bordas do menu, colocando espaços em branco coloridos.
    Sendo elas maiores que as dimensões do jogo.
*/

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

/*
    Desenha uma entrada, com instruções de quais teclas usar e o que elas fazem.
*/

void entrada_jogo()
{
    gotoxy(50, 15);
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("START:");
    textbackground(BLACK);
    textcolor(YELLOW);
    gotoxy(40, 17);
    printf("Pressione enter para iniciar.");
    gotoxy(10, 5);
    printf("Teclas de movimento:");
    gotoxy(10, 7);
    printf("         W          ");
    gotoxy(10, 8);
    printf("    A         D     ");
    gotoxy(10, 9);
    printf("         S          ");
    gotoxy(60, 28);
    printf("Pressione X quando desejar parar o pacman");
    gotoxy(65, 29);
    printf("e P para pausar o jogo.");

}

/*
    Recebe atraves do kbhit uma tecla e define o que ela significa,
    usado na movimentação do pacman.
*/

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
        return PARA; //4
    else if(tecla == 'P')
        return PAUSE;//5
    return 9; //default
}

/*
    Recebe um jogador e uma matriz, a partir disso procura na matriz a posição em
    que o pacman(a letra 'C') se encontra e quando acha passa a posição para o jogador.
*/

void posicao_pacman(PACMAN *jogador, char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int encontrado = 0, linha = 0, coluna = 0;

    while(encontrado == 0 && linha < LINHA_LAB) //PASSA PELA MATRIZ ENQUANDO NÃO ACHA O PACMAN OU A MATRIZ NAO ACABA
    {
        while(encontrado == 0 && coluna < COLUNA_LAB)
        {
            if(matriz_lab[linha][coluna] == 'C') //QUANDO ACHA O PACMAN
            {
                jogador->pos.x = coluna + DESLOCAMENTO; //SALVA SUAS COORDENADAS
                jogador->pos.y = linha + DESLOCAMENTO;
                textbackground(YELLOW);
                putchxy(coluna + DESLOCAMENTO, linha + DESLOCAMENTO, 'C'); //PRINTA ELE NO LUGAR ACHADO
                encontrado = 1; //E FINALIZA O WHILE
            }
            coluna ++;
        }
        coluna = 0;
        linha ++;
    }

}

/*
    Recebe um jogador (para ter acesso as posicoes setadas no posicao_pacman e para modifica-lo
    atraves de ponteiros, para a proxima posicao), uma direção (recebida atraves do kbhit na main
    e traduzida pelo traduz_teclas) e a matriz (para passarmos para o testa parede para ver se na proxima
    posição do pacman vai ter parede ou nao). Basicamente vai excluindo o pacman da posicao antiga e
    desenhando na nova SE POSSÍVEL.
*/

int move_pacman (FANTASMA fantasma [], PACMAN *jogador, int direcao, int direcaoAnt, char matriz_lab[LINHA_LAB][COLUNA_LAB], int *bolachas_especiais, int *bolachas_normais)
{
    int xt, yt; //X E Y TEMPORARIOS
    int certo = 0; //MOSTRA SE O MOVIMENTO É POSSIVEL OU NÃO. SE FOR 1 QUER DIZER QUE É POSSIVEL E SE FOR 0 NÃO É POSSIVEL.
    //COMEÇA CONSIDERANDO QUE O MOVIMENTO NÃO É POSSIVEL, MUDANDO CASO PASSE PELOS TESTES.

    if(direcao == PARA) //SE A DIREÇÃO PASSADA FOR "PARA", NEM CONTINUA, APENAS O PRINTA NO MESMO LUGAR
    {
        textbackground(YELLOW);
        textcolor(BLACK);
        putchxy(jogador->pos.x, jogador->pos.y, 'C');
        textbackground(BLACK);
        certo = 1;
        atualiza_jogo (fantasma, jogador, matriz_lab, bolachas_normais, bolachas_especiais, direcao);
    }

    else //SENÃO EXECUTA TODA A FUNÇÃO
    {
        xt = jogador->pos.x;// USA VARIAVEIS TEMPORARIAS PARA FAZER OS TESTES FUTUROS
        yt = jogador->pos.y;

        textbackground(BLACK);

        atualiza_jogo (fantasma, jogador, matriz_lab, bolachas_normais, bolachas_especiais, direcao);

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

        /*
            Testa se no lugar futuro tera paredes.
            Caso não tiver entra no if e atribui as variaveis temporarias nas variaveis oficiais do pacman o printando depois no proximo espaço.
            E volta para a main retornando 1, mostrando que o movimento foi possível.
            Caso tiver, apenas o printa no mesmo lugar e volta pra main retornando 0, significando que o movimento não foi possivel
        */

        if(testa_parede(xt, yt, matriz_lab) == 1)
        {
            putchxy(jogador->pos.x, jogador->pos.y, ' ');
            jogador->pos.x = xt;
            jogador->pos.y = yt;
            certo = 1; // MOVIMENTO POSSIVEL
        }

        textbackground(YELLOW);
        textcolor(BLACK);
        putchxy(jogador->pos.x, jogador->pos.y, 'C');
        textbackground(BLACK);
    }
    gotoxy(1,1);

    return certo; // RETORNA SE O MOVIMENTO FOI POSSIVEL OU NÃO

}

void atualiza_jogo (FANTASMA fantasma [], PACMAN *jogador, char matriz_lab [LINHA_LAB][COLUNA_LAB], int *bolachas_normais, int *bolachas_especiais, int direcao)
{
    int continua_jogo; //VARIAVEL PARA SER USADA EM CASOS QUE O JOGADOR ACABA COM O NUMERO DE BOLACHAS E GANHA O JOGO

    if (jogador->pos.y - DESLOCAMENTO >= LINHA_LAB || jogador->pos.y - DESLOCAMENTO < 0 || jogador->pos.x - DESLOCAMENTO>= COLUNA_LAB || jogador->pos.x - DESLOCAMENTO < 0)
    {
        return;
    }

    /*
        Cada vez que o pacman come uma das bolachas põe um espaço em branco na matriz, senão o fantasma desenha de novo e em
        usos futuros da matriz pode apresentar problemas. Além disso, soma no score a potuação de cada uma e decrementa do total de bolachas uma.
        Tudo isso se havia uma bolacha na posição em que o pacman estava.
    */

    if(matriz_lab[jogador->pos.y - DESLOCAMENTO][jogador->pos.x - DESLOCAMENTO] == 'o') //cada vez que come uma bolachinha poe um espaço branco na matriz
    {
        matriz_lab[jogador->pos.y - DESLOCAMENTO][jogador->pos.x - DESLOCAMENTO] = ' ';//senao o fantasma desenha de novo.
        jogador->score = 10 + jogador->score;
        gotoxy(12, 1);
        textbackground(BLUE);
        textcolor(WHITE);
        printf("%d", jogador->score);
        textbackground(BLACK);
        (*bolachas_normais) -=1;
    }

    if(matriz_lab[jogador->pos.y - DESLOCAMENTO][jogador->pos.x - DESLOCAMENTO] == '*' )
    {
        matriz_lab[jogador->pos.y - DESLOCAMENTO][jogador->pos.x - DESLOCAMENTO] = ' ';
        jogador->score = 50 + jogador->score;
        gotoxy(12, 1);
        textbackground(BLUE);
        textcolor(WHITE);
        printf("%d", jogador->score);
        textbackground(BLACK);
        (*bolachas_especiais) -=1;
        jogador->poder = 1;
    }

    if(*bolachas_especiais < 1 && *bolachas_normais < 1) //TESTA SE AINDA TEM BOLACHAS NO JOGO
    {
        fflush(stdin);
        system("cmd /c cls"); //CASO NÃO TIVER, LIMPA A TELA E ACABA O JOGO
        textbackground(YELLOW);
        gotoxy(45, 20);
        printf("PARABENS, VOCE GANHOU!");
        gotoxy(47, 22);
        textbackground(BLACK);
        textcolor(YELLOW);
        printf("Seu score foi: %d", jogador->score); //PRINTA O SCORE
        gotoxy(41, 26);
        printf("Pressione enter para continuar");
        do
        {
            continua_jogo = getch(); //ESPERA ATÉ QUE O JOGADOR APERTE ENTER PARA CONTINUAR
        }
        while(continua_jogo != 13);
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
    int x, y; // COORDENADAS TEMPORARIAS

    x = fantasma->pos.x;//SALVA AS COORDENADAS DO PACMAN EM VARIAVEIS TEMPORARIAS
    y = fantasma->pos.y;

    textbackground(BLACK);
    if (y-DESLOCAMENTO >= LINHA_LAB || y-DESLOCAMENTO < 0 || x-DESLOCAMENTO>= COLUNA_LAB || x-DESLOCAMENTO < 0)
    {
        return;
    }
    /*
        Fantasma sempre printa atrás dele exatamente o que tinha na matriz no momento em que passou por cima.
    */

    if(matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == 'o' )
    {
        textcolor(WHITE);
        putchxy(x, y, 'o');

    }
    if(matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == '*')
    {
        textcolor(WHITE);
        putchxy(x, y, '*');
    }

    if(matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == ' ' || matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == 'W' || matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == 'C' )
    {
        putchxy(x, y, ' ');
    }

    textcolor(BLACK);

    direcao_movimento_fantasma(fantasma, matriz_lab, jogador); //AQUI É ONDE REALMENTE FAZ TODA A PARTE DE DIRECIONAMENTO DOS FANTASMAS, QUANDO RETORNA SO FAZ O MOVIMENTO

    textbackground(RED);
    if(jogador->poder == 1)
    {
        textbackground(GREEN);
        putchxy(fantasma->pos.x, fantasma->pos.y, 'w');// PRINTA O FANTASMA NA NOVA POSIÇÃO COMO 'w'  SE O PODER DO PACMAN ESTA ATIVADO
    }
    else
    {
        putchxy(fantasma->pos.x, fantasma->pos.y, 'W'); //OU COMO 'W' SE O PODER DO PACMAN ESTA DESATIVADO
    }
    textbackground(BLACK);

}

/*
    Testa se no determinado x e y tem '#' (parede) ou se esta nos limites do mapa
*/
int testa_parede (int x, int y, char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    if(x>101 || y>31 || x <= 2 || y <= 3 || matriz_lab[y-DESLOCAMENTO][x-DESLOCAMENTO] == '#')
        return 0;

    else
        return 1;
}


void direcao_movimento_fantasma (FANTASMA *fantasma, char matriz_lab [LINHA_LAB][COLUNA_LAB], PACMAN *jogador)
{
    int xt = fantasma->pos.x, yt = fantasma->pos.y, sorteia_decisao, move = 0;

    while(move == 0)
    {
        xt = fantasma->pos.x;
        yt = fantasma->pos.y;

        if (testa_bifurcacao (fantasma->dir_fant, fantasma->pos.x, fantasma->pos.y, matriz_lab) == 1)
        {
            sorteia_decisao = rand() %100;

            if(jogador->poder == 1)
            {
                if(sorteia_decisao > PROBDIRECAOFANTASMA)
                {
                    fantasma->dir_fant = fantasma->dir_fant = calcula_menor_distancia(jogador, fantasma);
                }
                else
                {
                    fantasma->dir_fant = rand() %4 ;
                }
            }
            else
            {
                if(sorteia_decisao < PROBDIRECAOFANTASMA)
                {
                    fantasma->dir_fant = fantasma->dir_fant = calcula_menor_distancia(jogador, fantasma);
                }
                else
                {
                    fantasma->dir_fant = rand() %4 ;
                }
            }

        }

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

        if(((testa_parede(xt, yt, matriz_lab)) == 1))//so pode entrar aqui quando esse teste der true, e o de outra direçao existente, q seja contraria a essa tbm
        {
            fantasma->pos.x = xt;
            fantasma->pos.y = yt;
            move = 1;
        }
        else //so sorteia uma nova direcao pro fantasma se tiver uma parede
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
        }
    }
}


int testa_bifurcacao (int dir_fant, int xt, int yt, char matriz_lab [LINHA_LAB][COLUNA_LAB])
{
    int num_caminhos = 0; //tenta ver se o num_caminhos é maior de dois (oq define uma bifurcação)

    xt ++; //testa se para a direita tem bifurcacao.

    if((testa_parede(xt, yt, matriz_lab)) == 1)
    {
        num_caminhos ++; //se entrou aqui quer dizer que nao tem parede para este lado entao soma 1
    }

    xt --; // volta original

    xt --; //testa se para a esquerda tem bifurcacao.
    if((testa_parede(xt, yt, matriz_lab)) == 1)
    {
        num_caminhos ++;
    }
    xt++; //volta para a original novamente


    yt --; //testa se para cima tem bifurcacao

    if((testa_parede(xt, yt, matriz_lab)) == 1)
    {
        num_caminhos ++;
    }

    yt ++; //volta ao original

    yt ++; //testa se para baixo tem bifurcacao

    if((testa_parede(xt, yt, matriz_lab)) == 1)
    {
        num_caminhos ++;
    }

    yt --;//volta ao original

    if(num_caminhos>2)
    {
        return 1; //numero de caminhos disponiveis maior que 1, retorna true
    }
    else
    {
        return 0;
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

void gerador_fantasma (FANTASMA fantasma[], char matriz_lab[LINHA_LAB][COLUNA_LAB], COORDENADA pos_iniciais_fantasmas [])
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
                fantasma[i].pos.x = coluna + DESLOCAMENTO;
                pos_iniciais_fantasmas[i].x = coluna + DESLOCAMENTO; //guarda a posicao x em que o fantasma nasceu
                fantasma[i].pos.y = linha + DESLOCAMENTO;
                pos_iniciais_fantasmas[i].y = linha + DESLOCAMENTO;//guarda a posicao y em que o fantasma nasceu
                textbackground(RED);
                putchxy(coluna + DESLOCAMENTO, linha + DESLOCAMENTO, 'W');
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
    if(arq == NULL)
    {
        return;
    }

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
        gotoxy(DESLOCAMENTO, DESLOCAMENTO + linha);
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
            if(matriz_lab[linha][coluna] == 'o')
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
            if(matriz_lab[linha][coluna] == '*')
                bolachas_especiais ++;
        }
    }

    return bolachas_especiais;
}

/*
    Recebe um jogador e os cinco fantasmas, testando um por um se estao na mesma posicao que o jogador.
    Caso estejam o pacman perde uma vida, aprecendo uma mensagem na tela. Se for a ultima vida do pacman, chama a função
    game_over e o while da função main fica falso, acabando o jogo.
*/
void testa_se_fantasma_comeu_pacman(PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB])
{
    int i, continua_jogo = 0;

    for(i = 0; i < NUM_FANTASMA; i++)
    {
        if(jogador -> pos.y == fantasma[i].pos.y && jogador -> pos.x == fantasma[i].pos.x) //TESTA SE ESTÃO NA MESMA POSIÇÃO
        {
            system("cls"); //CASO ESTIVEREM, LIMPA A TELA
            jogador->vidas --; //DIMINUI O NUMERO DE VIDAS DO PACMAN

            if(jogador->vidas <= 0) //TESTA SE ERA A ÚLTIMA VIDA DO PACMAN
            {
                game_over (jogador); //SE ERA ACABOU O JOGO
            }
            else //SENÃO TEM A OPÇÃO DE CONTINUAR
            {
                gotoxy(12, 8);
                textbackground(YELLOW);
                textcolor(BLACK);
                printf("VC MORREU, TEM MAIS %d VIDA(S).", jogador->vidas);
                gotoxy(60, 28);
                printf("Pressione enter para continuar.");
                desenha_menu();
                textbackground(BLACK);
                textcolor(WHITE);
            }

            do
            {
                continua_jogo = getch(); //ESPERA ATÉ QUE O JOGADOR APERTE ENTER PARA CONTINUAR O JOGO
                if(continua_jogo == 13)
                {
                    printa_labirinto(matriz_lab); //PRINTA O LABIRINTO DE NOVO
                    posicao_pacman(jogador, matriz_lab); //PÕE O PACMAN NA POSIÇÃO INICIAL
                    textbackground(BLUE);
                    gotoxy(32, 1);
                    printf("%d", jogador->vidas); //PRINTA A VIDA
                    gotoxy(12, 1);
                    printf("%d", jogador->score); //RINTA O SCORE
                    textbackground(BLACK);
                }
            }
            while (continua_jogo != 13);

        }
    }
}

void testa_se_pacman_comeu_fantasma (PACMAN *jogador, FANTASMA fantasma [], char matriz_lab[LINHA_LAB][COLUNA_LAB], COORDENADA pos_iniciais_fantasmas [])
{
    int i;

    for(i = 0; i < NUM_FANTASMA; i++) //TESTA SE ALGUM DOS FANTASMAS ESTA NA MESMA POSIÇÃO QUE O PACMAN
    {
        if(jogador -> pos.y == fantasma[i].pos.y && jogador -> pos.x == fantasma[i].pos.x)//CASO ESTIVER
        {
            textbackground(GREEN);
            putchxy(pos_iniciais_fantasmas[i].x, pos_iniciais_fantasmas[i].y, 'w');
            fantasma[i].pos.x = pos_iniciais_fantasmas[i].x; //PÕE O FANTASMA COM SUAS COORDENADAS INICIAIS
            fantasma[i].pos.y = pos_iniciais_fantasmas[i].y;
            jogador->score = jogador->score + 200; //DA MAIS 200 PONTOS NO SCORE DO PACMAN
            gotoxy(12, 1);
            textbackground(BLUE);
            printf("%d", jogador->score);
            textbackground(BLACK);
        }
    }
}

void game_over (PACMAN *jogador)//QUANDO ACABAM AS VIDAS DO JOGADOR
{
    gotoxy(48, 18);
    textbackground(YELLOW);
    textcolor(BLACK);
    printf("ACABARAM SUAS VIDAS.");
    gotoxy(49, 20);
    textbackground(BLACK);
    textcolor(YELLOW);
    printf("Seu score foi: %d", jogador->score); //PRINTA O SCORE
    gotoxy(43, 28);
    printf("Pressione enter para continuar."); //E VAI PRA MAIN
    textcolor(WHITE);
}

