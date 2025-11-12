#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

// --------------------
// ESTRUTURAS
// --------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// --------------------
// VARIÁVEIS GLOBAIS
// --------------------
int comparacoes = 0;

// --------------------
// FUNÇÕES AUXILIARES
// --------------------
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --------------------
// FUNÇÕES PARA VETOR DE ITENS
// --------------------
void inserirItemVetor(Item mochila[], int *n) {
    if (*n >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    printf("\n--- Inserir novo item ---\n");
    printf("Nome: ");
    limparBuffer();
    fgets(mochila[*n].nome, 30, stdin);
    mochila[*n].nome[strcspn(mochila[*n].nome, "\n")] = 0;

    printf("Tipo (arma, munição, cura): ");
    fgets(mochila[*n].tipo, 20, stdin);
    mochila[*n].tipo[strcspn(mochila[*n].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[*n].quantidade);

    (*n)++;
    printf("Item adicionado com sucesso!\n");
}

void listarItens(Item mochila[], int n) {
    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (n == 0)
        printf("Mochila vazia!\n");
}

void removerItemVetor(Item mochila[], int *n) {
    if (*n == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    char nome[30];
    printf("\nNome do item a remover: ");
    limparBuffer();
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *n - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*n)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado)
        printf("Item não encontrado!\n");
}

int buscarSequencialVetor(Item mochila[], int n, char nome[]) {
    comparacoes = 0;
    for (int i = 0; i < n; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Bubble sort por nome
void ordenarVetorPorNome(Item mochila[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome (Bubble Sort). Comparações: %d\n", comparacoes);
}

int buscaBinariaVetor(Item mochila[], int n, char nome[]) {
    comparacoes = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// --------------------
// FUNÇÕES PARA LISTA ENCADEADA
// --------------------
void inserirItemLista(No **inicio) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) return;

    printf("\n--- Inserir novo item (Lista) ---\n");
    printf("Nome: ");
    limparBuffer();
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item adicionado à lista!\n");
}

void listarItensLista(No *inicio) {
    printf("\n--- Itens na lista ---\n");
    No *atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n", i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    if (i == 1)
        printf("Lista vazia!\n");
}

void removerItemLista(No **inicio) {
    if (!*inicio) {
        printf("\nLista vazia!\n");
        return;
    }
    char nome[30];
    printf("\nNome do item a remover: ");
    limparBuffer();
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    No *atual = *inicio, *anterior = NULL;
    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Item não encontrado!\n");
        return;
    }

    if (!anterior)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
}

void buscarItemLista(No *inicio, char nome[]) {
    comparacoes = 0;
    No *atual = inicio;
    while (atual) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado!\nComparações: %d\n", comparacoes);
}

// --------------------
// FASE FINAL - TORRE DE RESGATE
// --------------------

// Bubble Sort por nome
void bubbleSortNome(Componente c[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(c[j].nome, c[j + 1].nome) > 0) {
                Componente temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente c[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = c[i];
        int j = i - 1;
        while (j >= 0 && strcmp(c[j].tipo, key.tipo) > 0) {
            c[j + 1] = c[j];
            j--;
            comparacoes++;
        }
        c[j + 1] = key;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente c[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (c[j].prioridade < c[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
}

int buscaBinariaComponente(Componente c[], int n, char nome[]) {
    int ini = 0, fim = n - 1;
    comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(c[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void mostrarComponentes(Componente c[], int n) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++)
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n", i + 1, c[i].nome, c[i].tipo, c[i].prioridade);
}

void faseFinal() {
    Componente c[MAX_COMPONENTES];
    int n = 0, opc;
    char nomeBusca[30];
    clock_t inicio, fim;

    do {
        printf("\n===== FASE FINAL - TORRE DE RESGATE =====\n");
        printf("1. Inserir componente\n");
        printf("2. Ordenar por nome (Bubble)\n");
        printf("3. Ordenar por tipo (Insertion)\n");
        printf("4. Ordenar por prioridade (Selection)\n");
        printf("5. Buscar componente (Binária por nome)\n");
        printf("6. Listar componentes\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
        case 1:
            if (n >= MAX_COMPONENTES) {
                printf("Limite atingido!\n");
                break;
            }
            printf("Nome: ");
            limparBuffer();
            fgets(c[n].nome, 30, stdin);
            c[n].nome[strcspn(c[n].nome, "\n")] = 0;
            printf("Tipo: ");
            fgets(c[n].tipo, 20, stdin);
            c[n].tipo[strcspn(c[n].tipo, "\n")] = 0;
            printf("Prioridade (1-10): ");
            scanf("%d", &c[n].prioridade);
            n++;
            break;
        case 2:
            inicio = clock();
            bubbleSortNome(c, n);
            fim = clock();
            printf("Bubble Sort concluído! Comparações: %d | Tempo: %.6fs\n", comparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        case 3:
            inicio = clock();
            insertionSortTipo(c, n);
            fim = clock();
            printf("Insertion Sort concluído! Comparações: %d | Tempo: %.6fs\n", comparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        case 4:
            inicio = clock();
            selectionSortPrioridade(c, n);
            fim = clock();
            printf("Selection Sort concluído! Comparações: %d | Tempo: %.6fs\n", comparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        case 5:
            printf("Nome a buscar: ");
            limparBuffer();
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;
            inicio = clock();
            int pos = buscaBinariaComponente(c, n, nomeBusca);
            fim = clock();
            if (pos >= 0)
                printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n", c[pos].nome, c[pos].tipo, c[pos].prioridade);
            else
                printf("Componente não encontrado.\n");
            printf("Comparações: %d | Tempo: %.6fs\n", comparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
            break;
        case 6:
            mostrarComponentes(c, n);
            break;
        }
    } while (opc != 0);
}

// --------------------
// MENU PRINCIPAL
// --------------------
int main() {
    Item mochila[MAX_ITENS];
    No *inicio = NULL;
    int n = 0;
    int opc, estrutura;

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE MOCHILA =====\n");
        printf("1. Usar vetor\n");
        printf("2. Usar lista encadeada\n");
        printf("3. Fase final - Torre de Resgate\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &estrutura);

        switch (estrutura) {
        case 1:
            do {
                printf("\n--- Mochila (Vetor) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (sequencial)\n");
                printf("5. Ordenar por nome\n");
                printf("6. Buscar item (binária)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opc);
                char nome[30];
                int pos;

                switch (opc) {
                case 1: inserirItemVetor(mochila, &n); break;
                case 2: removerItemVetor(mochila, &n); break;
                case 3: listarItens(mochila, n); break;
                case 4:
                    printf("Nome a buscar: ");
                    limparBuffer();
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    pos = buscarSequencialVetor(mochila, n, nome);
                    if (pos >= 0)
                        printf("Encontrado: %s | Tipo: %s | Quantidade: %d\n", mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                    else
                        printf("Item não encontrado.\n");
                    printf("Comparações: %d\n", comparacoes);
                    break;
                case 5: ordenarVetorPorNome(mochila, n); break;
                case 6:
                    printf("Nome a buscar: ");
                    limparBuffer();
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    pos = buscaBinariaVetor(mochila, n, nome);
                    if (pos >= 0)
                        printf("Encontrado: %s | Tipo: %s | Quantidade: %d\n", mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                    else
                        printf("Item não encontrado.\n");
                    printf("Comparações: %d\n", comparacoes);
                    break;
                }
            } while (opc != 0);
            break;

        case 2:
            do {
                printf("\n--- Mochila (Lista Encadeada) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opc);
                char nome[30];

                switch (opc) {
                case 1: inserirItemLista(&inicio); break;
                case 2: removerItemLista(&inicio); break;
                case 3: listarItensLista(inicio); break;
                case 4:
                    printf("Nome a buscar: ");
                    limparBuffer();
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    buscarItemLista(inicio, nome);
                    break;
                }
            } while (opc != 0);
            break;

        case 3:
            faseFinal();
            break;
        }

    } while (estrutura != 0);

    printf("\nJogo encerrado. Boa sorte na próxima partida!\n");
    return 0;
