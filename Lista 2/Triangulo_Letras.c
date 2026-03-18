#include <stdio.h>

int main() {
    char letra_digitada;
    scanf("%c", &letra_digitada);

    int total_de_linhas = letra_digitada - 'A' + 1; 

    // Laco principal
    for (int i = 0; i < total_de_linhas; i++) {
        
        // 1. Pontos da esquerda
        for (int j = 1; total_de_linhas - j > i; j++) {
            printf(".");
        }

        // 2. Letras crescendo
        for (char c = 'A'; c <= 'A' + i; c++) {
            printf("%c", c);
        }

        // 3. Letras decrescendo
        for (char d = 'A' + i - 1; d >= 'A'; d--) {
            printf("%c", d);
        } 

        // 4. Pontos da direita
        for (int j = 1; total_de_linhas - j > i; j++) {
            printf(".");
        }

        // Pula a linha
        printf("\n");
        
    }

    return 0;
}