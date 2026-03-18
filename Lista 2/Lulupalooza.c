#include <stdio.h>

int main() {
    // variaveis globais para guardar o vencedo
    int melhor_dist_geral = 999999;
    int melhor_canal = -1;
    int melhor_minuto_geral = -1;
    int termo_vencedor = -1;

    // le o numero de xupenio e a quantidade de canais
    int x, n;
    scanf("%d %d", &x, &n);

    // laco para passar por todos os canais
    for (int i = 1; i <= n; i++) {
        // le os dois primeiros numeros do canal atual
        int a, b;
        scanf("%d %d", &a, &b);

        // variaveis locais
        int melhor_dist_canal = 999999;
        int melhor_min_canal = -1;
        int termo_canal = -1;

        // calcula a distancia do primeiro minuto
        int dist_a = a - x;
        if (dist_a < 0) {
            dist_a = dist_a * -1;
        }
        
        // o primeiro assume como melhor provisorio do canal
        melhor_dist_canal = dist_a;
        melhor_min_canal = 1;
        termo_canal = a;

        // calcula a distancia do segundo minuto
        int dist_b = b - x;
        if (dist_b < 0) {
            dist_b = dist_b * -1;
        }
        
        // atualiza se for estritamente menor para priorizar o menor minuto no empate
        if (dist_b < melhor_dist_canal) {
            melhor_dist_canal = dist_b;
            melhor_min_canal = 2;
            termo_canal = b;
        }

        // prepara para calcular o restante da sequencia
        int minuto_atual = 3;
        int anterior = a;
        int atual = b;

        // laco infinito quebrado quando o numero passa de x
        while (1) {
            int proximo = anterior + atual;
            
            int dist_c = proximo - x;
            if (dist_c < 0) {
                dist_c = dist_c * -1;
            }

            // verifica se a nova distancia e melhor
            if (dist_c < melhor_dist_canal) {
                melhor_dist_canal = dist_c;
                melhor_min_canal = minuto_atual;
                termo_canal = proximo;
            } else if (proximo > x) {
                // para o laco pois os numeros so vao crescer e se afastar de x
                break;
            }

            // atualiza os valores das variaveis para a proxima repeticao do laco
            anterior = atual;
            atual = proximo;
            minuto_atual++;
        }

        // compara o melhor do canal com o melhor geral
        if (melhor_dist_canal <= melhor_dist_geral) {
            melhor_dist_geral = melhor_dist_canal;
            melhor_canal = i;
            melhor_minuto_geral = melhor_min_canal;
            termo_vencedor = termo_canal;
        }
    }

    // descobre se o ingresso e vip somando os digitos
    int soma_digitos = 0;
    int temp = termo_vencedor;
    
    // laco para separar e somar cada digito ate o numero zerar
    while (temp > 0) {
        soma_digitos = soma_digitos + (temp % 10);
        temp = temp / 10;
    }

    // imprime a resposta final baseada na regra do vip
    if (soma_digitos > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhor_canal, melhor_minuto_geral);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", melhor_canal, melhor_minuto_geral);
    }

    return 0;
}