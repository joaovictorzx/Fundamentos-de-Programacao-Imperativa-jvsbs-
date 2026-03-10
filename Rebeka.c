#include <stdio.h>

int main() {
    int total, px, py, pz;
    
    // Leitura do dinheiro total e das tres porcentagens
    scanf("%d", &total);
    scanf("%d %d %d", &px, &py, &pz);

    // Variaveis de controle
    // investiu = -1 significa que ainda nao achamos uma divisao valida
    int investiu = -1; 
    int a = 0, b = 0, c = 0, sobra = 0;

    // 1. Tenta investir 0 reais
    if ((total * px) % 100 == 0 && (total * py) % 100 == 0 && (total * pz) % 100 == 0) {
        investiu = 0;
        a = (total * px) / 100;
        b = (total * py) / 100;
        c = (total * pz) / 100;
        sobra = total - (a + b + c);
    } 
    // 2. Tenta investir 1 real
    else if (((total + 1) * px) % 100 == 0 && ((total + 1) * py) % 100 == 0 && ((total + 1) * pz) % 100 == 0) {
        int t = total + 1;
        int ta = (t * px) / 100;
        int tb = (t * py) / 100;
        int tc = (t * pz) / 100;
        int t_sobra = t - (ta + tb + tc);
        
        // Precisa sobrar pelo menos 1 nota a mais do que investiu (1 + 1 = 2)
        if (t_sobra >= 2) {
            investiu = 1;
            a = ta; b = tb; c = tc; sobra = t_sobra;
        }
    }

    // 3. Tenta investir 2 reais 
    // Usa if isolado caso as contas acima falhem na condicao da sobra minima
    if (investiu == -1) {
        int t = total + 2;
        if ((t * px) % 100 == 0 && (t * py) % 100 == 0 && (t * pz) % 100 == 0) {
            int ta = (t * px) / 100;
            int tb = (t * py) / 100;
            int tc = (t * pz) / 100;
            int t_sobra = t - (ta + tb + tc);
            
            if (t_sobra >= 3) {
                investiu = 2;
                a = ta; b = tb; c = tc; sobra = t_sobra;
            }
        }
    }

    // 4. Tenta investir 3 reais
    if (investiu == -1) {
        int t = total + 3;
        if ((t * px) % 100 == 0 && (t * py) % 100 == 0 && (t * pz) % 100 == 0) {
            int ta = (t * px) / 100;
            int tb = (t * py) / 100;
            int tc = (t * pz) / 100;
            int t_sobra = t - (ta + tb + tc);
            
            if (t_sobra >= 4) {
                investiu = 3;
                a = ta; b = tb; c = tc; sobra = t_sobra;
            }
        }
    }

    // --- SAIDA DA DIVISAO ---
    if (investiu == -1) {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    } else {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
    }

    // --- DESAFIOS EXTRAS ---
    // Executa os desafios caso a condicao de investir 2 ou 3 tenha dado certo
    if (investiu == 2) {
        char l1, l2, l3;
        // O espaco no %c ignora quebras de linha anteriores
        scanf(" %c %c %c", &l1, &l2, &l3);
        
        // Transforma em minuscula caso a entrada seja maiuscula
        if (l1 >= 'A' && l1 <= 'Z') l1 = l1 + 32;
        if (l2 >= 'A' && l2 <= 'Z') l2 = l2 + 32;
        if (l3 >= 'A' && l3 <= 'Z') l3 = l3 + 32;

        int soma = (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1);
        printf("%d\n", soma);
        
    } else if (investiu == 3) {
        int id1, id2, id3;
        scanf("%d %d %d", &id1, &id2, &id3);
        
        int parcelas = 0;
        if (id1 % 3 == 0 || id2 % 3 == 0 || id3 % 3 == 0) {
            parcelas = (id1 / 3) + (id2 / 3) + (id3 / 3);
        }
        printf("%d\n", parcelas);
    }

    // --- FIM DA NOITE DE REBEKA ---
    int dinheiro_final = 3; // Dinheiro inicial que ela acordou
    if (investiu != -1) {
        dinheiro_final = 3 - investiu + sobra;
    }

    if (dinheiro_final >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}