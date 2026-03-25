#include <stdio.h>

int main() {
    int n, k, p;
    
    scanf("%d %d %d", &n, &k, &p);
    
    int primeiro_valido = -1;
    int total_encontrados = 0;

    for (int i = n; i < k; i++) {
        
        int num = i;
        
        while (num % 2 == 0) {
           num = num / 2;
        }
        
        int fatores = 0; // conta quantos fatores impares distintos achou
        int valido = 1;  // bandeira para sinalizar se encontrar um fator que se repete
        
        for (int div = 3; div <= num; div = div + 2) { // laco para dividir por impares: 3, 5, 7...
            
            if (num % div == 0) {
                fatores++; // conta que achou um divisor
                num = num / div; // faz a divisao real
                
                // checa se o fator repetiu logo em seguida
                if (num % div == 0) {
                    valido = 0; // invalido
                    break;      // para o laco de divisao, ja que nao serve
                }
            }
        }
        
        if (valido == 1 && fatores == p) {
            total_encontrados++; // conta mais um
        
            // se o primeiro_valido ainda for -1, significa que esse e o primeirao de todos
            if (primeiro_valido == -1) {
                primeiro_valido = i;
            }
        }
    }
    
    if (total_encontrados > 0) {
    // subtrai 1 para n�o contar o "primeiro_valido" de novo
    printf("%d %d\n", primeiro_valido, total_encontrados - 1); 
} else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }
    
    return 0;
}