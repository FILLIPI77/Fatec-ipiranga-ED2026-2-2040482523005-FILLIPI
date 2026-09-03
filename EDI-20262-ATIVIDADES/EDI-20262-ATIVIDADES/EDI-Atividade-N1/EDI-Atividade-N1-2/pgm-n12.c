#include <stdio.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

/* O vetor e global porque as funcoes devem acessa-lo sem recebe-lo como parametro. */
int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void) {
    printf("=================================\n");
    printf("SISTEMA DE ESTOQUE - LOJA CONSTRUMAIS\n");
    printf("=================================\n");
}

void preencherEstoque(void) {
    int *p = estoque;

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", (p + i));
    }
}

void exibirEstoque(int momento) {
    int *p = estoque;

    if (momento == 0) {
        printf("–- Estoque atual (antes da reposicao) –-\n");
    } else {
        printf("–- Estoque final (apos reposicao) –-\n");
    }

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d unidades\n", i + 1, *(p + i));
    }
}

float calcularMediaEstoque(void) {
    int *p = estoque;
    int soma = 0;

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        soma += *(p + i);
    }

    /* p + i e o endereco do elemento; *(p + i) e o valor armazenado nesse endereco. */
    return (float)soma / TAMANHO_ESTOQUE;
}

void simularReposicao(int quantidadeAtual, int reposicao) {
    printf("–- Simulacao de reposicao (passagem por valor) –-\n");
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n",
           quantidadeAtual, reposicao, quantidadeAtual + reposicao);
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", estoque[0]);
}

void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        *(p + i) += reposicao;
    }

    printf("–- Aplicacao real da reposicao (ponteiro interno ao vetor global) –-\n");
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);
}

void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    int encontrouCritico = 0;

    printf("–- Analise de estoque critico (minimo = %d unidades) –-\n", minimo);

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n",
                   i + 1, *(p + i));
            encontrouCritico = 1;
        }
    }

    if (!encontrouCritico) {
        printf("Estoque regularizado: nenhum produto esta abaixo do minimo.\n");
    }
}

int main(void) {
    int reposicao;
    float media;

    exibirCabecalho();
    preencherEstoque();

    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);

    exibirEstoque(0);

    simularReposicao(estoque[0], reposicao);

    aplicarReposicaoGeral(reposicao);

    exibirEstoque(1);

    printf("–- Media geral do estoque –-\n");
    media = calcularMediaEstoque();
    printf("Media final: %.2f unidades\n", media);

    identificarEstoqueCritico(ESTOQUE_MINIMO);

    return 0;
}