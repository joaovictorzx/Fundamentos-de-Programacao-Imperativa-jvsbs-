#include <stdio.h>

int main() {
    int n, a, b;

    // Leitura de N, A e B
    scanf("%d", &n);
    scanf("%d %d", &a, &b);

    // Calculo das somas pela formula da PA

    // 1. Soma total de 1 ate N
    int soma_total = (1 + n) * n / 2;

    // 2. Soma dos multiplos de A
    int qtd_a = n / a; 
    int ultimo_a = qtd_a * a; 
    int soma_a = (a + ultimo_a) * qtd_a / 2;

    // 3. Soma dos multiplos de B
    int qtd_b = n / b;
    int ultimo_b = qtd_b * b;
    int soma_b = (b + ultimo_b) * qtd_b / 2;

    // 4. Soma dos multiplos comuns (A * B)
    int m_comum = a * b;
    int soma_ab = 0;
    
    // Calcula apenas se o produto A*B for menor ou igual a N
    if (m_comum <= n) {
        int qtd_ab = n / m_comum;
        int ultimo_ab = qtd_ab * m_comum;
        soma_ab = (m_comum + ultimo_ab) * qtd_ab / 2;
    }

    // Calculo final ajustando os repetidos
    int resultado = soma_total - soma_a - soma_b + soma_ab;

    printf("%d\n", resultado);

    // Verificacao de par ou impar
    if (resultado % 2 == 0) {
        printf("L� ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...\n");
    }

    return 0;
}