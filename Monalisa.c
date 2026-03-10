#include <stdio.h>

int main()
{
    int d1, m1, a1, d2, m2, a2;
    scanf ("%d %d %d %d %d %d", &d1, &m1, &a1, &d2, &m2, &a2);

    //amor
    // Regra: Somar tudo, multiplicar por 7 e tirar o resto de 101
    int soma_amor = d1 + m1 + a1 + d2 + m2 + a2;
    int resultado_soma_amor = (soma_amor * 7) % 101;

    if (resultado_soma_amor > 20) {
        printf ("Amor %d%%: Pessimo dia para se apaixonar.", resultado_soma_amor);
    } else if (resultado_soma_amor > 20 && resultado_soma_amor < 40) {
        printf ("Amor %d%%: Melhor manter o coracao <3 longe de perigo.", resultado_soma_amor); 
    } else if (resulto_soma_amor > 40 && resultado_soma_amor < 69) { 
        printf ("Amor %d%%: Se o papo e as ideias baterem, esta liberado pensar em algo.", resultado_soma_amor);
    } else if (resultado_soma_amor > 69 && resultado_soma_amor < 80) {
        printf ("Amor %d%%: Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.", resultado_soma_amor);
    } else {
        printf ("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.", resultado_soma_amor);
    }

    //sorte
    // Regra: (Soma dias + meses*9 + diferença anos) resto 101
    int dif_anos = a2 - a1;
    if (dif_anos < 0) {
        dif_anos = dif_anos * -1;
    }

    int sorte = (d1 + d2 + (m1 + m2) * 9 + diff_anos) % 101;

    printf("Sorte: %d%% ", sorte);
    if (sorte<30){
        printf("Nem jogue moedas pra cima hoje. ");
    } else if (sorte <= 50) {
        printf("Melhor nao arriscar. ");
    } else if (sorte <= 79) {
        printf("Por sua conta em risco. ");
    } else if (sorte<=90) {
        printf("Hoje vale a pena arriscar. ");
    } else {
        printf("Nao tenha medo de virar cartas hoje. ");
    } 
    printf("Sem tigrinho nem jogos de azar, por favor!\n");


    //trabalho
    // Regra: (Soma anos - (dias+meses)*8) resto 101
    int trabalho = ((a1 + a2) - (d1 + d2 + m1 + m2) * 8) % 101;    
    if (trabalho < 0) {
        trabalho = trabalho + 101;
    }
    printf("Trabalho: %d%% ", trabalho);
    if (trabalho < 40) {
        printf("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n");
    } else if (trbalho <= 50) {
        printf ("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n");
    } else if (trabalho <= 69) {
        printf("Um dia proveitoso com certeza, leve sua simpatia consigo.\n");
    } else if (trabalho <= 84) {
        printf("Boas vibracoes hoje, chances podem estar ao seu redor.\n");
    } else {
        printf("Use do maximo de networking possível hoje, dia bom para negocios.\n");
    }


    //cor
    // Regra: Soma dos quadrados resto 11
    int cor = ((d1 * d1) + (m1 * m1) + (a1 * a1) + (d2 * d2) + (m2 * m2) + (a2 * a2)) % 11;

    printf("Cor: ");
    switch (cor) { 
        case 0: printf("Cinza\n"); break;
        case 1: printf("Vermelho\n"); break;
        case 2: printf("Laranja\n"); break;
        case 3: printf("Amarelo\n"); break;
        case 4: printf("Verde\n"); break;
        case 5: printf("Azul\n"); break;
        case 6: printf("Roxo\n"); break;
        case 7: printf("Marrom\n"); break;
        case 8: printf("Rosa\n"); break;
        case 9: printf("Preto\n"); break;
        case 10: printf("Branco\n"); break;
    }

    return 0;
}