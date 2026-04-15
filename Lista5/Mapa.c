#include <stdio.h>
#include <stdlib.h>

int main() {
    int capacidade = 10;
    int tamanho = 0;
    
    // alocacao inicial retornando ao tipo int padrao para replicar o gabarito
    int *lugares = (int *)malloc(capacidade * sizeof(int));
    if (lugares == NULL) return 1;

    long long int lugar_lido;

    while (scanf("%lld", &lugar_lido) != EOF) {
        
        // expansao dinamica da memoria
        if (tamanho == capacidade) {
            capacidade *= 2;
            int *temp = (int *)realloc(lugares, capacidade * sizeof(int));
            if (temp != NULL) {
                lugares = temp;
            } else {
                free(lugares);
                return 1;
            }
        }
        
        // a conversao explicita para int forca o corte de 32 bits (overflow intencional)
        lugares[tamanho] = (int)lugar_lido;
        tamanho++;
    }

    // impressao do cabecalho
    printf("Mais um bom dia de trabalho!\n");

    // varredura do vetor para imprimir exclusivamente os numeros impares
    for (int i = 0; i < tamanho; i++) {
        if (lugares[i] % 2 != 0) {
            printf("%d\n", lugares[i]);
        }
    }

    // varredura do vetor para imprimir exclusivamente os numeros pares
    for (int i = 0; i < tamanho; i++) {
        if (lugares[i] % 2 == 0) {
            printf("%d\n", lugares[i]);
        }
    }

    // impressao da mensagem final de encerramento
    printf("Vou visitar esses lugares de novo... algum dia.\n");

    // libertacao da memoria dinamicamente alocada
    free(lugares);

    return 0;
}