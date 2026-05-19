#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // para usar uint32_t

// estrutura de 32 bits
struct PacoteCampos
{
    unsigned int id_sensor : 10;
    unsigned int status : 3;
    unsigned int bateria : 1;
    int temperatura : 12; // int normal para comportar valores negativos
    unsigned int controle : 6;
};

// union para sobrepor o numero hexadecimal e a estrutura fatiada
union PacoteTelemetria
{
    uint32_t dado_bruto;
    struct PacoteCampos campos;
};


int main()
{
    // configurar o vetor dinâmico
    int tamanho_max = 2;
    int tamanho_atual = 0;

    // alocar memória para o vetor dinâmico
    union PacoteTelemetria *vetor_pacotes = malloc(tamanho_max * sizeof(union PacoteTelemetria));

    if (vetor_pacotes == NULL)
    {
        printf("Erro ao alocar memoria inicial.\n");
        return 1;
    }

    uint32_t entrada_hex;

    // leitura até receber 0
    while (1)
    {
        scanf("%x", &entrada_hex);

        // condição de parada
        if (entrada_hex == 0)
        {
            break; // sair do loop se a entrada for 0
        }

        // verificar se é necessário redimensionar o vetor
        if (tamanho_atual == tamanho_max)
        {
            tamanho_max *= 2; // dobra o tamnho

            // esticar o espaço de memória
            union PacoteTelemetria *temp = realloc(vetor_pacotes, tamanho_max * sizeof(union PacoteTelemetria));

            if (temp == NULL)
            {
                printf("Erro ao redimensionar memoria.\n");
                free(vetor_pacotes);
                return 1;
            }
            vetor_pacotes = temp; // atualizar o ponteiro para o novo espaço de memória
        }

        // armazenar o dado bruto no vetor
        vetor_pacotes[tamanho_atual].dado_bruto = entrada_hex;
        tamanho_atual++; // incrementar o tamanho atual
    }

    // imprimir os campos de cada pacote
    printf("\n"); // espaçamento para separar entrada da saída
    for (int i = 0; i < tamanho_atual; i++)
    {
        // exibe o número do pacote e o valor em hexa com 8 dígitos e padding zero (%08X)
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, vetor_pacotes[i].dado_bruto);
        printf("ID do Sensor : %d\n", vetor_pacotes[i].campos.id_sensor);
        printf("Status : %d\n", vetor_pacotes[i].campos.status);

        // operador para formatar a string de Bateria Baixa
        if (vetor_pacotes[i].campos.bateria == 1)
        {
            printf("Bateria Baixa: SIM (ALERTA)\n");
        }
        else
        {
            printf("Bateria Baixa: Nao\n");
        }

        printf("Temperatura : %d graus\n", vetor_pacotes[i].campos.temperatura);
        printf("--------------------------------------------------\n");
    }

    // libertação da memória alocada para o vetor de pacotes
    free(vetor_pacotes);

    return 0;
}