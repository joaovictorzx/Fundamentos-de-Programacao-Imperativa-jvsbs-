#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numero_strings;
    // leitura da quantidade de strings
    if (scanf("%d", &numero_strings) != 1) return 1;

    // alocacao de um vetor de ponteiros para a matriz de strings
    char **strings = (char **)malloc(numero_strings * sizeof(char *));
    if (strings == NULL) return 1;

    int tamanho_total_mesclada = 0;
    int maior_tamanho_string = 0;

    // leitura e armazenamento dinamico das strings individuais
    for (int i = 0; i < numero_strings; i++) {
        // alocacao inicial provisoria
        strings[i] = (char *)malloc(1005 * sizeof(char));
        if (strings[i] == NULL) return 1;

        scanf("%s", strings[i]);
        
        int tamanho_atual = strlen(strings[i]);
        tamanho_total_mesclada += tamanho_atual;

        // rastreamento do limite maximo para o laco de mesclagem
        if (tamanho_atual > maior_tamanho_string) {
            maior_tamanho_string = tamanho_atual;
        }

        // reajuste da memoria para o tamanho exato lido
        char *temp = (char *)realloc(strings[i], (tamanho_atual + 1) * sizeof(char));
        if (temp != NULL) {
            strings[i] = temp;
        }
    }

    // alocacao da string principal que recebera a mesclagem intercalada
    char *string_mesclada = (char *)malloc((tamanho_total_mesclada + 1) * sizeof(char));
    if (string_mesclada == NULL) return 1;

    int indice_mesclada = 0;

    // etapa 1: algoritmo de mesclagem intercalada
    for (int j = 0; j < maior_tamanho_string; j++) {
        for (int i = 0; i < numero_strings; i++) {
            // insercao do caractere caso o indice atual seja valido para a string
            if (j < strlen(strings[i])) {
                string_mesclada[indice_mesclada] = strings[i][j];
                indice_mesclada++;
            }
        }
    }
    string_mesclada[indice_mesclada] = '\0'; 

    // alocacao da string que operara como pilha para as fusoes
    char *string_fundida = (char *)malloc((tamanho_total_mesclada + 1) * sizeof(char));
    if (string_fundida == NULL) return 1;

    int topo_fundida = 0;

    // etapa 2: algoritmo de fusao de caracteres
    for (int i = 0; i < tamanho_total_mesclada; i++) {
        // insercao do caractere na estrutura de pilha
        string_fundida[topo_fundida] = string_mesclada[i];
        topo_fundida++;

        // resolucao de fusoes em cascata no topo da pilha
        while (topo_fundida >= 2 && string_fundida[topo_fundida - 1] == string_fundida[topo_fundida - 2]) {
            char caractere_base = string_fundida[topo_fundida - 1];
            
            // remocao virtual do par identico
            topo_fundida -= 2;

            // substituicao pela regra de avanco na tabela ascii
            char novo_caractere;
            if (caractere_base == 'z') {
                novo_caractere = 'a'; 
            } else {
                novo_caractere = caractere_base + 1; 
            }

            // adicao do caractere resultante para checagem continua
            string_fundida[topo_fundida] = novo_caractere;
            topo_fundida++;
        }
    }
    string_fundida[topo_fundida] = '\0'; 

    // impressao dos resultados finais
    printf("%s\n", string_mesclada);
    printf("%s\n", string_fundida);

    // liberacao da memoria dinamica alocada
    for (int i = 0; i < numero_strings; i++) {
        free(strings[i]);
    }
    free(strings);
    free(string_mesclada);
    free(string_fundida);

    return 0;
}