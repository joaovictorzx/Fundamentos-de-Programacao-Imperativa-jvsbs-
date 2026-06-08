#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos uma estrutura simples de Pilha para o jogo
typedef struct {
    char data[10000]; // Tamanho seguro para suportar grandes pilhas 
    int size;
} Stack;

// Função para inserir bloco no topo da pilha
void push(Stack *s, char c) {
    s->data[s->size++] = c;
}

// A lógica principal do jogo: avalia se há combinações ou destruições
void evaluate(Stack *s) {
    int changed = 1;
    
    // O loop garante que reações em cadeia sejam processadas 
    // (ex: um bloco recém fundido ativa outra regra)
    while (changed) {
        changed = 0;
        
        // Regra 1: Destruir 3 blocos iguais consecutivos no topo
        if (s->size >= 3) {
            char c1 = s->data[s->size - 1];
            char c2 = s->data[s->size - 2];
            char c3 = s->data[s->size - 3];
            
            if (c1 == c2 && c2 == c3) {
                s->size -= 3; // Elimina os 3 removendo-os do topo
                changed = 1;
                continue;     // Reinicia o loop para verificar o novo topo
            }
        }
        
        // Regras 2, 3 e 4: Fusão de blocos de cores diferentes no topo
        if (s->size >= 2) {
            char top1 = s->data[s->size - 1];
            char top2 = s->data[s->size - 2];
            char new_color = 0;
            
            // Verifica as misturas (independentemente da ordem que se tocam)
            if ((top1 == 'g' && top2 == 'b') || (top1 == 'b' && top2 == 'g')) {
                new_color = 'c'; // ciano
            } else if ((top1 == 'r' && top2 == 'b') || (top1 == 'b' && top2 == 'r')) {
                new_color = 'm'; // magenta
            } else if ((top1 == 'r' && top2 == 'g') || (top1 == 'g' && top2 == 'r')) {
                new_color = 'y'; // amarelo
            }
            
            // Se ocorreu uma fusão, aplica na pilha
            if (new_color) {
                s->size -= 2;                  // Remove os 2 originais
                s->data[s->size++] = new_color; // Adiciona o novo fundido
                changed = 1;
                continue;
            }
        }
    }
}

// Imprime a pilha do topo até a base
void print_stack(Stack *s) {
    if (s->size == 0) {
        printf("Pilha vazia!\n\n");
    } else {
        for (int i = s->size - 1; i >= 0; i--) {
            printf("%c\n", s->data[i]);
        }
        printf("\n"); // Pula uma linha após cada impressão de pilha
    }
}

int main() {
    Stack s;
    s.size = 0;
    char c;
    
    // Lê a entrada caractere por caractere ignorando espaços em branco e quebras de linha
    while (scanf(" %c", &c) == 1) {
        // Filtra apenas os caracteres válidos para o jogo previnindo bugs com sujeira de buffer
        if (strchr("rgbcmy", c)) {
            push(&s, c);
            evaluate(&s);
            print_stack(&s);
        }
    }
    
    // Mensagem de encerramento
    printf("Thank You So Much For Playing My Game!\n");
    
    return 0;
}