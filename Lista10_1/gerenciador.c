#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da tarefa
typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa *prox;
} Tarefa;

// Ponteiros globais para gerenciar a fila
Tarefa *head = NULL;
Tarefa *tail = NULL;

// Insere uma nova tarefa no final da fila (Tail)
void inserir(int id, int prioridade) {
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    nova->id = id;
    nova->prioridade = prioridade;
    nova->prox = NULL;

    if (head == NULL) {
        head = nova;
        tail = nova;
    } else {
        tail->prox = nova;
        tail = nova;
    }
}

// Remove a tarefa do início da fila (Head)
void remover() {
    if (head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa *temp = head;
    printf("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);
    
    head = head->prox;
    
    // Se a fila ficou vazia, ajusta o tail também
    if (head == NULL) {
        tail = NULL;
    }
    
    free(temp);
}

// Lista todas as tarefas do início ao fim
void listar() {
    if (head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa *atual = head;
    while (atual != NULL) {
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->prox;
    }
}

int main() {
    char comando;
    int id, prioridade;

    // Loop principal para processar os comandos até o 'F'
    while (scanf(" %c", &comando) && comando != 'F') {
        switch (comando) {
            case 'I':
                scanf("%d %d", &id, &prioridade);
                inserir(id, prioridade);
                break;
            case 'R':
                remover();
                break;
            case 'L':
                listar();
                break;
        }
    }

    // Limpeza final da memória caso ainda haja tarefas na fila
    while (head != NULL) {
        Tarefa *temp = head;
        head = head->prox;
        free(temp);
    }

    return 0;
}