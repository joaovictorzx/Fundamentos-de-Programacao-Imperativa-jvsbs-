#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da Árvore Binária de Busca
typedef struct No
{
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;

// Função para criar um novo nó na memória RAM
No *criar_no(int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo != NULL)
    {
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Função de inserção na Árvore Binária de Busca (ignora duplicados)
No *inserir(No *raiz, int valor)
{
    if (raiz == NULL)
    {
        return criar_no(valor);
    }
    if (valor < raiz->valor)
    {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

// Percurso: Pré-Ordem (Raiz -> Esquerda -> Direita)
void pre_ordem(No *raiz, int *primeiro)
{
    if (raiz != NULL)
    {
        if (*primeiro)
        {
            printf("%d", raiz->valor);
            *primeiro = 0;
        }
        else
        {
            printf(" %d", raiz->valor);
        }
        pre_ordem(raiz->esquerda, primeiro);
        pre_ordem(raiz->direita, primeiro);
    }
}

// Percurso: Em Ordem (Esquerda -> Raiz -> Direita)
void em_ordem(No *raiz, int *primeiro)
{
    if (raiz != NULL)
    {
        em_ordem(raiz->esquerda, primeiro);
        if (*primeiro)
        {
            printf("%d", raiz->valor);
            *primeiro = 0;
        }
        else
        {
            printf(" %d", raiz->valor);
        }
        em_ordem(raiz->direita, primeiro);
    }
}

// Percurso: Pós-Ordem (Esquerda -> Direita -> Raiz)
void pos_ordem(No *raiz, int *primeiro)
{
    if (raiz != NULL)
    {
        pos_ordem(raiz->esquerda, primeiro);
        pos_ordem(raiz->direita, primeiro);
        if (*primeiro)
        {
            printf("%d", raiz->valor);
            *primeiro = 0;
        }
        else
        {
            printf(" %d", raiz->valor);
        }
    }
}

// Conta a quantidade total de nós armazenados
int contar_nos(No *raiz)
{
    if (raiz == NULL)
        return 0;
    return 1 + contar_nos(raiz->esquerda) + contar_nos(raiz->direita);
}

// Conta a quantidade de nós folha (nós que não possuem filhos)
int contar_folhas(No *raiz)
{
    if (raiz == NULL)
        return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    return contar_folhas(raiz->esquerda) + contar_folhas(raiz->direita);
}

// Calcula a altura da árvore binária
int calcular_altura(No *raiz)
{
    if (raiz == NULL)
        return -1;
    int alt_esq = calcular_altura(raiz->esquerda);
    int alt_dir = calcular_altura(raiz->direita);
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

// Retorna o menor valor da árvore (basta caminhar tudo para a esquerda)
int buscar_menor(No *raiz)
{
    No *atual = raiz;
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual->valor;
}

// Retorna o maior valor da árvore (basta caminhar tudo para a direita)
int buscar_maior(No *raiz)
{
    No *atual = raiz;
    while (atual->direita != NULL)
    {
        atual = atual->direita;
    }
    return atual->valor;
}

// Libera a memória alocada dinamicamente para evitar memory leaks
void liberar_arvore(No *raiz)
{
    if (raiz != NULL)
    {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}

int main()
{
    No *raiz = NULL;
    int valor;

    // Leitura dos inteiros positivos até encontrar o limitador -1
    while (scanf("%d", &valor) == 1 && valor != -1)
    {
        if (valor > 0)
        {
            raiz = inserir(raiz, valor);
        }
    }

    // Se nenhuma chave foi inserida, exibe a mensagem padrão
    if (raiz == NULL)
    {
        printf("ARVORE VAZIA\n");
        return 0;
    }

    int primeiro;

    // Impressão dos Percursos
    printf("PREORDEM: ");
    primeiro = 1;
    pre_ordem(raiz, &primeiro);
    printf("\n");

    printf("EMORDEM: ");
    primeiro = 1;
    em_ordem(raiz, &primeiro);
    printf("\n");

    printf("POSORDEM: ");
    primeiro = 1;
    pos_ordem(raiz, &primeiro);
    printf("\n");

    // Impressão das Métricas Analíticas
    printf("NOS: %d\n", contar_nos(raiz));
    printf("FOLHAS: %d\n", contar_folhas(raiz));
    printf("ALTURA: %d\n", calcular_altura(raiz));
    printf("MENOR: %d\n", buscar_menor(raiz));
    printf("MAIOR: %d\n", buscar_maior(raiz));

    // Desalocação da memória
    liberar_arvore(raiz);

    return 0;
}