#include <stdio.h>

int main() {
    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);

    // Variaveis de controle
    int q_atual, q_destino;
    int dest_x, dest_y;
    int q_x_primeiro, q_y_primeiro;

    // Identificacao dos quadrantes e destinos
    if (x > 0 && y > 0) {
        q_atual = 1;
        q_destino = 3;
        dest_x = -1;
        dest_y = -1;
        q_x_primeiro = 2; // Passa pelo Q2 se mover X primeiro
        q_y_primeiro = 4; // Passa pelo Q4 se mover Y primeiro
    } else if (x < 0 && y > 0) {
        q_atual = 2;
        q_destino = 4;
        dest_x = 1;
        dest_y = -1;
        q_x_primeiro = 1;
        q_y_primeiro = 3;
    } else if (x < 0 && y < 0) {
        q_atual = 3;
        q_destino = 1;
        dest_x = 1;
        dest_y = 1;
        q_x_primeiro = 4;
        q_y_primeiro = 2;
    } else if (x > 0 && y < 0) {
        q_atual = 4;
        q_destino = 2;
        dest_x = -1;
        dest_y = 1;
        q_x_primeiro = 3;
        q_y_primeiro = 1;
    } else {
        printf("caminhada invalida\n");
        return 0;
    }

    // Verifica se o quadrante a evitar e o de inicio ou o destino
    if (c == q_atual || c == q_destino) {
        printf("caminhada invalida\n");
    } else {
        // Calculo da distancia absoluta (sem usar funcoes prontas)
        int passos_x = x - dest_x;
        if (passos_x < 0) passos_x = -passos_x;

        int passos_y = y - dest_y;
        if (passos_y < 0) passos_y = -passos_y;

        // Decisao do caminho
        if (c == q_x_primeiro) {
            // Se mover X primeiro cai no quadrante evitado, move Y primeiro
            printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
        } else if (c == q_y_primeiro) {
            // Se mover Y primeiro cai no quadrante evitado, move X primeiro
            printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
        } else {
            // Se c nao for adjacente
            printf("caminhada invalida\n");
        }
    }

    return 0;
}