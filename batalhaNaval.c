#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AGUA '~'
#define NAVIO 'N'
#define TIRO_AGUA 'o'
#define TIRO_NAVIO 'X'

// Função para limpar o buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// Inicializa o tabuleiro com água
void inicializarTabuleiro(char tabuleiro[][10], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            tabuleiro[i][j] = AGUA;
}

// Exibe o tabuleiro para o jogador
void mostrarTabuleiro(char tabuleiro[][10], int tamanho, int mostrarNavios) {
    printf("   ");
    for (int i = 0; i < tamanho; i++)
        printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%2d ", i);
        for (int j = 0; j < tamanho; j++) {
            char c = tabuleiro[i][j];
            if (!mostrarNavios && c == NAVIO)
                printf(" %c ", AGUA);
            else
                printf(" %c ", c);
        }
        printf("\n");
    }
}

// Coloca navios aleatoriamente no tabuleiro
void posicionarNavios(char tabuleiro[][10], int tamanho, int numNavios) {
    int colocados = 0;
    while (colocados < numNavios) {
        int x = rand() % tamanho;
        int y = rand() % tamanho;
        if (tabuleiro[x][y] != NAVIO) {
            tabuleiro[x][y] = NAVIO;
            colocados++;
        }
    }
}

// Realiza o disparo no tabuleiro
int atirar(char tabuleiro[][10], int x, int y) {
    if (tabuleiro[x][y] == NAVIO) {
        tabuleiro[x][y] = TIRO_NAVIO;
        printf("Acertou um navio!\n");
        return 1;
    } else if (tabuleiro[x][y] == AGUA) {
        tabuleiro[x][y] = TIRO_AGUA;
        printf("Água!\n");
        return 0;
    } else {
        printf("Você já atirou aqui!\n");
        return -1;
    }
}

int main() {
    srand(time(NULL));

    int tamanho, numNavios;
    int dificuldade;

    printf("=== BATALHA NAVAL ===\n");
    printf("Escolha a dificuldade:\n");
    printf("1 - Novato (Fácil)\n");
    printf("2 - Aventureiro (Médio)\n");
    printf("3 - Mestre (Difícil)\n");
    printf("Opção: ");
    scanf("%d", &dificuldade);

    switch (dificuldade) {
        case 1:
            tamanho = 5;
            numNavios = 3;
            break;
        case 2:
            tamanho = 7;
            numNavios = 5;
            break;
        case 3:
            tamanho = 10;
            numNavios = 8;
            break;
        default:
            printf("Opção inválida! Saindo...\n");
            return 1;
    }

    char tabuleiro[10][10];
    inicializarTabuleiro(tabuleiro, tamanho);
    posicionarNavios(tabuleiro, tamanho, numNavios);

    int acertos = 0;
    while (acertos < numNavios) {
        int x, y;
        mostrarTabuleiro(tabuleiro, tamanho, 0);

        printf("Digite coordenadas (linha coluna): ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Entrada inválida.\n");
            limparBuffer();
            continue;
        }

        if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
            printf("Coordenadas fora do tabuleiro.\n");
            continue;
        }

        int resultado = atirar(tabuleiro, x, y);
        if (resultado == 1) {
            acertos++;
        }
    }

    printf("\nParabéns! Você afundou todos os navios!\n");
    mostrarTabuleiro(tabuleiro, tamanho, 1);

    return 0;
}
