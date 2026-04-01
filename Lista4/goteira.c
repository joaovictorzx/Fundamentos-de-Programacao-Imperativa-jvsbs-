#include <stdio.h>

// funcao recursiva para simular o comportamento de espalhamento da agua
void espalha_agua(int linha, int coluna, int total_linhas, int total_colunas, char parede[][505])
{
    // marca a posicao atual como agua
    parede[linha][coluna] = 'o';

    // verifica se a agua ainda nao atingiu o fundo da matriz
    if (linha + 1 < total_linhas)
    {

        // se o espaco imediatamente abaixo for vazio, a agua continua caindo
        if (parede[linha + 1][coluna] == '.')
        {
            espalha_agua(linha + 1, coluna, total_linhas, total_colunas, parede);
        }
        // se encontrar uma prateleira, a agua precisa espalhar para os dois lados
        else if (parede[linha + 1][coluna] == '#')
        {

            // verifica limite da borda e se o espaco a direita esta livre para espalhar
            if (coluna + 1 < total_colunas && parede[linha][coluna + 1] == '.')
            {
                espalha_agua(linha, coluna + 1, total_linhas, total_colunas, parede);
            }

            // verifica limite da borda e se o espaco a esquerda esta livre para espalhar
            if (coluna - 1 >= 0 && parede[linha][coluna - 1] == '.')
            {
                espalha_agua(linha, coluna - 1, total_linhas, total_colunas, parede);
            }
        }
    }
}

int main()
{
    int linhas, colunas;

    // leitura das dimensoes da parede
    scanf("%d %d", &linhas, &colunas);

    // declaracao do array bidimensional com folga de seguranca no tamanho
    char parede[505][505];

    int inicio_linha = 0;
    int inicio_coluna = 0;

    // leitura da configuracao inicial da matriz e identificacao da goteira
    for (int i = 0; i < linhas; i++)
    {
        scanf("%s", parede[i]);

        for (int j = 0; j < colunas; j++)
        {
            // checagem para identificar a origem da agua (tratando possiveis variacoes do caractere)
            if (parede[i][j] == 'o' || parede[i][j] == 'O')
            {
                inicio_linha = i;
                inicio_coluna = j;

                // o ponto inicial e temporariamente substituido por um espaco vazio
                // isso garante que a recursao preencha o caminho corretamente desde o inicio
                parede[i][j] = '.';
            }
        }
    }

    // inicio da simulacao a partir das coordenadas registradas
    espalha_agua(inicio_linha, inicio_coluna, linhas, colunas, parede);

    // impressao da matriz atualizada apos o trajeto completo da agua
    for (int i = 0; i < linhas; i++)
    {
        printf("%s\n", parede[i]);
    }

    return 0;
}