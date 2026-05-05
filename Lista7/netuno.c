#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[]; 
};

// --- ROTINAS DE COMBATE ---

void rotina_defesa(Mecha *m, int slot, int input, int *output) {
    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    
    *output = input - atrib1 - (slot * atrib2);
    if (*output < 0) *output = 0;
    
    printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[slot].nome, *output);
}

void rotina_utilidade(Mecha *m, int slot, int input, int *output) {
    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    
    int recuperado = atrib1 + (slot * atrib2);
    m->energia_atual += recuperado;
    
    printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[slot].nome, m->energia_atual);
}

void rotina_ataque(Mecha *m, int slot, int input, int *output) {
    int atrib1 = m->sistemas[slot].atrib1;
    int atrib2 = m->sistemas[slot].atrib2;
    
    if (m->energia_atual < atrib2) {
        printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[slot].nome);
    } else {
        *output = atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= atrib2;
        printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[slot].nome, *output, m->energia_atual);
    }
}

int comparar_mecha(const void *a, const void *b) {
    Mecha *m1 = *(Mecha **)a;
    Mecha *m2 = *(Mecha **)b;
    return m1->id - m2->id;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Mecha **esquadrao = malloc(n * sizeof(Mecha*));

    for (int i = 0; i < n; i++) {
        int id, energia_inicial, q;
        char modelo[50];
        
        scanf("%d %s %d %d", &id, modelo, &energia_inicial, &q);

        Mecha *m = malloc(sizeof(Mecha) + q * sizeof(SubSistema));
        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia_inicial;
        m->num_sistemas = q;

        for (int s = 0; s < q; s++) {
            char tipo;
            scanf(" %c %s %d %d", &tipo, m->sistemas[s].nome, &m->sistemas[s].atrib1, &m->sistemas[s].atrib2);
            
            if (tipo == 'D') m->sistemas[s].subrotina = rotina_defesa;
            else if (tipo == 'U') m->sistemas[s].subrotina = rotina_utilidade;
            else if (tipo == 'A') m->sistemas[s].subrotina = rotina_ataque;
        }

        scanf("%d", &m->valor_wintermute);
        esquadrao[i] = m;
    }

    qsort(esquadrao, n, sizeof(Mecha*), comparar_mecha);

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < n; i++) {
        Mecha *m = esquadrao[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        int dummy;
        for (int s = 0; s < m->num_sistemas; s++) 
            if (m->sistemas[s].subrotina == rotina_defesa) m->sistemas[s].subrotina(m, s, m->valor_wintermute, &dummy);
        
        for (int s = 0; s < m->num_sistemas; s++) 
            if (m->sistemas[s].subrotina == rotina_utilidade) m->sistemas[s].subrotina(m, s, m->valor_wintermute, &dummy);
        
        for (int s = 0; s < m->num_sistemas; s++) 
            if (m->sistemas[s].subrotina == rotina_ataque) m->sistemas[s].subrotina(m, s, m->valor_wintermute, &dummy);

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        // Linha de separacao
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    for (int i = 0; i < n; i++) free(esquadrao[i]);
    free(esquadrao);

    return 0;
}