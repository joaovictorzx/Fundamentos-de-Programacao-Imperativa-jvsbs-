#include <stdio.h>
#include <stdlib.h>

// definicao do tipo customizado para o ponteiro de funcao
typedef int (*filtro_operacao)(int);

// bloco de funcoes dos filtros disponiveis
int calibracao(int valor) {
    return valor + 5;
}

int saturacao(int valor) {
    // correcao do limite de saturacao de 255 para 80
    if (valor > 80) {
        return 80;
    } else if (valor < 0) {
        return 0;
    }
    return valor;
}

int amplificador(int valor) {
    return valor * 2;
}

// funcao para aplicar um filtro isolado em toda a matriz
void aplicar_filtro(int **matriz, int linhas, int colunas, filtro_operacao filtro) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = filtro(matriz[i][j]);
        }
    }
}

// funcao de alocacao dinamica bidimensional
int** alocar_matriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }
    return matriz;
}

// funcao de libertacao de memoria
void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    int linhas, colunas;
    
    // leitura inicial das dimensoes da rede de sensores
    if (scanf("%d %d", &linhas, &colunas) != 2) return 0;

    int **matriz = alocar_matriz(linhas, colunas);

    // preenchimento da matriz com os dados brutos
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // mapeamento obrigatorio do vetor de ponteiros para funcao
    filtro_operacao operacoes[4];
    operacoes[1] = calibracao;
    operacoes[2] = saturacao;
    operacoes[3] = amplificador;

    int comando;
    
    // laco de processamento principal lendo ate encontrar a interrupcao 0
    while (scanf("%d", &comando) == 1 && comando != 0) {
        
        // execucao de filtros diretos
        if (comando >= 1 && comando <= 3) {
            aplicar_filtro(matriz, linhas, colunas, operacoes[comando]);
            
        } 
        // execucao do fluxo em cascata (pipeline)
        else if (comando == 4) {
            int quantidade_filtros;
            scanf("%d", &quantidade_filtros);
            
            for (int k = 0; k < quantidade_filtros; k++) {
                int filtro_id;
                scanf("%d", &filtro_id);
                aplicar_filtro(matriz, linhas, colunas, operacoes[filtro_id]);
            }
        }
    }

    // variaveis de rastreamento para as metricas finais
    int maior_valor = matriz[0][0];
    int pos_linha = 0;
    int pos_coluna = 0;

    printf("Matriz processada:\n");
    
    // varredura simultanea para impressao e deteccao do valor maximo
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d", matriz[i][j]);
            if (j < colunas - 1) {
                printf(" ");
            }

            // prevencao estrita para manter a primeira ocorrencia em caso de empate
            if (matriz[i][j] > maior_valor) {
                maior_valor = matriz[i][j];
                pos_linha = i;
                pos_coluna = j;
            }
        }
        printf("\n");
    }

    // impressao da quebra de linha obrigatoria entre os blocos
    printf("\n");
    
    // atualizacao das strings do relatorio final
    printf("Sensor critico: %d\n", maior_valor);
    printf("Posicao: (%d,%d)\n", pos_linha, pos_coluna);

    liberar_matriz(matriz, linhas);

    return 0;
}
