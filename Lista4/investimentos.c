#include <stdio.h>

int main()
{
    // inicializacao da matriz 4x4 com zeros para contagem de visitas
    int cidade[4][4] = {0};

    // definicao das coordenadas iniciais no canto superior esquerdo
    int posicao_x = 0;
    int posicao_y = 0;

    // laco de repeticao para processar os 20 movimentos exigidos
    for (int i = 0; i < 20; i++)
    {
        char movimento;
        scanf(" %c", &movimento);

        // atualizacao dos eixos com base na direcao lida
        if (movimento == 'c')
        {
            posicao_y--; // move para cima
        }
        else if (movimento == 'b')
        {
            posicao_y++; // move para baixo
        }
        else if (movimento == 'e')
        {
            posicao_x--; // move para a esquerda
        }
        else if (movimento == 'd')
        {
            posicao_x++; // move para a direita
        }

        // incremento do contador do local visitado mediante validacao dos limites da matriz
        if (posicao_x >= 0 && posicao_x < 4 && posicao_y >= 0 && posicao_y < 4)
        {
            cidade[posicao_y][posicao_x]++;
        }
    }

    int max_visitas = -1;
    int alvo_x = 0;
    int alvo_y = 0;

    // varredura da matriz bidimensional para identificar a coordenada de maior frequencia
    for (int linha = 0; linha < 4; linha++)
    {
        for (int coluna = 0; coluna < 4; coluna++)
        {
            if (cidade[linha][coluna] > max_visitas)
            {
                max_visitas = cidade[linha][coluna];
                alvo_y = linha;
                alvo_x = coluna;
            }
        }
    }

    // impressao das coordenadas do esconderijo final no formato especificado
    printf("Coordenada X:%d, Y:%d\n", alvo_x, alvo_y);

    return 0;
}