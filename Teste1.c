/*
    ============================================================
                    JOGO DA CALCULADORA
    ============================================================

    TECLAS DO JOGO:

    1 ou 3 -> Escolher personagem
    2      -> Andar para a esquerda
    6      -> Andar para a direita
    8      -> Binóculo
    X      -> Tesouro
    5      -> Cobra
    7      -> Foice
    9      -> Machado
    4      -> Bumerangue
    =      -> Pontuação final

    OBJETIVO:

    1. Escolher um personagem.
    2. Começar em uma posição aleatória.
    3. Encontrar o binóculo.
    4. O binóculo revela o tesouro.
    5. Encontrar o tesouro.
    6. Enfrentar a cobra.
    7. Escolher uma arma.
    8. Somar os pontos.
    9. Mostrar a pontuação final.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
    ============================================================
                        CONSTANTES
    ============================================================
*/

/* Quantidade de posições da trilha */
#define TAMANHO_TRILHA 6

/* Teclas de movimentação */
#define ESQUERDA 2
#define DIREITA 6

/* Teclas das armas */
#define FOICE 7
#define MACHADO 9
#define BUMERANGUE 4


/*
    ============================================================
                    FUNÇÃO MOSTRAR TRILHA
    ============================================================

    Mostra a trilha na tela.

    O jogador é representado pelo número do personagem.

    Exemplo:

    [ . X . 1 . . ]

    Nesse exemplo, o personagem 1 está na posição 3.
*/
void mostrarTrilha(char trilha[], int posJogador, int personagem)
{
    int i;

    printf("\nTrilha: [ ");

    /*
        Percorre todas as posições da trilha.
    */
    for (i = 0; i < TAMANHO_TRILHA; i++)
    {
        /*
            Se a posição atual for a posição do jogador,
            mostramos o personagem.
        */
        if (i == posJogador)
        {
            printf("%d ", personagem);
        }
        else
        {
            /*
                Caso contrário, mostramos o que existe
                naquela posição.
            */
            printf("%c ", trilha[i]);
        }
    }

    printf("]\n");
}


/*
    ============================================================
                    FUNÇÃO ESCOLHER PERSONAGEM
    ============================================================

    O jogador pode escolher:

    1 -> Personagem 1
    3 -> Personagem 3
*/
int escolherPersonagem()
{
    int personagem;

    printf("\nEscolha seu personagem:\n");
    printf("[1] Personagem 1\n");
    printf("[3] Personagem 3\n");

    do
    {
        printf("> ");
        scanf("%d", &personagem);

        /*
            Verifica se a opção é válida.
        */
        if (personagem != 1 && personagem != 3)
        {
            printf("Opcao invalida! Escolha 1 ou 3.\n");
        }

    } while (personagem != 1 && personagem != 3);

    return personagem;
}


/*
    ============================================================
                    FUNÇÃO SORTEAR POSIÇÕES
    ============================================================

    Esta função sorteia três posições:

    - Jogador
    - Binóculo
    - Tesouro

    IMPORTANTE:

    As três posições precisam ser diferentes.

    Exemplo válido:

    [ J . 8 . X . ]

    Exemplo inválido:

    [ J . 8 X . . ] -> válido

    [ J . 8 . 8 . ] -> inválido
*/
void sortearPosicoes(
    int *posJogador,
    int *posBinoculo,
    int *posTesouro
)
{
    /*
        ========================================================
                    SORTEAR JOGADOR
        ========================================================

        rand() % 6 gera um número entre:

        0, 1, 2, 3, 4 e 5.
    */
    *posJogador = rand() % TAMANHO_TRILHA;


    /*
        ========================================================
                    SORTEAR BINÓCULO
        ========================================================

        Sorteamos o binóculo.
    */
    *posBinoculo = rand() % TAMANHO_TRILHA;


    /*
        O binóculo não pode ficar no mesmo lugar
        que o jogador.
    */
    while (*posBinoculo == *posJogador)
    {
        *posBinoculo = rand() % TAMANHO_TRILHA;
    }


    /*
        ========================================================
                    SORTEAR TESOURO
        ========================================================

        Sorteamos o tesouro.
    */
    *posTesouro = rand() % TAMANHO_TRILHA;


    /*
        O tesouro não pode ficar:

        1. Na posição do jogador.
        2. Na posição do binóculo.
    */
    while (*posTesouro == *posJogador ||
           *posTesouro == *posBinoculo)
    {
        *posTesouro = rand() % TAMANHO_TRILHA;
    }
}


/*
    ============================================================
                    FUNÇÃO JOGAR NA TRILHA
    ============================================================
*/
int jogarNaTrilha(
    char trilha[],
    int *posJogador,
    int posBinoculo,
    int posTesouro,
    int personagem,
    int *pontuacao
)
{
    int movimento;

    /*
        Indica se o jogador já encontrou o binóculo.

        0 = não encontrou
        1 = encontrou
    */
    int achouBinoculo = 0;


    /*
        Indica se o jogador já encontrou o tesouro.

        0 = não encontrou
        1 = encontrou
    */
    int achouTesouro = 0;


    /*
        Coloca o binóculo na trilha.
    */
    trilha[posBinoculo] = '8';


    printf("\n====================================\n");
    printf("          AVENTURA INICIADA!\n");
    printf("====================================\n");

    printf("\nUse %d para andar para a esquerda.\n",
           ESQUERDA);

    printf("Use %d para andar para a direita.\n",
           DIREITA);

    printf("\nEncontre o binoculo (8) para revelar");
    printf(" o tesouro!\n");


    /*
        Continua enquanto o tesouro não for encontrado.
    */
    while (!achouTesouro)
    {
        /*
            Mostra a trilha.
        */
        mostrarTrilha(
            trilha,
            *posJogador,
            personagem
        );


        /*
            Mostra a posição atual.
        */
        printf("Posicao atual: %d\n", *posJogador);

        printf("Escolha %d ou %d: ",
               ESQUERDA,
               DIREITA);

        scanf("%d", &movimento);


        /*
            ====================================================
                    ANDAR PARA A ESQUERDA
            ====================================================
        */
        if (movimento == ESQUERDA)
        {
            /*
                Verifica se não estamos na primeira
                posição.
            */
            if (*posJogador > 0)
            {
                (*posJogador)--;

                printf("Voce andou para a esquerda.\n");
            }
            else
            {
                printf("Voce ja esta no inicio da trilha!\n");
            }
        }


        /*
            ====================================================
                    ANDAR PARA A DIREITA
            ====================================================
        */
        else if (movimento == DIREITA)
        {
            /*
                Verifica se não estamos na última
                posição.
            */
            if (*posJogador < TAMANHO_TRILHA - 1)
            {
                (*posJogador)++;

                printf("Voce andou para a direita.\n");
            }
            else
            {
                printf("Voce ja esta no final da trilha!\n");
            }
        }


        /*
            ====================================================
                    MOVIMENTO INVÁLIDO
            ====================================================
        */
        else
        {
            printf("\nMovimento invalido!\n");
            printf("Use somente %d ou %d.\n",
                   ESQUERDA,
                   DIREITA);

            continue;
        }


        /*
            ====================================================
                    VERIFICAR BINÓCULO
            ====================================================
        */

        if (!achouBinoculo &&
            *posJogador == posBinoculo)
        {
            /*
                O jogador encontrou o binóculo.
            */
            achouBinoculo = 1;


            /*
                Remove o binóculo da trilha.
            */
            trilha[posBinoculo] = '.';


            /*
                Revela o tesouro.
            */
            trilha[posTesouro] = 'X';


            printf("\n====================================\n");
            printf("        BINOCULO ENCONTRADO!\n");
            printf("====================================\n");

            printf("O tesouro foi revelado!\n");
        }


        /*
            ====================================================
                    VERIFICAR TESOURO
            ====================================================
        */

        if (achouBinoculo &&
            *posJogador == posTesouro)
        {
            /*
                O tesouro foi encontrado.
            */
            achouTesouro = 1;


            /*
                Adiciona 50 pontos.
            */
            *pontuacao += 50;


            printf("\n====================================\n");
            printf("          TESOURO ENCONTRADO!\n");
            printf("====================================\n");

            printf("+50 pontos!\n");

            printf("Pontuacao atual: %d\n",
                   *pontuacao);
        }
    }


    return achouTesouro;
}


/*
    ============================================================
                    FUNÇÃO ESCOLHER ARMA
    ============================================================
*/
int escolherArma()
{
    int arma;

    printf("\n====================================\n");
    printf("            ESCOLHA SUA ARMA\n");
    printf("====================================\n");

    printf("[7] Foice\n");
    printf("[9] Machado\n");
    printf("[4] Bumerangue\n");

    do
    {
        printf("> ");
        scanf("%d", &arma);

        if (arma != FOICE && arma != MACHADO && arma != BUMERANGUE)
        {
            printf("Arma invalida!\n");
            printf("Escolha 7, 9 ou 4.\n");
        }

    } while (arma != FOICE && arma != MACHADO && arma != BUMERANGUE);

    return arma;
}


/*
    ============================================================
                    FUNÇÃO CALCULAR DANO
    ============================================================

    Foice      -> 20 de dano
    Machado    -> 30 de dano
    Bumerangue -> 15 de dano
*/
int calcularDano(int arma)
{
    if (arma == MACHADO)
    {
        return 30;
    }
    else if (arma == FOICE)
    {
        return 20;
    }
    else
    {
        return 15;
    }
}


/*
    ============================================================
                    FUNÇÃO BATALHA
    ============================================================
*/
void batalha(int *pontuacao)
{
    int arma, dano;


    /*
        Apresenta o inimigo.
    */
    printf("\n====================================\n");
    printf("       UMA COBRA GIGANTE APARECEU!\n");
    printf("                    5\n");
    printf("====================================\n");


    /*
        Jogador escolhe uma arma.
    */
    arma = escolherArma();


    /*
        Calcula o dano.
    */
    dano = calcularDano(arma);


    /*
        Mostra o ataque.
    */
    printf("\nVoce atacou a cobra!\n");
    printf("Dano causado: %d\n", dano);


    /*
        Soma o dano à pontuação.
    */
    *pontuacao += dano;


    /*
        Verifica se a cobra foi derrotada.
    */
    if (dano >= 20)
    {
        printf("\nA cobra foi derrotada!\n");
        printf("Voce venceu o jogo!\n");
    }
    else
    {
        printf("\nA cobra ficou ferida.\n");
        printf("Voce escapou com o tesouro!\n");
    }


    /*
        Mostra a pontuação depois da batalha.
    */
    printf("\nPontuacao apos a batalha: %d\n",
           *pontuacao);
}


/*
    ============================================================
                        FUNÇÃO MAIN
    ============================================================

    É aqui que o programa começa.
*/
int main()
{
    /*
        ========================================================
                    CRIAR A TRILHA
        ========================================================

        A trilha possui 6 posições.

        Inicialmente:

        [ . . . . . . ]
    */
    char trilha[TAMANHO_TRILHA] = {'.', '.', '.', '.', '.', '.'};


    /*
        ========================================================
                    VARIÁVEIS
        ========================================================
    */

    /*
        Agora o jogador também terá uma posição
        sorteada aleatoriamente.
    */
    int posJogador;


    /*
        Posição do binóculo.
    */
    int posBinoculo;


    /*
        Posição do tesouro.
    */
    int posTesouro;


    /*
        Personagem escolhido.
    */
    int personagem;


    /*
        Pontuação começa em zero.
    */
    int pontuacao = 0;


    /*
        ========================================================
                INICIAR NÚMEROS ALEATÓRIOS
        ========================================================

        time(NULL) pega o horário atual.

        srand() usa esse horário para criar uma
        sequência diferente de números aleatórios
        a cada partida.
    */
    srand(time(NULL));


    /*
        ========================================================
                        TÍTULO
        ========================================================
    */

    printf("====================================\n");
    printf("       JOGO DA CALCULADORA\n");
    printf("====================================\n");


    /*
        ========================================================
                    ESCOLHER PERSONAGEM
        ========================================================
    */

    personagem = escolherPersonagem();


    /*
        ========================================================
                SORTEAR AS TRÊS POSIÇÕES
        ========================================================

        Agora:

        - jogador tem uma posição aleatória;
        - binóculo tem uma posição aleatória;
        - tesouro tem uma posição aleatória.

        E nenhuma das três posições será igual.
    */
    sortearPosicoes(&posJogador, &posBinoculo, &posTesouro);


    /*
        Mostra que o personagem começou em uma posição aleatória. Isso ajuda o jogador a entender o jogo.
    */
    printf("\n====================================\n");
    printf("          AVENTURA INICIADA!\n");
    printf("====================================\n");

    printf("Seu personagem comecou na ");
    printf("posicao %d.\n", posJogador);

    printf("O binoculo esta escondido na trilha.\n");
    printf("Encontre-o para revelar o tesouro!\n");


    /*
        ========================================================
                    JOGAR NA TRILHA
        ========================================================
    */

    jogarNaTrilha(trilha,&posJogador,posBinoculo,posTesouro,personagem,&pontuacao);


    /*
        ========================================================
                    BATALHA CONTRA A COBRA
        ========================================================
    */

    batalha(&pontuacao);


    /*
        ========================================================
                    PONTUAÇÃO FINAL
        ========================================================
    */

    printf("\n");
    printf("====================================\n");
    printf("          (=) RESULTADO FINAL\n");
    printf("====================================\n");

    printf("Pontuacao final: %d pontos\n",
           pontuacao);

    printf("====================================\n");
    printf("             FIM DO JOGO!\n");
    printf("====================================\n");


    /*
        O programa terminou corretamente.
    */
    return 0;
}
