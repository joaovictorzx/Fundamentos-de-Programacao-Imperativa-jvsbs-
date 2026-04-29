#include <stdio.h>
#include <stdlib.h>

// funcoes de operacao matematica
int dobro(int valor) {
    return valor * 2;
}

int quadrado(int valor) {
    return valor * valor;
}

int absoluto(int valor) {
    if (valor < 0) {
        return -valor;
    }
    return valor;
}

// funcao para alocar a matriz dinamicamente
int** alocar_matriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }
    return matriz;
}

// funcao para ler os elementos da matriz
void ler_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

// funcao para imprimir a matriz
void imprimir_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d", matriz[i][j]);
            // prevencao de espaco em branco no final da linha
            if (j < colunas - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// funcao para liberar a memoria alocada
void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// funcao para aplicar a operacao usando ponteiro para funcao
void aplicar_operacao(int **matriz, int linhas, int colunas, int (*operacao)(int)) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            // executa a funcao apontada na memoria e sobrescreve o valor atual
            matriz[i][j] = operacao(matriz[i][j]);
        }
    }
}

int main() {
    int linhas, colunas;
    
    // leitura das dimensoes da matriz
    if (scanf("%d %d", &linhas, &colunas) != 2) return 0;

    // instanciacao da matriz via funcao dedicada
    int **matriz = alocar_matriz(linhas, colunas);

    // preenchimento dos dados
    ler_matriz(matriz, linhas, colunas);

    int opcao;
    scanf("%d", &opcao);

    // declaracao do ponteiro para funcao
    int (*ponteiro_operacao)(int) = NULL;

    // mapeamento da escolha do usuario para a respectiva funcao
    if (opcao == 1) {
        ponteiro_operacao = dobro;
    } else if (opcao == 2) {
        ponteiro_operacao = quadrado;
    } else if (opcao == 3) {
        ponteiro_operacao = absoluto;
    }

    // aplicacao da transformacao correspondente em toda a matriz
    if (ponteiro_operacao != NULL) {
        aplicar_operacao(matriz, linhas, colunas, ponteiro_operacao);
    }

    // impressao do resultado
    imprimir_matriz(matriz, linhas, colunas);

    // libertacao da memoria alocada para evitar vazamentos (memory leaks)
    liberar_matriz(matriz, linhas);

    return 0;
}
