#include <stdio.h>

int main() {
    int q;
    scanf("%d", &q);

    int col = 0;
    int invalido = 0;
    int cursor_colocado = 0;
    int pending_b = 0;

    for (int i = 0; i < q; i++) {
        int s;
        char d;
        scanf("%d %c", &s, &d);

        if (invalido) {
            continue;
        }

        if (d == 'D') {
            if (cursor_colocado == 0) {
                for (int j = 0; j < s; j++) {
                    printf(".");
                }
                printf("\n");
                col = s - 1;
                cursor_colocado = 1;
            } else {
                for (int j = 0; j < col; j++) {
                    printf(" ");
                }
                for (int j = 0; j <= s; j++) {
                    printf(".");
                }
                printf("\n");
                col = col + s;
            }
            pending_b = 0;
        } else if (d == 'E') {
            if (cursor_colocado == 0) {
                printf("Informacao invalida\n");
                invalido = 1;
                continue;
            } else if (col - s < 0) {
                printf("Informacao invalida\n");
                invalido = 1;
                continue;
            } else {
                col = col - s;
                for (int j = 0; j < col; j++) {
                    printf(" ");
                }
                for (int j = 0; j <= s; j++) {
                    printf(".");
                }
                printf("\n");
            }
            pending_b = 0;
        } else if (d == 'B') {
            if (cursor_colocado == 0) {
                col = 0;
                cursor_colocado = 1;
            }
            for (int j = 0; j < s - 1; j++) {
                for (int k = 0; k < col; k++) {
                    printf(" ");
                }
                printf(".\n");
            }
            pending_b = 1;
        }
    }

    if (invalido == 0 && pending_b == 1) {
        for (int k = 0; k < col; k++) {
            printf(" ");
        }
        printf(".\n");
    }

    return 0;
}