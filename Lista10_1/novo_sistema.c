#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Estrutura de no para conter as informacoes de cada aluno
typedef struct Aluno {
    char matricula[20];
    int prioridade;
    double cr;
    long long l;
    long long r;
    int score;
    struct Aluno *prox;
} Aluno;

// Estrutura descritora para gerenciar as filas de forma limpa
typedef struct {
    Aluno *head;
    Aluno *tail;
} Fila;

// Inicializa uma fila vazia
void inicializar_fila(Fila *f) {
    f->head = NULL;
    f->tail = NULL;
}

// Enfileira um aluno no final da fila (Mecanica FIFO)
void enqueue(Fila *f, Aluno *novo) {
    novo->prox = NULL;
    if (f->tail == NULL) {
        f->head = novo;
        f->tail = novo;
    } else {
        f->tail->prox = novo;
        f->tail = novo;
    }
}

// Remove e retorna o primeiro aluno da fila
Aluno* dequeue(Fila *f) {
    if (f->head == NULL) {
        return NULL;
    }
    Aluno *temp = f->head;
    f->head = f->head->prox;
    if (f->head == NULL) {
        f->tail = NULL;
    }
    return temp;
}

int main() {
    char comando[20];
    char nome_disciplina[60] = "";
    int vagas = 0;
    long long tempo_atual = 1;

    Fila fila_requisicoes;
    Fila fila_confirmados;

    inicializar_fila(&fila_requisicoes);
    inicializar_fila(&fila_confirmados);

    while (scanf("%s", comando) == 1) {
        if (strcmp(comando, "START") == 0) {
            scanf("%s %d", nome_disciplina, &vagas);
            tempo_atual = 1; // Reseta o relogio central do servidor
        } 
        else if (strcmp(comando, "ADD") == 0) {
            Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
            scanf("%s %d %lf %lld %lld", novo->matricula, &novo->prioridade, &novo->cr, &novo->l, &novo->r);
            
            // Formula oficial: Score = round(CR * 100) / Prioridade
            novo->score = (int)(round(novo->cr * 100.0) / novo->prioridade);
            
            enqueue(&fila_requisicoes, novo);
        } 
        else if (strcmp(comando, "PROC") == 0) {
            int qtd;
            scanf("%d", &qtd);

            for (int i = 0; i < qtd; i++) {
                if (fila_requisicoes.head == NULL) {
                    break; // Fila de requisicoes esvaziou antes do limite do lote
                }

                Aluno *atual = dequeue(&fila_requisicoes);

                // Se o servidor estiver ocioso antes da chegada do proximo aluno, avanca para L
                if (tempo_atual < atual->l) {
                    tempo_atual = atual->l;
                }

                // Verificacao de Timeout (Tempo Atual ultrapassou o limite R)
                if (tempo_atual > atual->r) {
                    printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", atual->matricula);
                    free(atual); 
                } 
                else {
                    // Se houver vaga disponivel na disciplina
                    if (vagas > 0) {
                        printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %lld\n", 
                               atual->matricula, atual->score, tempo_atual);
                        vagas--;
                        enqueue(&fila_confirmados, atual); 
                    } 
                    // Se a turma ja estiver cheia
                    else {
                        printf("[LOTADO] mat=%s | score=%d | Processado no seg: %lld\n", 
                               atual->matricula, atual->score, tempo_atual);
                        free(atual);
                    }
                    tempo_atual++; // Processamentos validos consomem 1 segundo
                }
            }
        } 
        else if (strcmp(comando, "FIM") == 0) {
            // CORRIGIDO: Emissao do titulo com os traços decorativos exigidos
            printf("--- LISTA OFICIAL: %s ---\n", nome_disciplina);
            int posicao = 1;
            
            // Esvazia a fila de confirmados para imprimir a lista oficial
            while (fila_confirmados.head != NULL) {
                Aluno *aprovado = dequeue(&fila_confirmados);
                printf("%d. Matricula: %s\n", posicao++, aprovado->matricula);
                free(aprovado);
            }

            // Limpa eventuais nos remanescentes na fila de requisicoes
            while (fila_requisicoes.head != NULL) {
                Aluno *sobra = dequeue(&fila_requisicoes);
                free(sobra);
            }
            break; 
        }
    }

    return 0;
}