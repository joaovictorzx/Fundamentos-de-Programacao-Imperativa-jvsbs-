#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enumeracao para identificar os tipos elementais de forma padronizada
typedef enum
{
    FOGO = 0,
    AGUA = 1,
    ELETRICIDADE = 2,
    PLANTA = 3
} tipo_elemental;

// funcao auxiliar para converter o enum no formato de texto exigido pela saida
const char *obter_nome_tipo(tipo_elemental tipo)
{
    switch (tipo)
    {
    case FOGO:
        return "Fogo";
    case AGUA:
        return "Agua";
    case ELETRICIDADE:
        return "Eletricidade";
    case PLANTA:
        return "Planta";
    default:
        return "Desconhecido";
    }
}

// estrutura de dados aninhada para as entidades do sistema
typedef struct
{
    int id;
    char nome[50];
    tipo_elemental tipo;
    int xp;
    int ataque;
    int ordem_registro;
} pokemon;

typedef struct
{
    char nome[50];
    int cpf;
    int idade;
    pokemon *pokemons;
    int num_pokemons;
    int cap_pokemons;
    int nivel;
    int ordem_registro;
} treinador;

typedef struct
{
    treinador *treinadores;
    int num_treinadores;
    int cap_treinadores;
    int contador_treinadores;
    int contador_pokemons;
} sistema;

// prototipos de execucao
void impl_cadastrar_treinador(sistema *sys, char *nome, int cpf, int idade);
void impl_cadastrar_pokemon(sistema *sys, int cpf, int id_pokemon, char *nome, int xp, int ataque, int tipo);
void impl_listar(sistema *sys);
void impl_remover_treinador(sistema *sys, int cpf);
void impl_atualizar_pokemon(sistema *sys, int cpf, int id_pokemon, char *nome, int xp, int ataque, int tipo);

// requisito obrigatorio: estrutura contendo ponteiros de funcao para roteamento de comandos
typedef struct
{
    void (*cadastrar_treinador)(sistema *, char *, int, int);
    void (*cadastrar_pokemon)(sistema *, int, int, char *, int, int, int);
    void (*listar)(sistema *);
    void (*remover_treinador)(sistema *, int);
    void (*atualizar_pokemon)(sistema *, int, int, char *, int, int, int);
} gerenciador_operacoes;

// funcoes auxiliares de busca e calculo
int buscar_treinador(sistema *sys, int cpf)
{
    for (int i = 0; i < sys->num_treinadores; i++)
    {
        if (sys->treinadores[i].cpf == cpf)
        {
            return i;
        }
    }
    return -1;
}

int buscar_pokemon(treinador *t, int id)
{
    for (int i = 0; i < t->num_pokemons; i++)
    {
        if (t->pokemons[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void recalcular_nivel(treinador *t)
{
    int nivel_acumulado = 0;
    for (int i = 0; i < t->num_pokemons; i++)
    {
        nivel_acumulado += (2 * t->pokemons[i].xp) + t->pokemons[i].ataque;
    }
    t->nivel = nivel_acumulado;
}

// bloco de implementacao das funcoes acionadas pela interface de gerenciamento
void impl_cadastrar_treinador(sistema *sys, char *nome, int cpf, int idade)
{
    if (buscar_treinador(sys, cpf) != -1)
    {
        return; // ignora cadastro se o cpf ja existir
    }

    // realocacao dinamica caso o limite atual seja atingido
    if (sys->num_treinadores == sys->cap_treinadores)
    {
        sys->cap_treinadores = (sys->cap_treinadores == 0) ? 2 : sys->cap_treinadores * 2;
        sys->treinadores = (treinador *)realloc(sys->treinadores, sys->cap_treinadores * sizeof(treinador));
    }

    treinador *novo = &sys->treinadores[sys->num_treinadores];
    strcpy(novo->nome, nome);
    novo->cpf = cpf;
    novo->idade = idade;
    novo->num_pokemons = 0;
    novo->cap_pokemons = 2;
    novo->pokemons = (pokemon *)malloc(novo->cap_pokemons * sizeof(pokemon));
    novo->nivel = 0;

    novo->ordem_registro = sys->contador_treinadores++;
    sys->num_treinadores++;
}

void impl_cadastrar_pokemon(sistema *sys, int cpf, int id_pokemon, char *nome, int xp, int ataque, int tipo)
{
    int idx_treinador = buscar_treinador(sys, cpf);
    if (idx_treinador == -1)
        return;

    treinador *t = &sys->treinadores[idx_treinador];

    if (buscar_pokemon(t, id_pokemon) != -1)
        return;

    // expansao dinamica da lista aninhada de pokemons
    if (t->num_pokemons == t->cap_pokemons)
    {
        t->cap_pokemons *= 2;
        t->pokemons = (pokemon *)realloc(t->pokemons, t->cap_pokemons * sizeof(pokemon));
    }

    pokemon *novo = &t->pokemons[t->num_pokemons];
    novo->id = id_pokemon;
    strcpy(novo->nome, nome);
    novo->xp = xp;
    novo->ataque = ataque;
    novo->tipo = (tipo_elemental)tipo;
    novo->ordem_registro = sys->contador_pokemons++;
    t->num_pokemons++;

    recalcular_nivel(t);
}

// regras de ordenacao passadas para a funcao qsort da biblioteca stdlib
int comparar_pokemons(const void *a, const void *b)
{
    pokemon *p1 = (pokemon *)a;
    pokemon *p2 = (pokemon *)b;
    int forca1 = (2 * p1->xp) + p1->ataque;
    int forca2 = (2 * p2->xp) + p2->ataque;

    if (forca1 != forca2)
    {
        return forca2 - forca1;
    }
    return p1->ordem_registro - p2->ordem_registro;
}

int comparar_treinadores(const void *a, const void *b)
{
    treinador *t1 = (treinador *)a;
    treinador *t2 = (treinador *)b;

    if (t1->nivel != t2->nivel)
    {
        return t2->nivel - t1->nivel;
    }
    return t1->ordem_registro - t2->ordem_registro;
}

void impl_listar(sistema *sys)
{
    printf("Classificação atual\n");

    // ordenacao dos vetores principais baseada nas regras de comparacao
    qsort(sys->treinadores, sys->num_treinadores, sizeof(treinador), comparar_treinadores);

    for (int i = 0; i < sys->num_treinadores; i++)
    {
        treinador *t = &sys->treinadores[i];
        printf("T: %s, CPF: %d, Nivel: %d\n", t->nome, t->cpf, t->nivel);

        // ordenacao exclusiva do subvetor de pokemons do treinador atual
        if (t->num_pokemons > 0)
        {
            qsort(t->pokemons, t->num_pokemons, sizeof(pokemon), comparar_pokemons);
            for (int j = 0; j < t->num_pokemons; j++)
            {
                pokemon *p = &t->pokemons[j];
                printf("  P: %d, %s, %d, %d, %s\n", p->id, p->nome, p->xp, p->ataque, obter_nome_tipo(p->tipo));
            }
        }
    }
}

void impl_remover_treinador(sistema *sys, int cpf)
{
    int idx = buscar_treinador(sys, cpf);
    if (idx == -1)
        return;

    // libertacao da memoria aninhada associada ao subvetor de pokemons
    free(sys->treinadores[idx].pokemons);

    // deslocamento de memoria linear para suprimir a lacuna deixada
    for (int i = idx; i < sys->num_treinadores - 1; i++)
    {
        sys->treinadores[i] = sys->treinadores[i + 1];
    }
    sys->num_treinadores--;
}

void impl_atualizar_pokemon(sistema *sys, int cpf, int id_pokemon, char *nome, int xp, int ataque, int tipo)
{
    int idx_treinador = buscar_treinador(sys, cpf);
    if (idx_treinador == -1)
        return;

    treinador *t = &sys->treinadores[idx_treinador];
    int idx_pokemon = buscar_pokemon(t, id_pokemon);
    if (idx_pokemon == -1)
        return;

    // sobrescrita dos dados
    pokemon *p = &t->pokemons[idx_pokemon];
    strcpy(p->nome, nome);
    p->xp = xp;
    p->ataque = ataque;
    p->tipo = (tipo_elemental)tipo;

    recalcular_nivel(t);
}

// funcao isolada para saneamento total de memoria
void liberar_sistema(sistema *sys)
{
    for (int i = 0; i < sys->num_treinadores; i++)
    {
        free(sys->treinadores[i].pokemons);
    }
    free(sys->treinadores);
}

int main()
{
    // preparacao do modelo relacional e atribuicao dos atributos globais
    sistema sys;
    sys.cap_treinadores = 10;
    sys.treinadores = (treinador *)malloc(sys.cap_treinadores * sizeof(treinador));
    sys.num_treinadores = 0;
    sys.contador_treinadores = 0;
    sys.contador_pokemons = 0;

    // instanciacao da estrutura de gestao orientada a comandos
    gerenciador_operacoes ger;
    ger.cadastrar_treinador = impl_cadastrar_treinador;
    ger.cadastrar_pokemon = impl_cadastrar_pokemon;
    ger.listar = impl_listar;
    ger.remover_treinador = impl_remover_treinador;
    ger.atualizar_pokemon = impl_atualizar_pokemon;

    int operacao;
    while (scanf("%d", &operacao) == 1 && operacao != 0)
    {
        if (operacao == 1)
        {
            char nome[50];
            int cpf, idade;
            scanf("%s %d %d", nome, &cpf, &idade);
            ger.cadastrar_treinador(&sys, nome, cpf, idade);
        }
        else if (operacao == 2)
        {
            int cpf, id_pokemon, xp, ataque, tipo;
            char nome[50];
            scanf("%d %d %s %d %d %d", &cpf, &id_pokemon, nome, &xp, &ataque, &tipo);
            ger.cadastrar_pokemon(&sys, cpf, id_pokemon, nome, xp, ataque, tipo);
        }
        else if (operacao == 3)
        {
            ger.listar(&sys);
        }
        else if (operacao == 4)
        {
            int cpf;
            scanf("%d", &cpf);
            ger.remover_treinador(&sys, cpf);
        }
        else if (operacao == 5)
        {
            int cpf, id_pokemon, xp, ataque, tipo;
            char nome[50];
            scanf("%d %d %s %d %d %d", &cpf, &id_pokemon, nome, &xp, &ataque, &tipo);
            ger.atualizar_pokemon(&sys, cpf, id_pokemon, nome, xp, ataque, tipo);
        }
    }

    // processo de desmontagem e devolucao da memoria dinamica ao sistema operativo
    liberar_sistema(&sys);
    return 0;
}
