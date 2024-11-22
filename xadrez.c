#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int linha;
    int coluna;
} Posicao;

Posicao criaPosicao(int linha, int coluna) {
    Posicao pos;
    pos.linha = linha;
    pos.coluna = coluna;
    return pos;
}

bool verifica(int** tabuleiro, int tam, Posicao pos) {
    int i, j;

    for (i = 0; i < pos.coluna; i++) {
        if (tabuleiro[pos.linha][i]) {
            return false;
        }
    }

    for (i = pos.linha, j = pos.coluna; i >= 0 && j >= 0; i--, j--) {
        if (tabuleiro[i][j]) {
            return false;
        }
    }

    for (i = pos.linha, j = pos.coluna; j >= 0 && i < tam; i++, j--) {
        if (tabuleiro[i][j]) {
            return false;
        }
    }

    return true;
}

bool solucao(int** tabuleiro, int tam, int col) {
    if (col >= tam) {
        return true;
    }

    for (int i = 0; i < tam; i++) {
        Posicao pos = criaPosicao(i, col);
        if (verifica(tabuleiro, tam, pos)) {
            tabuleiro[pos.linha][pos.coluna] = 1;

            if (solucao(tabuleiro, tam, col + 1)) {
                return true;
            }

            tabuleiro[pos.linha][pos.coluna] = 0;
        }
    }

    return false;
}

int main() {
    int tam;
    int i, j;

    printf("Insira o tamanho do tabuleiro: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    int** tabuleiro = (int**)malloc(tam * sizeof(int*));
    for (i = 0; i < tam; i++) {
        tabuleiro[i] = (int*)calloc(tam, sizeof(int));
    }

    if (solucao(tabuleiro, tam, 0)) {
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                printf("%c ", tabuleiro[i][j] ? 'Q' : '-');
            }
            printf("\n");
        }
        printf("\n");
    } else {
        printf("Não há solução\n");
    }

    for (i = 0; i < tam; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}