#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigo;
    char nome[50];
    int quantidade;
    double preco;
} Produto;

typedef struct
{
    int codigo;
    char tipo;
    int quantidade;
} Movimento;

int main()
{
    // Abertura segura dos arquivos de entrada
    FILE *f_produtos = fopen("produtos.txt", "r");
    FILE *f_movimentos = fopen("movimentos.txt", "r");

    if (f_produtos == NULL || f_movimentos == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        if (f_produtos)
            fclose(f_produtos);
        if (f_movimentos)
            fclose(f_movimentos);
        return 1;
    }

    // Carregar produtos em memoria RAM
    Produto produtos[200];
    int total_produtos = 0;
    while (fscanf(f_produtos, "%d %s %d %lf",
                  &produtos[total_produtos].codigo,
                  produtos[total_produtos].nome,
                  &produtos[total_produtos].quantidade,
                  &produtos[total_produtos].preco) == 4)
    {
        total_produtos++;
    }
    fclose(f_produtos);

    // Variaveis contadoras do relatorio
    int movimentos_aplicados = 0;
    int saidas_recusadas = 0;
    int movimentos_sem_cadastro = 0;

    // Criacao dos arquivos temporarios/finais de relatorio de inconsistencia
    FILE *f_inconsistencias = fopen("inconsistencias_tmp.txt", "w+");

    Movimento mov;
    // Processamento do arquivo de movimentos linha por linha
    while (fscanf(f_movimentos, "%d %c %d", &mov.codigo, &mov.tipo, &mov.quantidade) == 3)
    {
        int encontrado = -1;
        for (int i = 0; i < total_produtos; i++)
        {
            if (produtos[i].codigo == mov.codigo)
            {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1)
        {
            // Regra: Produto Inexistente
            movimentos_sem_cadastro++;
            fprintf(f_inconsistencias, "%d %c %d PRODUTO_INEXISTENTE\n", mov.codigo, mov.tipo, mov.quantidade);
        }
        else
        {
            if (mov.tipo == 'E')
            {
                produtos[encontrado].quantidade += mov.quantidade;
                movimentos_aplicados++;
            }
            else if (mov.tipo == 'S')
            {
                if (produtos[encontrado].quantidade >= mov.quantidade)
                {
                    produtos[encontrado].quantidade -= mov.quantidade;
                    movimentos_aplicados++;
                }
                else
                {
                    // Regra: Estoque Insuficiente para Saida
                    saidas_recusadas++;
                    fprintf(f_inconsistencias, "%d %c %d ESTOQUE_INSUFICIENTE\n", mov.codigo, mov.tipo, mov.quantidade);
                }
            }
        }
    }
    fclose(f_movimentos);
    fclose(f_inconsistencias);

    // Gravar o arquivo de estoque atualizado final
    FILE *f_atualizado = fopen("estoque_atualizado.txt", "w");
    for (int i = 0; i < total_produtos; i++)
    {
        fprintf(f_atualizado, "%d %s %d %.2f\n",
                produtos[i].codigo, produtos[i].nome, produtos[i].quantidade, produtos[i].preco);
    }
    fclose(f_atualizado);

    // Montagem final estruturada do relatorio.txt
    FILE *f_relatorio = fopen("relatorio.txt", "w");
    fprintf(f_relatorio, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
    fprintf(f_relatorio, "MOVIMENTOS APLICADOS: %d\n", movimentos_aplicados);
    fprintf(f_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(f_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", movimentos_sem_cadastro);

    // Secao de produtos com estoque baixo (menor ou igual a 5 unidades)
    fprintf(f_relatorio, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < total_produtos; i++)
    {
        if (produtos[i].quantidade <= 5)
        {
            fprintf(f_relatorio, "%d %s %d\n", produtos[i].codigo, produtos[i].nome, produtos[i].quantidade);
        }
    }

    // Transcrever as inconsistencias registradas temporariamente
    fprintf(f_relatorio, "INCONSISTENCIAS:\n");
    f_inconsistencias = fopen("inconsistencias_tmp.txt", "r");
    if (f_inconsistencias != NULL)
    {
        char linha_inc[256];
        while (fgets(linha_inc, sizeof(linha_inc), f_inconsistencias))
        {
            fputs(linha_inc, f_relatorio);
        }
        fclose(f_inconsistencias);
        remove("inconsistencias_tmp.txt"); // Deleta o arquivo temporario
    }
    fclose(f_relatorio);

    return 0;
}