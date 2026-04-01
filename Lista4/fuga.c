#include <stdio.h>

// estrutura para representar os elementos da fila na busca em largura
typedef struct
{
    int linha;
    int coluna;
    int distancia;
} Posicao;

// declaracoes globais para evitar estouro de pilha (stack overflow) com matrizes grandes
Posicao fila[1000000];
char mapa[1005][1005];
int visitado[1005][1005];

int main()
{
    int linhas, colunas;

    // leitura das dimensoes da matriz separadas pelo caractere 'x'
    if (scanf("%dx%d", &linhas, &colunas) != 2)
    {
        return 0;
    }

    int inicio_linha = -1;
    int inicio_coluna = -1;

    // leitura do mapa e rastreamento da coordenada de origem
    for (int i = 0; i < linhas; i++)
    {
        scanf("%s", mapa[i]);
        for (int j = 0; j < colunas; j++)
        {
            if (mapa[i][j] == 'o')
            {
                inicio_linha = i;
                inicio_coluna = j;
            }
            visitado[i][j] = 0; // inicializacao da matriz de controle
        }
    }

    // inicializacao dos ponteiros da fila
    int cabeca = 0;
    int cauda = 0;

    // enfileiramento do no inicial
    fila[cauda].linha = inicio_linha;
    fila[cauda].coluna = inicio_coluna;
    fila[cauda].distancia = 0;
    cauda++;

    visitado[inicio_linha][inicio_coluna] = 1;

    // vetores de deslocamento espacial: cima, baixo, esquerda, direita
    int deslocamento_linha[] = {-1, 1, 0, 0};
    int deslocamento_coluna[] = {0, 0, -1, 1};

    int menor_distancia = -1;

    // execucao do laco principal da busca em largura
    while (cabeca < cauda)
    {
        Posicao atual = fila[cabeca];
        cabeca++;

        // verificacao da condicao de sucesso: alcance do caractere de destino
        if (mapa[atual.linha][atual.coluna] == 'd')
        {
            menor_distancia = atual.distancia;
            break;
        }

        // iteracao sobre os quatro eixos adjacentes possiveis
        for (int i = 0; i < 4; i++)
        {
            int nova_linha = atual.linha + deslocamento_linha[i];
            int nova_coluna = atual.coluna + deslocamento_coluna[i];

            // validacao dos limites matriz e checagem de barreiras e de nos ja processados
            if (nova_linha >= 0 && nova_linha < linhas && nova_coluna >= 0 && nova_coluna < colunas)
            {
                if (mapa[nova_linha][nova_coluna] != '#' && visitado[nova_linha][nova_coluna] == 0)
                {

                    // enfileiramento do novo no com incremento de distancia
                    fila[cauda].linha = nova_linha;
                    fila[cauda].coluna = nova_coluna;
                    fila[cauda].distancia = atual.distancia + 1;
                    cauda++;

                    // atualizacao do controle de estado para evitar reprocessamento
                    visitado[nova_linha][nova_coluna] = 1;
                }
            }
        }
    }

    // emissao do relatorio de rotas segundo os padroes de formatacao exigidos
    if (menor_distancia != -1)
    {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", menor_distancia);
    }
    else
    {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}