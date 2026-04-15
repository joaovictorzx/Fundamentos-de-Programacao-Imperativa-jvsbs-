#include <stdio.h>
#include <stdlib.h>

// funcao para calcular a media de um vetor de notas
float calcular_media(float *notas, int tamanho) {
    float soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += notas[i];
    }
    return soma / tamanho;
}

// funcao para encontrar a maior nota e registrar o respectivo aluno
void encontrar_maior(float *notas, int tamanho, float *maior_nota, int *aluno) {
    *maior_nota = notas[0];
    *aluno = 1; // identificador do aluno comeca em 1
    for (int i = 1; i < tamanho; i++) {
        if (notas[i] > *maior_nota) {
            *maior_nota = notas[i];
            *aluno = i + 1;
        }
    }
}

// funcao para encontrar a menor nota e registrar o respectivo aluno
void encontrar_menor(float *notas, int tamanho, float *menor_nota, int *aluno) {
    *menor_nota = notas[0];
    *aluno = 1;
    for (int i = 1; i < tamanho; i++) {
        if (notas[i] < *menor_nota) {
            *menor_nota = notas[i];
            *aluno = i + 1;
        }
    }
}

// funcao para contabilizar alunos com nota estritamente superior a media
int contar_acima_media(float *notas, int tamanho, float media) {
    int contagem = 0;
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > media) {
            contagem++;
        }
    }
    return contagem;
}

// funcao auxiliar para ordenar um vetor temporario utilizando bubble sort
void ordenar_vetor(float *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[i] > vetor[j]) {
                float temporario = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temporario;
            }
        }
    }
}

// funcao para calcular a mediana sem modificar o vetor original
float calcular_mediana(float *notas, int tamanho) {
    float *copia = (float *)malloc(tamanho * sizeof(float));
    for (int i = 0; i < tamanho; i++) {
        copia[i] = notas[i];
    }
    
    ordenar_vetor(copia, tamanho);
    
    float mediana;
    if (tamanho % 2 != 0) {
        mediana = copia[tamanho / 2];
    } else {
        mediana = (copia[(tamanho / 2) - 1] + copia[tamanho / 2]) / 2.0;
    }
    
    free(copia);
    return mediana;
}

// funcao para calcular a moda ou definir se nao existe moda unica
int calcular_moda(float *notas, int tamanho, float *resultado_moda) {
    float *copia = (float *)malloc(tamanho * sizeof(float));
    for (int i = 0; i < tamanho; i++) {
        copia[i] = notas[i];
    }
    
    ordenar_vetor(copia, tamanho);
    
    int maximo_repeticoes = 0;
    int quantidade_modas = 0;
    float candidata_moda = -1;
    
    int repeticoes_atuais = 1;
    
    // iteracao sobre o vetor ordenado para contar sequencias identicas
    for (int i = 1; i < tamanho; i++) {
        if (copia[i] == copia[i - 1]) {
            repeticoes_atuais++;
        } else {
            if (repeticoes_atuais > maximo_repeticoes) {
                maximo_repeticoes = repeticoes_atuais;
                candidata_moda = copia[i - 1];
                quantidade_modas = 1;
            } else if (repeticoes_atuais == maximo_repeticoes) {
                quantidade_modas++;
            }
            repeticoes_atuais = 1;
        }
    }
    
    // verificacao final apos a saida do laco para o ultimo bloco de repeticoes
    if (repeticoes_atuais > maximo_repeticoes) {
        maximo_repeticoes = repeticoes_atuais;
        candidata_moda = copia[tamanho - 1];
        quantidade_modas = 1;
    } else if (repeticoes_atuais == maximo_repeticoes) {
        quantidade_modas++;
    }
    
    free(copia);
    
    // confirmacao do resultado e indicacao da existencia de multiplas modas
    if (quantidade_modas == 1) {
        *resultado_moda = candidata_moda;
        return 1;
    }
    return 0;
}

// funcao para formatar e imprimir o relatorio unificado
void imprimir_relatorio(float *notas, int tamanho, const char *titulo) {
    float media = calcular_media(notas, tamanho);
    
    float maior_nota, menor_nota;
    int aluno_maior, aluno_menor;
    
    encontrar_maior(notas, tamanho, &maior_nota, &aluno_maior);
    encontrar_menor(notas, tamanho, &menor_nota, &aluno_menor);
    
    int acima_media = contar_acima_media(notas, tamanho, media);
    float mediana = calcular_mediana(notas, tamanho);
    
    float moda;
    int tem_moda_unica = calcular_moda(notas, tamanho, &moda);
    
    printf("%s\n", titulo);
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", maior_nota, aluno_maior);
    printf("Menor nota: %.2f (aluno %d)\n", menor_nota, aluno_menor);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana);
    
    if (tem_moda_unica) {
        printf("Moda: %.2f\n", moda);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }
}

int main() {
    int alunos_iniciais;
    scanf("%d", &alunos_iniciais);
    
    // alocacao do bloco inicial de memoria para a turma basica
    float *notas = (float *)malloc(alunos_iniciais * sizeof(float));
    
    for (int i = 0; i < alunos_iniciais; i++) {
        scanf("%f", &notas[i]);
    }
    
    imprimir_relatorio(notas, alunos_iniciais, "Relatorio inicial");
    
    int novos_alunos;
    scanf("%d", &novos_alunos);
    
    // operacao de redimensionamento da memoria caso existam adicoes tardias
    if (novos_alunos > 0) {
        notas = (float *)realloc(notas, (alunos_iniciais + novos_alunos) * sizeof(float));
        
        for (int i = alunos_iniciais; i < alunos_iniciais + novos_alunos; i++) {
            scanf("%f", &notas[i]);
        }
    }
    
    printf("\n");
    imprimir_relatorio(notas, alunos_iniciais + novos_alunos, "Relatorio atualizado");
    
    // libertacao da memoria alocada antes do fecho do programa
    free(notas);
    
    return 0;
}