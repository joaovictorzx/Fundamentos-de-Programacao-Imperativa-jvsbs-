#include <stdio.h>
#include <ctype.h>

int main() {
    int inicio[50]; // vetor para guardar o indice de inicio de cada palavra
    int tamanho[50]; // vetor para guardar o tamanho de cada palavra
    int total_palavras = 0; // contador de palavras
    int dentro_palavra = 0; // variavel de estado
    int tamanho_atual = 0; // tamanho da palavra em processamento
    char entrada[100];

    // le a string ate a quebra de linha
    scanf("%[^\n]", entrada);

    // varredura para preencher os vetores de inicio e tamanho
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (isalpha(entrada[i])) { 
            if (!dentro_palavra) { 
                dentro_palavra = 1;
                inicio[total_palavras] = i; 
            }
            tamanho_atual++; 
        } else { 
            if (dentro_palavra) {
                dentro_palavra = 0; 
                tamanho[total_palavras] = tamanho_atual; 
                total_palavras++; 
                tamanho_atual = 0; 
            }
        }
    } 
    // fechamento caso a string termine em uma letra
    if (dentro_palavra) { 
        tamanho[total_palavras] = tamanho_atual; 
        total_palavras++; 
    }

    int total_pares = 0; // contador de anagramas encontrados

    // laco externo itera sobre a primeira palavra da comparacao
    for (int i = 0; i < total_palavras; i++) {
        
        // laco interno itera sobre as palavras subsequentes
        for (int j = i + 1; j < total_palavras; j++) {
            
            // otimizacao: so executa a analise se os tamanhos forem identicos
            if (tamanho[i] == tamanho[j]) {
                int contagem[26] = {0}; // vetor de frequencia zerado
                
                // laco para mapear a frequencia dos caracteres simultaneamente
                for (int k = 0; k < tamanho[i]; k++) {
                    // extrai e converte o caractere para minusculo
                    char c1 = tolower(entrada[inicio[i] + k]);
                    char c2 = tolower(entrada[inicio[j] + k]);
                    
                    // incrementa para a primeira palavra e decrementa para a segunda
                    contagem[c1 - 'a']++;
                    contagem[c2 - 'a']--;
                }
                
                // validacao do vetor de frequencia
                int eh_anagrama = 1;
                for (int k = 0; k < 26; k++) {
                    if (contagem[k] != 0) {
                        eh_anagrama = 0; // invalida se houver qualquer desbalanceamento
                        break;
                    }
                }
                
                // bloco de execucao e impressao para pares validados
                if (eh_anagrama) {
                    // imprime o cabecalho apenas na primeira ocorrencia
                    if (total_pares == 0) {
                        printf("Pares de anagramas encontrados:\n");
                    }
                    
                    // laco de impressao dos caracteres da primeira palavra
                    for (int k = 0; k < tamanho[i]; k++) {
                        printf("%c", entrada[inicio[i] + k]);
                    }
                    
                    printf(" e ");
                    
                    // laco de impressao dos caracteres da segunda palavra
                    for (int k = 0; k < tamanho[j]; k++) {
                        printf("%c", entrada[inicio[j] + k]);
                    }
                    printf("\n");
                    
                    total_pares++; // incrementa o registro de pares validados
                }
            }
        }
    }

    // condicional de impressao do relatorio final
    if (total_pares == 0) {
        printf("Nao existem anagramas na frase.\n");
    } else {
        printf("\nTotal de pares: %d\n", total_pares);
    }

    return 0;
}