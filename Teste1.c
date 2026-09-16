/*
    Regras do teclado:
      1 e 3 -> personagens escolhiveis
      X     -> tesouro
      8     -> binoculo (revela onde esta o tesouro)
      7     -> foice (arma)
      9     -> machado (arma)
      4     -> bumerangue (arma)
      2     -> mover para a esquerda
      6     -> mover para a direita
      5     -> cobra (boss)
      =     -> soma da pontuacao final
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRILHA_TAM 10 /* tamanho da trilha (posicoes 0 a 9) */

/* ---------- utilidades de tela e entrada ---------- */

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* descarta o resto da linha atual do teclado (inclusive o ENTER) */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta */
    }
}

void pausar(void) {
    printf("\n(pressione ENTER para continuar...)");
    getchar(); /* a linha ja foi limpa por lerOpcao(), entao isso espera um novo ENTER */
}

/* le um numero inteiro do usuario, validando a entrada */
int lerOpcao(void) {
    int op;
    int resultado;
    while ((resultado = scanf("%d", &op)) != 1) {
        if (resultado == EOF) {
            printf("\nEntrada encerrada. Ate a proxima!\n");
            exit(0);
        }
        limparBufferEntrada();
        printf("Entrada invalida. Tente novamente: ");
    }
    limparBufferEntrada(); /* limpa o ENTER digitado depois do numero */
    return op;
}

/* ---------- telas de arte ASCII ---------- */

void mostrarCabecalho(void) {
    printf("  ____________________________ \n");
    printf(" |  JOGO DA CALCULADORA      | \n");
    printf(" |   (edicao especial Elmore)| \n");
    printf(" |____________________________| \n\n");
}

void mostrarTecladoCalculadora(void) {
    printf(" +----+----+----+ \n");
    printf(" |  7 |  8 |  9 | \n");
    printf(" +----+----+----+ \n");
    printf(" |  4 |  5 |  6 | \n");
    printf(" +----+----+----+ \n");
    printf(" |  1 |  2 |  3 | \n");
    printf(" +----+----+----+ \n");
    printf(" |  X |  0 |  = | \n");
    printf(" +----+----+----+ \n");
}

/* desenha a trilha de busca, mostrando o jogador e os itens ja revelados */
void mostrarTrilha(const char trilha[], int posJogador, char iconeJogador) {
    int i;
    printf(" ");
    for (i = 0; i < TRILHA_TAM; i++) printf("+---");
    printf("+\n ");
    for (i = 0; i < TRILHA_TAM; i++) {
        char c = (i == posJogador) ? iconeJogador : trilha[i];
        printf("| %c ", c);
    }
    printf("|\n ");
    for (i = 0; i < TRILHA_TAM; i++) printf("+---");
    printf("+\n");
}

/* ---------- estrutura das armas ---------- */
typedef struct {
    char nome[20];
    char tecla;
    int danoMin;
    int danoMax;
    int golpesPorTurno;
} Arma;

int main(void) {
    int pontuacao = 0;
    int escolhaPersonagem;
    char iconeJogador;
    char trilha[TRILHA_TAM];
    int posBinoculo, posTesouro, posJogador, movimentos;
    int binoculoAchado, tesouroAchado, tesouroRevelado;
    int i;
    int pontosExploracao, pontosBatalha;

    srand((unsigned int) time(NULL));

    limparTela();
    mostrarCabecalho();
    printf("Um dia comum na cidade de Elmore acabou de virar bagunca total.\n");
    printf("Voce vai explorar a trilha da calculadora, achar o binoculo,\n");
    printf("encontrar o tesouro perdido e enfrentar a cobra gigante que\n");
    printf("apareceu do nada (como sempre acontece por la).\n\n");
    mostrarTecladoCalculadora();
    pausar();

    /* ---------- escolha do personagem ---------- */
    limparTela();
    mostrarCabecalho();
    printf("Escolha seu personagem:\n");
    printf("  [1] o gato azul e impulsivo, sempre metido em confusao\n");
    printf("  [3] o peixinho leal, sempre do lado do amigo\n");
    printf("Opcao: ");
    do {
        escolhaPersonagem = lerOpcao();
        if (escolhaPersonagem != 1 && escolhaPersonagem != 3) {
            printf("Escolha invalida. Digite 1 ou 3: ");
        }
    } while (escolhaPersonagem != 1 && escolhaPersonagem != 3);

    iconeJogador = (escolhaPersonagem == 1) ? '1' : '3';

    /* ---------- montagem da trilha ---------- */
    for (i = 0; i < TRILHA_TAM; i++) trilha[i] = '.';

    posBinoculo = rand() % TRILHA_TAM;
    do {
        posTesouro = rand() % TRILHA_TAM;
    } while (posTesouro == posBinoculo);

    trilha[posBinoculo] = '8'; /* binoculo visivel na trilha */
    tesouroRevelado = 0;
    trilha[posTesouro] = '?'; /* tesouro escondido ate o binoculo ser achado */

    posJogador = 0;
    movimentos = 0;
    binoculoAchado = 0;
    tesouroAchado = 0;

    /* ---------- fase de exploracao ---------- */
    while (!tesouroAchado) {
        int mov;

        limparTela();
        mostrarCabecalho();
        printf("Use as teclas:\n");
        printf("  [2] mover para a esquerda\n");
        printf("  [6] mover para a direita\n");
        if (!tesouroRevelado)
            printf("Objetivo atual: achar o binoculo (8)\n\n");
        else
            printf("Objetivo atual: achar o tesouro (X)\n\n");

        mostrarTrilha(trilha, posJogador, iconeJogador);
        printf("\nPosicao atual: %d   Movimentos: %d\n", posJogador, movimentos);
        printf("Escolha (2 ou 6): ");

        mov = lerOpcao();
        if (mov == 2) {
            if (posJogador > 0) posJogador--;
            movimentos++;
        } else if (mov == 6) {
            if (posJogador < TRILHA_TAM - 1) posJogador++;
            movimentos++;
        } else {
            printf("Tecla invalida! Use somente 2 ou 6.\n");
            pausar();
            continue;
        }

        /* chegou no binoculo */
        if (!binoculoAchado && posJogador == posBinoculo) {
            binoculoAchado = 1;
            tesouroRevelado = 1;
            trilha[posTesouro] = 'X'; /* revela o tesouro de verdade */
            trilha[posBinoculo] = '.';
            limparTela();
            mostrarCabecalho();
            printf(">> Voce encontrou o binoculo (8)!\n");
            printf(">> Ao longe, no meio da bagunca de Elmore, o tesouro (X) foi avistado!\n");
            pausar();
        }

        /* chegou no tesouro (so conta se o binoculo ja foi achado) */
        if (binoculoAchado && posJogador == posTesouro) {
            tesouroAchado = 1;
        }
    }

    pontosExploracao = 100 - movimentos * 3;
    if (pontosExploracao < 0) pontosExploracao = 0;
    pontuacao += pontosExploracao;

    limparTela();
    mostrarCabecalho();
    printf(">> Voce encontrou o tesouro (X)!\n");
    printf(">> Pontos por exploracao (%d movimentos): %d\n", movimentos, pontosExploracao);
    pausar();

    /* ---------- boss: a cobra ---------- */
    limparTela();
    mostrarCabecalho();
    printf("   ____\n");
    printf("  /    \\   Do nada, uma COBRA GIGANTE (5) surgiu em Elmore\n");
    printf(" | 0  0 |  e esta bem na frente do tesouro!\n");
    printf("  \\_/\\_/   Classico dia de terca-feira por aqui.\n");
    printf("   |  |  \n");
    printf("  ~~~~~~~~~~~~ (boss)\n\n");
    printf("Escolha sua arma para a batalha:\n");
    printf("  [7] Foice     (dano medio, golpe unico e forte)\n");
    printf("  [9] Machado   (dano alto, golpe pesado)\n");
    printf("  [4] Bumerangue(dano baixo, mas atinge duas vezes)\n");
    printf("\nOpcao: ");

    {
        Arma armas[3];
        Arma *armaEscolhida = NULL;
        int hpCobra = 100;
        int hpJogador = 60;
        int turno = 1;
        int danoTotalCausado = 0;

        armas[0] = (Arma){"Foice", '7', 15, 25, 1};
        armas[1] = (Arma){"Machado", '9', 22, 32, 1};
        armas[2] = (Arma){"Bumerangue", '4', 8, 14, 2};

        while (armaEscolhida == NULL) {
            int escolhaArma = lerOpcao();
            int k;
            for (k = 0; k < 3; k++) {
                if (escolhaArma == (armas[k].tecla - '0')) {
                    armaEscolhida = &armas[k];
                    break;
                }
            }
            if (armaEscolhida == NULL) {
                printf("Escolha invalida. Digite 7, 9 ou 4: ");
            }
        }

        /* ---------- simulacao da batalha ---------- */
        limparTela();
        mostrarCabecalho();
        printf("Voce escolheu: %s\n", armaEscolhida->nome);
        printf("A batalha contra a cobra (5) comeca!\n\n");

        while (hpCobra > 0 && hpJogador > 0) {
            int danoRodada = 0;
            int g, contraAtaque;

            printf("--- Turno %d ---\n", turno);

            for (g = 0; g < armaEscolhida->golpesPorTurno; g++) {
                int dano = armaEscolhida->danoMin +
                           rand() % (armaEscolhida->danoMax - armaEscolhida->danoMin + 1);
                danoRodada += dano;
            }
            hpCobra -= danoRodada;
            danoTotalCausado += danoRodada;
            printf("Voce atacou com %s e causou %d de dano!\n", armaEscolhida->nome, danoRodada);

            if (hpCobra <= 0) {
                hpCobra = 0;
                printf("A cobra foi derrotada!\n");
                break;
            }

            contraAtaque = 5 + rand() % 11; /* 5 a 15 */
            hpJogador -= contraAtaque;
            printf("A cobra revidou causando %d de dano!\n", contraAtaque);
            printf("HP Cobra: %d   HP Jogador: %d\n\n", hpCobra, (hpJogador > 0 ? hpJogador : 0));

            turno++;
        }

        pontosBatalha = 0;
        limparTela();
        mostrarCabecalho();
        if (hpJogador <= 0) {
            printf("Voce foi derrotado pela cobra... mais um dia estranho em Elmore.\n");
            pontosBatalha = danoTotalCausado; /* ainda ganha pontos pelo dano causado */
        } else {
            int bonusTurno = 80 - turno * 5;
            if (bonusTurno < 0) bonusTurno = 0;
            printf("Parabens! Voce derrotou a cobra em %d turnos e salvou\n", turno);
            printf("o dia (de novo) para a cidade de Elmore!\n");
            pontosBatalha = danoTotalCausado + bonusTurno + hpJogador;
        }
        pontuacao += pontosBatalha;

        printf("Pontos da batalha: %d\n", pontosBatalha);
        pausar();
    }

    /* ---------- resultado final ---------- */
    limparTela();
    mostrarCabecalho();
    printf("RESULTADO FINAL\n\n");
    printf("Exploracao ......... %d\n", pontosExploracao);
    printf("Batalha ............ %d\n", pontosBatalha);
    printf("-----------------------------\n");
    printf("(=) PONTUACAO TOTAL: %d\n\n", pontuacao);

    if (pontuacao >= 180) printf("Classificacao: LENDARIO(A) CACADOR(A) DE TESOUROS!\n");
    else if (pontuacao >= 120) printf("Classificacao: AVENTUREIRO(A) EXPERIENTE!\n");
    else printf("Classificacao: AVENTUREIRO(A) INICIANTE.\n");

    printf("\nObrigado por jogar!\n");
    return 0;
}
