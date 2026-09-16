/*
    Teclas do jogo:
      1 ou 3 -> escolha do personagem
      2 / 6  -> mover na trilha (esquerda / direita)
      8      -> binoculo (revela onde esta o tesouro)
      X      -> tesouro
      5      -> cobra (inimigo final)
      7/9/4  -> foice / machado / bumerangue (armas)
      =      -> soma da pontuacao final
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char trilha[6] = {'.', '.', '.', '.', '.', '.'};
    int posJogador = 0, posBinoculo, posTesouro, achouBinoculo = 0, achouTesouro = 0, personagem, movimento, arma, dano, pontuacao = 0, i;
    srand(time(NULL)); /* "embaralha" os numeros aleatorios a cada partida */

    printf("=== JOGO DA CALCULADORA ===\n\n");

    /* ---------------------------------------------------
       PASSO 1: o jogador escolhe o personagem
       --------------------------------------------------- */
    printf("Escolha seu personagem:\n");
    printf("[1] Personagem 1\n");
    printf("[3] Personagem 3\n");
    printf("> ");
    scanf("%d", &personagem);

    /* ---------------------------------------------------
       PASSO 2: sorteia onde ficam o binoculo e o tesouro
       --------------------------------------------------- */
    posBinoculo = rand() % 6;    
    posTesouro = rand() % 6;
    while (posTesouro == posBinoculo) {
        posTesouro = rand() % 6;
    }
    trilha[posBinoculo] = '8';

    printf("\nUse 2 para ir para esquerda e 6 para ir para direita.\n");
    printf("Ache o binoculo (8) para descobrir onde esta o tesouro (X)!\n");

    /* ---------------------------------------------------
       PASSO 3: o jogador anda pela trilha ate achar o tesouro
       --------------------------------------------------- */
    while (achouTesouro == 0) {

        /* desenha a trilha na tela */
        printf("\n[ ");
        for (i = 0; i < 6; i++) {
            if (i == posJogador) {
                printf("%d ", personagem); /* mostra o jogador */
            } else {
                printf("%c ", trilha[i]);  /* mostra o que tem na trilha */
            }
        }
        printf("]\n");

        printf("Posicao: %d | Escolha 2 ou 6: ", posJogador);
        scanf("%d", &movimento);

        if (movimento == 2 && posJogador > 0) {
            posJogador = posJogador - 1; /* anda para esquerda */
        }
        if (movimento == 6 && posJogador < 5) {
            posJogador = posJogador + 1; /* anda para direita */
        }

        /* chegou no binoculo? */
        if (achouBinoculo == 0 && posJogador == posBinoculo) {
            achouBinoculo = 1;
            trilha[posBinoculo] = '.';
            trilha[posTesouro] = 'X'; /* revela o tesouro na trilha */
            printf("\n>> Binoculo encontrado! O tesouro apareceu na trilha.\n");
        }

        /* chegou no tesouro? (so conta depois de achar o binoculo) */
        if (achouBinoculo == 1 && posJogador == posTesouro) {
            achouTesouro = 1;
            pontuacao = pontuacao + 50;
            printf("\n>> Voce encontrou o tesouro! +50 pontos.\n");
        }
    }

    /* ---------------------------------------------------
       PASSO 4: batalha contra a cobra
       --------------------------------------------------- */
    printf("\nUma cobra gigante (5) apareceu para proteger o tesouro!\n");
    printf("Escolha sua arma:\n");
    printf("[7] Foice\n[9] Machado\n[4] Bumerangue\n> ");
    scanf("%d", &arma);

    if (arma == 9) {
        dano = 30; /* machado: dano alto */
    } else if (arma == 7) {
        dano = 20; /* foice: dano medio */
    } else {
        dano = 15; /* bumerangue: dano baixo */
    }

    printf("\nVoce ataca a cobra e causa %d de dano!\n", dano);
    pontuacao = pontuacao + dano;

    if (dano >= 20) {
        printf("A cobra foi derrotada! Voce venceu o jogo!\n");
    } else {
        printf("A cobra ficou ferida, mas voce escapou com o tesouro!\n");
    }

    /* ---------------------------------------------------
       PASSO 5: mostra a pontuacao final
       --------------------------------------------------- */
    printf("\n===========================\n");
    printf("(=) PONTUACAO FINAL: %d\n", pontuacao);
    printf("===========================\n");

    return 0;
}
