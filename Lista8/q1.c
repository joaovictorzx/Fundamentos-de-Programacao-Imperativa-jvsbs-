#include <stdio.h>

// estrutura para os campos do sensor, utilizando bit fields para otimizar o uso de memória
struct CamposSensor {
    unsigned char erro : 1;
    unsigned char modo: 3;
    unsigned char leitura: 4;
};

// definie a union para acessar os campos do sensor tanto como estrutura quanto como byte bruto
union RegistroSendor {
    struct CamposSensor campos;
    unsigned char byte_bruto;
};

int main(){
    union RegistroSendor sensor; //define a union como "sensor" na main
    int valor_entrada;

    // solicita ao usuário um valor inteiro para o sensor, garantindo que esteja no intervalo de 0 a 255
    printf("Digite um valor inteiro (0-255) para o sensor: ");
    scanf("%d", &valor_entrada);

    // colocando o valor de entrada no byte bruto da união, o que automaticamente preenche os campos da estrutura
    sensor.byte_bruto = (unsigned char)valor_entrada;

    // mostra os valores dos campos do sensor, mostrando o erro, modo e leitura
    printf("Byte bruto: %u | ", sensor.byte_bruto);
    printf("Erro: %u | ", sensor.campos.erro);
    printf("Modo: %u | ", sensor.campos.modo);
    printf("Leitura: %u", sensor.campos.leitura);

    return 0;
}