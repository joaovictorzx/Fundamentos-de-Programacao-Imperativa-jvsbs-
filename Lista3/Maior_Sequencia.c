#include <stdio.h>

int main() {
    int num_casos;
    scanf("%d", &num_casos);

    // laco principal dos casos de teste
    for (int i = 0; i < num_casos; i++) {
        int len_sequencia;
        scanf("%d", &len_sequencia);

        int sequencia[100];

        // le os numeros e guarda no vetor
        for (int k = 0; k < len_sequencia; k++) {
            scanf("%d", &sequencia[k]);
        }

        // inicializa as variaveis de rastreamento
        int tamanho_atual = 1;
        int inicio_atual = 0;
        int maior_tamanho = 1;
        int inicio_maior = 0;

        // laco de verificacao da sequencia decrescente
        for (int j = 1; j < len_sequencia; j++) {
            // verifica se o numero atual e menor que o anterior
            if (sequencia[j] < sequencia[j - 1]) {
                tamanho_atual++;
            } else {
                // se quebrou a sequencia, verifica se e o novo recorde
                if (tamanho_atual > maior_tamanho) {
                    maior_tamanho = tamanho_atual;
                    inicio_maior = inicio_atual;
                }
                // reseta os contadores para o novo numero
                inicio_atual = j;
                tamanho_atual = 1;
            }
        }

        // verificacao final para sequencias que terminam no final do vetor
        if (tamanho_atual > maior_tamanho) {
            maior_tamanho = tamanho_atual;
            inicio_maior = inicio_atual;
        }

        // verifica se realmente encontrou alguma sequencia decrescente
        if (maior_tamanho == 1) {
            // se o recorde continuou 1, e porque nao houve sequencia decrescente
            printf("0\n");
        } else {
            // impressao do tamanho recorde
            printf("%d\n", maior_tamanho);

            // laco para imprimir os numeros da sequencia vencedora deixando espaco no final
            for (int j = inicio_maior; j < inicio_maior + maior_tamanho; j++) {
                printf("%d ", sequencia[j]);
            }
            printf("\n");
        }
    }

    return 0;
}