#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// estrutura para armazenar os dados de cada cidadela detectada
typedef struct {
    char nome[201];
    char funcao[201];
    int populacao;
    int periculosidade;
    int ordem_chegada;
} Cidadela;

// formata strings para o padrao: Primeira Letra Maiuscula, demais minusculas
void formatar_estilo_nome(char *destino, const char *origem) {
    int j = 0;
    for (int i = 0; origem[i]; i++) {
        if (isalpha((unsigned char)origem[i])) {
            destino[j] = (j == 0) ? toupper((unsigned char)origem[i]) : tolower((unsigned char)origem[i]);
            j++;
        }
    }
    destino[j] = '\0';
}

// ordenador multicriterio: populacao (desc) > periculosidade (desc) > nome (asc)
int comparar_cidadelas(const void *a, const void *b) {
    Cidadela *c1 = (Cidadela *)a;
    Cidadela *c2 = (Cidadela *)b;
    
    if (c1->populacao != c2->populacao) 
        return c2->populacao - c1->populacao;
        
    if (c1->periculosidade != c2->periculosidade) 
        return c2->periculosidade - c1->periculosidade;
        
    int cmp_nome = strcmp(c1->nome, c2->nome);
    if (cmp_nome != 0) return cmp_nome;
    
    return c1->ordem_chegada - c2->ordem_chegada;
}

int main() {
    Cidadela lista_cidades[100];
    int total_cidades = 0;
    int chave_gingrey = -1;
    char buffer_linha[500];

    // leitura linha por linha ate o fim do arquivo
    while (fgets(buffer_linha, sizeof(buffer_linha), stdin)) {
        buffer_linha[strcspn(buffer_linha, "\n\r")] = '\0';
        if (strlen(buffer_linha) == 0) continue;

        // identifica a mensagem de resgate com a chave (presenca de '!')
        if (strchr(buffer_linha, '!')) {
            int temp_chave = 0;
            for (int i = 0; buffer_linha[i]; i++) {
                if (isdigit((unsigned char)buffer_linha[i])) {
                    temp_chave = temp_chave * 10 + (buffer_linha[i] - '0');
                }
            }
            chave_gingrey = temp_chave;
            continue; 
        }

        Cidadela temp = {"", "Nenhum", 0, 0, total_cidades};
        char iniciais_nome[201] = "";
        char iniciais_funcao[201] = "";
        int p_nome = 0, p_funcao = 0;

        char *divisor_funcao = strstr(buffer_linha, "  ");

        for (int i = 0; buffer_linha[i]; i++) {
            if (isdigit((unsigned char)buffer_linha[i])) {
                temp.populacao = temp.populacao * 10 + (buffer_linha[i] - '0');
            }
            if (isupper((unsigned char)buffer_linha[i])) {
                iniciais_nome[p_nome++] = buffer_linha[i];
            }
            if (buffer_linha[i] == '*') {
                temp.periculosidade++;
            }
        }

        if (divisor_funcao) {
            char *cursor = divisor_funcao + 2;
            int nova_palavra = 1;
            while (*cursor) {
                if (isalpha((unsigned char)*cursor)) {
                    if (nova_palavra) {
                        iniciais_funcao[p_funcao++] = *cursor;
                        nova_palavra = 0;
                    }
                } else {
                    nova_palavra = 1;
                }
                cursor++;
            }
        }
        
        if (p_nome > 0) {
            iniciais_nome[p_nome] = '\0';
            formatar_estilo_nome(temp.nome, iniciais_nome);
            
            if (p_funcao > 0) {
                iniciais_funcao[p_funcao] = '\0';
                formatar_estilo_nome(temp.funcao, iniciais_funcao);
            }
            
            lista_cidades[total_cidades++] = temp;
        }
    }

    if (chave_gingrey == -1 || chave_gingrey > total_cidades || chave_gingrey <= 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        qsort(lista_cidades, total_cidades, sizeof(Cidadela), comparar_cidadelas);
        Cidadela alvo = lista_cidades[chave_gingrey - 1];

        char estrelas_perigo[50] = "";
        for (int i = 0; i < alvo.periculosidade; i++) estrelas_perigo[i] = '*';
        estrelas_perigo[alvo.periculosidade] = '\0';

        // Imprime a base SEM pular linha
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s.", 
               alvo.nome, alvo.populacao, alvo.funcao, estrelas_perigo);

        int denso = (alvo.populacao >= 1000);
        int perigoso = (alvo.periculosidade > 3);

        // Imprime as frases de alerta na MESMA LINHA, corrigidas com a pontuacao exata
        if (denso && perigoso) {
            printf(" Talvez seja melhor desistir...\n");
        } else if (denso) {
            printf(" Um lugar denso, vai ser difícil achar ela.\n");
        } else if (perigoso) {
            printf(" Vai ser complicado entrar lá.\n");
        } else {
            printf("\n"); 
        }
    }

    return 0;
}