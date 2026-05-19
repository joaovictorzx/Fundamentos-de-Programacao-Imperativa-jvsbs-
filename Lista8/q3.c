#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[50];
} IrisData;

// Funcao auxiliar para contar frequencia e achar a moda (especie predominante)
void calcular_moda(IrisData *dados, int total, char *resultado)
{
    int max_freq = 0;
    char moda[50] = "";

    for (int i = 0; i < total; i++)
    {
        int freq = 0;
        for (int j = 0; j < total; j++)
        {
            if (strcmp(dados[i].species, dados[j].species) == 0)
            {
                freq++;
            }
        }
        // Desempate por maior frequencia ou menor ordem lexicografica em caso de empate
        if (freq > max_freq || (freq == max_freq && strcmp(dados[i].species, moda) < 0))
        {
            max_freq = freq;
            strcpy(moda, dados[i].species);
        }
    }
    strcpy(resultado, moda);
}

void processar_csv(int numero_arquivo)
{
    char nome_arquivo[30];
    sprintf(nome_arquivo, "iris%d.csv", numero_arquivo);

    // Abre o arquivo para leitura
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        return;
    }

    char linha[256];
    // Ignorar a linha de cabecalho do CSV
    if (!fgets(linha, sizeof(linha), arq))
    {
        fclose(arq);
        return;
    }

    int capacidade = 10;
    int total = 0;
    IrisData *dados = malloc(capacidade * sizeof(IrisData));

    // Leitura dos dados tabulares com realloc dinamico
    while (fgets(linha, sizeof(linha), arq))
    {
        if (total == capacidade)
        {
            capacidade *= 2;
            dados = realloc(dados, capacidade * sizeof(IrisData));
        }

        // Remocao de quebras de linha residuais
        linha[strcspn(linha, "\n\r")] = '\0';

        // Parsing da linha separada por virgulas
        sscanf(linha, "%lf,%lf,%lf,%lf,%s",
               &dados[total].sepal_length,
               &dados[total].sepal_width,
               &dados[total].petal_length,
               &dados[total].petal_width,
               dados[total].species);
        total++;
    }
    fclose(arq);

    if (total == 0)
    {
        free(dados);
        return;
    }

    // Calculos estatisticos
    double soma_sl = 0, soma_sw = 0, soma_pl = 0, soma_pw = 0;
    for (int i = 0; i < total; i++)
    {
        soma_sl += dados[i].sepal_length;
        soma_sw += dados[i].sepal_width;
        soma_pl += dados[i].petal_length;
        soma_pw += dados[i].petal_width;
    }

    char especie_moda[50];
    calcular_moda(dados, total, especie_moda);

    // Exibicao no terminal do conteudo
    printf("--- Conteudo do Arquivo: %s ---\n", nome_arquivo);
    for (int i = 0; i < total; i++)
    {
        printf("%.1f, %.1f, %.1f, %.1f, %s\n",
               dados[i].sepal_length, dados[i].sepal_width,
               dados[i].petal_length, dados[i].petal_width, dados[i].species);
    }

    // Reabre o arquivo em modo "append" (a) para gravar no final dele
    arq = fopen(nome_arquivo, "a");
    if (arq != NULL)
    {
        fprintf(arq, "\nMedias,%.2f,%.2f,%.2f,%.2f\n",
                soma_sl / total, soma_sw / total, soma_pl / total, soma_pw / total);
        fprintf(arq, "Moda,%s\n", especie_moda);
        fclose(arq);
    }

    free(dados);
}

int main()
{
    int quantidade_arquivos;
    if (scanf("%d", &quantidade_arquivos) != 1)
        return 0;

    for (int i = 1; i <= quantidade_arquivos; i++)
    {
        processar_csv(i);
    }

    return 0;
}