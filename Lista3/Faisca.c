#include <stdio.h>

int main()
{
    int numero_casos;
    scanf("%d", &numero_casos);

    // vetor dimensionado para armazenar todos os fios e ornamentos
    char luz_gigante[100000];
    int tamanho_gigante = 0;

    // iteracao sobre cada caso de teste
    for (int i = 0; i < numero_casos; i++)
    {
        char fio[100];
        int flashs;

        // leitura da string e do inteiro padrao
        scanf("%s %d", fio, &flashs);

        // simulacao do efeito dos flashs via soma binaria para otimizacao de tempo
        int carry = flashs;

        for (int j = 0; fio[j] != '\0'; j++)
        {
            // conversao do caractere para o valor numerico 0 ou 1
            int estado_atual = (fio[j] == 'X') ? 0 : 1;

            // soma do estado atual com a quantidade de flashs acumulados
            int soma = estado_atual + carry;

            // atualizacao do led: soma impar resulta em ligado, soma par em desligado
            if (soma % 2 == 1)
            {
                fio[j] = 'O';
            }
            else
            {
                fio[j] = 'X';
            }

            // calculo do excedente transferido para o proximo led da sequencia
            carry = soma / 2;
        }

        // impressao do estado final do fio isolado
        printf("%s\n", fio);

        // conexao com a luz gigante e insercao do ornamento pertinente
        if (tamanho_gigante > 0)
        {
            char ultimo_gigante = luz_gigante[tamanho_gigante - 1];
            char primeiro_novo = fio[0];

            int tamanho_par = (tamanho_gigante % 2 == 0);
            int estados_iguais = (ultimo_gigante == primeiro_novo);

            // selecao do ornamento de acordo com as condicoes estabelecidas
            if (tamanho_par && estados_iguais)
            {
                luz_gigante[tamanho_gigante] = '@';
            }
            else if (!tamanho_par && estados_iguais)
            {
                luz_gigante[tamanho_gigante] = '#';
            }
            else if (tamanho_par && !estados_iguais)
            {
                luz_gigante[tamanho_gigante] = '$';
            }
            else
            {
                luz_gigante[tamanho_gigante] = '%';
            }
            // incremento do tamanho apos a adicao do ornamento
            tamanho_gigante++;
        }

        // concatenacao do fio atual ao final da luz gigante
        for (int j = 0; fio[j] != '\0'; j++)
        {
            luz_gigante[tamanho_gigante] = fio[j];
            tamanho_gigante++;
        }
    }

    // insercao do caractere nulo e impressao da string finalizada
    luz_gigante[tamanho_gigante] = '\0';
    printf("%s\n", luz_gigante);

    return 0;
}