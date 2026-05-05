#include <stdio.h>
#include <string.h>

// estrutura para representar um jogo na colecao
typedef struct {
    char titulo[100];
    char genero[100];
    char estudio[100];
    char console[100];
    int nota;
    int ano;
} Jogo;

int main() {
    int n;
    // leitura da quantidade inicial de jogos
    if (scanf("%d", &n) == EOF) return 0;

    Jogo colecao[100];

    // cadastro dos jogos e mensagens de feedback conforme a nota
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s %d %d", 
              colecao[i].titulo, 
              colecao[i].genero, 
              colecao[i].estudio, 
              colecao[i].console, 
              &colecao[i].nota, 
              &colecao[i].ano);

        if (colecao[i].nota > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        } else if (colecao[i].nota < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }

    char comando[50];
    // processamento das funcoes ate o fim da entrada (eof)
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "printColecao") == 0) {
            for (int i = 0; i < n; i++) {
                printf("%s %d\n", colecao[i].titulo, colecao[i].nota);
            }
        } else {
            char parametro[100];
            scanf("%s", parametro);
            int contagem = 0;

            if (strcmp(comando, "printAno") == 0) {
                int anoBusca = atoi(parametro);
                for (int i = 0; i < n; i++) {
                    if (colecao[i].ano == anoBusca) {
                        printf("%s\n", colecao[i].titulo);
                        contagem++;
                    }
                }
            } else if (strcmp(comando, "printLetra") == 0) {
                char letra = parametro[0];
                for (int i = 0; i < n; i++) {
                    if (colecao[i].titulo[0] == letra) {
                        printf("%s\n", colecao[i].titulo);
                        contagem++;
                    }
                }
            } else if (strcmp(comando, "printStudio") == 0) {
                for (int i = 0; i < n; i++) {
                    if (strcmp(colecao[i].estudio, parametro) == 0) {
                        printf("%s\n", colecao[i].titulo);
                        contagem++;
                    }
                }
            } else if (strcmp(comando, "printConsole") == 0) {
                for (int i = 0; i < n; i++) {
                    if (strcmp(colecao[i].console, parametro) == 0) {
                        printf("%s\n", colecao[i].titulo);
                        contagem++;
                    }
                }
            }

            // mensagens de finalizacao da busca por parametro
            if (contagem > 0) {
                printf("Tenho %d jogos || %s.\n", contagem, parametro);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
            }
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n");
    return 0;
}