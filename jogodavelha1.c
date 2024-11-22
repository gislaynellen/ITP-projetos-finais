#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 3

// Definição da estrutura para representar o jogo da velha
typedef struct {
    char** tabuleiro;  // Ponteiro para um array bidimensional de caracteres representando o tabuleiro
} JogoDaVelha;

// Função para inicializar o tabuleiro
void inicializaTabuleiro(JogoDaVelha* jogo) {
    // Aloca memória para as linhas do tabuleiro
    jogo->tabuleiro = (char**)malloc(SIZE * sizeof(char*));
    for (int i = 0; i < SIZE; i++) {
        // Aloca memória para cada coluna do tabuleiro
        jogo->tabuleiro[i] = (char*)malloc(SIZE * sizeof(char));
        for (int j = 0; j < SIZE; j++) {
            // Preenche o tabuleiro com números de 1 a 9 para indicar as posições
            jogo->tabuleiro[i][j] = '0' + (i * SIZE + j + 1);
        }
    }
}

// Função para liberar a memória alocada para o tabuleiro
void liberaTabuleiro(JogoDaVelha* jogo) {
    // Libera cada linha do tabuleiro
    for (int i = 0; i < SIZE; i++) {
        free(jogo->tabuleiro[i]);
    }
    // Libera o array de ponteiros
    free(jogo->tabuleiro);
}

// Função para imprimir o estado atual do tabuleiro
void imprimeTabuleiro(JogoDaVelha* jogo) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Imprime cada célula do tabuleiro
            printf(" %c ", jogo->tabuleiro[i][j]);
            if (j < SIZE - 1) {
                // Imprime o separador de colunas
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            // Imprime o separador de linhas
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

// Função para validar se uma posição escolhida está disponível
bool validaPosicao(JogoDaVelha* jogo, int pos) {
    int row = (pos - 1) / SIZE;  // Calcula a linha da posição
    int col = (pos - 1) % SIZE;  // Calcula a coluna da posição
    // Verifica se a posição não está ocupada por 'X' ou 'O'
    return (jogo->tabuleiro[row][col] != 'X' && jogo->tabuleiro[row][col] != 'O');
}

// Função para verificar se o jogador atual venceu
bool checaVitoria(JogoDaVelha* jogo, char jogador) {
    // Verifica linhas e colunas
    for (int i = 0; i < SIZE; i++) {
        if (jogo->tabuleiro[i][0] == jogador && jogo->tabuleiro[i][1] == jogador && jogo->tabuleiro[i][2] == jogador)
            return true;
        if (jogo->tabuleiro[0][i] == jogador && jogo->tabuleiro[1][i] == jogador && jogo->tabuleiro[2][i] == jogador)
            return true;
    }

    // Verifica diagonais
    if (jogo->tabuleiro[0][0] == jogador && jogo->tabuleiro[1][1] == jogador && jogo->tabuleiro[2][2] == jogador)
        return true;
    if (jogo->tabuleiro[0][2] == jogador && jogo->tabuleiro[1][1] == jogador && jogo->tabuleiro[2][0] == jogador)
        return true;

    // Retorna falso se nenhuma condição de vitória foi satisfeita
    return false;
}

// Função para verificar se o tabuleiro deu empate
bool checaTabuleiroCheio(JogoDaVelha* jogo) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Se houver uma célula que não está marcada com 'X' ou 'O', o tabuleiro não está cheio
            if (jogo->tabuleiro[i][j] != 'X' && jogo->tabuleiro[i][j] != 'O')
                return false;
        }
    }
    // Se todas as células estão preenchidas, retorna verdadeiro
    return true;
}

int main() {
    JogoDaVelha jogo;  
    inicializaTabuleiro(&jogo);  // Inicializa o tabuleiro

    srand(time(NULL)); // Gerar números aleatórios

    int jogadorPos, pcPos;  // Variáveis para armazenar as posições escolhidas pelos jogadores
    char jogadorAtual = 'X';  // Define o jogador atual (X começa)

    while (true) {  // Loop principal do jogo
        imprimeTabuleiro(&jogo);  // Imprime o tabuleiro

        if (jogadorAtual == 'X') {  // Turno do jogador humano
            printf("Escolha sua posição, jogador X: ");
            scanf("%d", &jogadorPos);  // Lê a posição escolhida

            // Verifica se a posição é válida
            if (jogadorPos < 1 || jogadorPos > 9 || !validaPosicao(&jogo, jogadorPos)) {
                printf("Posição inválida, escolha outra.\n");
                continue;  // Se inválida, pede outra posição
            }

            int row = (jogadorPos - 1) / SIZE;  // Calcula a linha da posição
            int col = (jogadorPos - 1) % SIZE;  // Calcula a coluna da posição
            jogo.tabuleiro[row][col] = 'X';  // Marca a posição com 'X'
        } else {  // Turno do PC
            do {
                pcPos = rand() % 9 + 1;  // Gera uma posição aleatória
            } while (!validaPosicao(&jogo, pcPos));  // Repete até encontrar uma posição válida

            int row = (pcPos - 1) / SIZE;  // Calcula a linha da posição
            int col = (pcPos - 1) % SIZE;  // Calcula a coluna da posição
            jogo.tabuleiro[row][col] = 'O';  // Marca a posição com 'O'

            printf("PC escolheu a posição %d.\n", pcPos);
        }

        // Verifica se o jogador atual venceu
        if (checaVitoria(&jogo, jogadorAtual)) {
            imprimeTabuleiro(&jogo);  // Imprime o tabuleiro final
            printf("Jogador %c venceu!\n", jogadorAtual);
            break;  // Encerra o jogo
        } else if (checaTabuleiroCheio(&jogo)) {  // Verifica se o tabuleiro está cheio (empate)
            imprimeTabuleiro(&jogo);  // Imprime o tabuleiro final
            printf("Empate!\n");
            break;  // Encerra o jogo
        }

        // Alterna o jogador atual
        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
    }

    liberaTabuleiro(&jogo);  // Libera a memória alocada para o tabuleiro

    return 0;
}
