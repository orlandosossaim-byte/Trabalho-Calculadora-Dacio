/*
    Teclas do jogo:
      1 ou 3 -> escolha do personagem
      2 / 6  -> mover na trilha (esquerda / direita)
      8      -> binoculo (revela onde esta o tesouro)
      X      -> tesouro
      5      -> cobra (boss final)
      7/9/4  -> foice / machado / bumerangue (armas contra a cobra)
      =      -> soma da pontuacao final
      */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_TRILHA 6 /* trilha menor, so para facilitar a demonstracao */
int lerNumero(void) {
    int n;
    int c;
    if (scanf("%d", &n) != 1) {
        printf("\nEntrada encerrada. Ate a proxima!\n");
        exit(0);
    }
    while ((c = getchar()) != '\n' && c != EOF) { /* limpa o resto da linha */ }
    return n;
}
void mostrarTrilha(char trilha[], int posJogador, char icone) {
    int i;
    printf("\n[ ");
    for (i = 0; i < TAM_TRILHA; i++) {
        if (i == posJogador)
            printf("%c ", icone);
        else
            printf("%c ", trilha[i]);
    }
    printf("]\n\n");
}
int main(void) {
    char trilha[TAM_TRILHA];
    int i, posJogador = 0, posBinoculo, posTesouro;
    int achouBinoculo = 0, achouTesouro = 0;
    int personagem, icone;
    int pontuacao = 0;
    srand((unsigned) time(NULL));
    /* ---------- escolha do personagem ---------- */
    printf("=== JOGO DA CALCULADORA ===\n\n");
    printf("Escolha seu personagem:\n");
    printf("[1] Personagem 1\n[3] Personagem 3\n> ");
    personagem = lerNumero();
    icone = (personagem == 3) ? '3' : '1';

    /* ---------- monta a trilha com o binoculo e o tesouro escondidos ---------- */
    for (i = 0; i < TAM_TRILHA; i++) trilha[i] = '.';
    posBinoculo = rand() % TAM_TRILHA;
    do {
        posTesouro = rand() % TAM_TRILHA;
    } while (posTesouro == posBinoculo);
    trilha[posBinoculo] = '8';
    /* ---------- fase 1: procurar o binoculo e o tesouro ---------- */
    printf("\nUse 2 (esquerda) ou 6 (direita) para andar na trilha.\n");
    printf("Ache o binoculo (8) para descobrir onde esta o tesouro (X)!\n");
    while (!achouTesouro) {
        int mov;
        mostrarTrilha(trilha, posJogador, icone);
        printf("Posicao: %d | Escolha 2 ou 6: ", posJogador);
        mov = lerNumero();
        if (mov == 2 && posJogador > 0) posJogador--;
        else if (mov == 6 && posJogador < TAM_TRILHA - 1) posJogador++;
        if (!achouBinoculo && posJogador == posBinoculo) {
            achouBinoculo = 1;
            trilha[posBinoculo] = '.';
            trilha[posTesouro] = 'X'; /* revela o tesouro */
            printf("\n>> Binoculo encontrado! O tesouro apareceu na trilha.\n");
        }
        if (achouBinoculo && posJogador == posTesouro) {
            achouTesouro = 1;
            pontuacao += 50;
            printf("\n>> Voce encontrou o tesouro! +50 pontos.\n");
        }
    }
    /* ---------- fase 2: batalha contra a cobra ---------- */
    printf("\nUma cobra gigante (5) apareceu para proteger o tesouro!\n");
    printf("Escolha sua arma:\n");
    printf("[7] Foice   [9] Machado   [4] Bumerangue\n> ");

    {
        int arma = lerNumero();
        int dano;
        if (arma == 7) dano = 20;      /* foice: dano medio */
        else if (arma == 9) dano = 30; /* machado: dano alto */
        else dano = 15;                /* bumerangue: dano baixo, mas simples */
        printf("\nVoce ataca a cobra e causa %d de dano!\n", dano);
        pontuacao += dano;
        if (dano >= 20)
            printf("A cobra foi derrotada! Voce venceu o jogo!\n");
        else
            printf("A cobra ficou ferida, mas voce conseguiu escapar com o tesouro!\n");
    }

    /* ---------- resultado final ---------- */
    printf("\n===========================\n");
    printf("(=) PONTUACAO FINAL: %d\n", pontuacao);
    printf("=============================\n");

    return 0;
}
