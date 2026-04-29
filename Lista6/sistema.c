#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao para alocar dinamicamente uma matriz bidimensional
int** alocar_matriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }
    return matriz;
}

// funcao para copiar a matriz gerando um estado completamente novo na memoria
int** copiar_matriz(int **original, int linhas, int colunas) {
    int **nova = alocar_matriz(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            nova[i][j] = original[i][j];
        }
    }
    return nova;
}

// funcao para libertar a memoria alocada para a matriz
void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// funcao para imprimir o estado da matriz
void imprimir_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d", matriz[i][j]);
            if (j < colunas - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// funcao para identificar a qual camada da area de efeito uma celula pertence
int obter_camada(int i, int j, int cx, int cy) {
    int dist_manhattan = abs(i - cx) + abs(j - cy);
    
    // validacao da camada 1 (centro e vizinhos ortogonais diretos)
    if (dist_manhattan <= 1) {
        return 1;
    }

    // validacao da camada 2 (vizinhos em 8 direcoes de qualquer celula da camada 1)
    int offsets_l1[5][2] = {{0,0}, {1,0}, {-1,0}, {0,1}, {0,-1}};
    for (int k = 0; k < 5; k++) {
        int l1_i = cx + offsets_l1[k][0];
        int l1_j = cy + offsets_l1[k][1];
        
        // se a celula for adjacente a alguma celula da camada 1, pertence a camada 2
        if (abs(i - l1_i) <= 1 && abs(j - l1_j) <= 1) {
            return 2;
        }
    }
    
    // retorna 0 caso a celula esteja fora da area de efeito
    return 0;
}

// funcao para contabilizar vizinhos vivos de uma celula especifica no turno atual
int contar_vizinhos_vivos(int **matriz, int linhas, int colunas, int i, int j) {
    int vivos = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            // ignora a propria celula central da varredura
            if (di == 0 && dj == 0) continue;
            
            int ni = i + di;
            int nj = j + dj;
            
            // validacao dos limites da matriz
            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
                if (matriz[ni][nj] > 0) {
                    vivos++;
                }
            }
        }
    }
    return vivos;
}

// implementacao da regra de ataque explosao arcana
void explosao_arcana(int **matriz, int linhas, int colunas, int cx, int cy) {
    printf("Estado do mapa após usar a Explosão Arcana:\n");
    
    int **nova = copiar_matriz(matriz, linhas, colunas);
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int camada = obter_camada(i, j, cx, cy);
            if (camada == 1) {
                nova[i][j] -= 50;
            } else if (camada == 2) {
                nova[i][j] -= 25;
            }
            
            // prevencao contra pontos de vida negativos
            if (nova[i][j] < 0) {
                nova[i][j] = 0;
            }
        }
    }
    
    imprimir_matriz(nova, linhas, colunas);
    liberar_matriz(nova, linhas);
}

// implementacao da regra de ataque nuvem venenosa
void nuvem_venenosa(int **matriz, int linhas, int colunas, int cx, int cy) {
    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
    
    int **atual = copiar_matriz(matriz, linhas, colunas);

    for (int turno = 1; turno <= 3; turno++) {
        int **proxima = copiar_matriz(atual, linhas, colunas);
        int hp_total_aoe = 0;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                int camada = obter_camada(i, j, cx, cy);
                
                // execucao do laco apenas para alvos dentro do raio de acao
                if (camada > 0) {
                    int vivos = contar_vizinhos_vivos(atual, linhas, colunas, i, j);
                    int dano = 5 + (8 * vivos);
                    
                    proxima[i][j] -= dano;
                    if (proxima[i][j] < 0) {
                        proxima[i][j] = 0;
                    }
                    
                    // acumulacao do hp para analise de condicao de paragem
                    hp_total_aoe += proxima[i][j];
                }
            }
        }

        imprimir_matriz(proxima, linhas, colunas);
        
        liberar_matriz(atual, linhas);
        atual = proxima;

        // condicao de paragem antecipada caso a area inteira seja purgada
        if (hp_total_aoe == 0) {
            break;
        }
        

        // impressao da quebra de linha obrigatoria entre os turnos
        if (turno < 3) {
            printf("\n");
        }
    }
    
    liberar_matriz(atual, linhas);
}

int main() {
    int linhas, colunas;
    if (scanf("%d %d", &linhas, &colunas) != 2) return 0;

    int **matriz = alocar_matriz(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    int cx, cy;
    scanf("%d %d", &cx, &cy);

    char tipo_ataque[50];
    scanf("%s", tipo_ataque);

    printf("Estado inicial do mapa:\n");
    imprimir_matriz(matriz, linhas, colunas);
    
    // adicao da quebra de linha isolando os processos de impressao
    printf("\n");

    void (*ataque)(int**, int, int, int, int) = NULL;

    if (strcmp(tipo_ataque, "EXPLOSAO_ARCANA") == 0) {
        ataque = explosao_arcana;
    } else if (strcmp(tipo_ataque, "NUVEM_VENENOSA") == 0) {
        ataque = nuvem_venenosa;
    }

    if (ataque != NULL) {
        ataque(matriz, linhas, colunas, cx, cy);
    }

    liberar_matriz(matriz, linhas);
    return 0;
}
