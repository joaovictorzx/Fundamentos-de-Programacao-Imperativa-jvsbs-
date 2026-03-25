#include <stdio.h>

int main() {
    int total_clientes, multiplo_x, clientes_sistema;

    // leitura dos dados iniciais do problema
    scanf("%d", &total_clientes);
    scanf("%d", &multiplo_x);
    scanf("%d", &clientes_sistema);

    // vetor zerado para guardar a quantidade de latas de cada cliente
    // tamanho definido como 100000 para garantir espaco suficiente
    int latas_compradas[100000] = {0};

    // se x for maior que zero, marca-se 1 lata para os clientes que sao multiplos de x
    if (multiplo_x > 0) {
        for (int i = 1; i <= total_clientes; i++) {
            if (i % multiplo_x == 0) {
                latas_compradas[i] = 1;
            }
        }
    }

    // leitura dos clientes que compraram mais latas e tiveram o horario registrado
    for (int i = 0; i < clientes_sistema; i++) {
        int horas, minutos, quantidade;
        scanf("%d:%d %d", &horas, &minutos, &quantidade);

        // conversao do horario para o total de minutos passados desde as 07:00
        int minutos_passados = (horas * 60 + minutos) - (7 * 60);

        // a divisao por 3 define a posicao exata do cliente na fila
        int posicao_cliente = minutos_passados / 3;

        // atualizacao do numero de latas do cliente na respectiva posicao
        latas_compradas[posicao_cliente] = quantidade;
    }

    int total_acumulado = 0;
    int vencedor = -1;
    int latas_vencedor = 0;

    // iteracao por todos os clientes para somar as latas e verificar a meta de 50
    for (int i = 1; i <= total_clientes; i++) {
        total_acumulado += latas_compradas[i];

        if (total_acumulado >= 50) {
            vencedor = i;
            latas_vencedor = latas_compradas[i];
            break; // interrompe o laco ao encontrar o ganhador da cesta basica
        }
    }

    // impressao dos resultados
    if (vencedor != -1) {
        // calculo do horario de atendimento do vencedor de forma inversa
        int minutos_totais = (7 * 60) + (vencedor * 3);
        int hr_vencedor = minutos_totais / 60;
        int min_vencedor = minutos_totais % 60;

        // aplicacao das regras de plural exigidas na saida
        if (latas_vencedor == 1) {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.\n", vencedor, hr_vencedor, min_vencedor);
        } else {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", vencedor, hr_vencedor, min_vencedor, latas_vencedor);
        }
    } else {
        // execucao caso a meta de 50 latas nao seja atingida
        int faltam = 50 - total_acumulado;
        if (faltam == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n");
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }
    }

    return 0;
}