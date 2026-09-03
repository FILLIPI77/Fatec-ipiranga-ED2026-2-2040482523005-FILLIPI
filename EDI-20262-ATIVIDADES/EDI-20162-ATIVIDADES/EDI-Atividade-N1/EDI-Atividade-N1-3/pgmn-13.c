#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* - - - - - - - - -- - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - -*
 * Disciplina : Estrutura de Dados                                                                 *
 * Prof . Verissimo                                                                                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Objetivo do Programa : Controlar os atendimentos de veiculos de um lava-rapido,                 *
 *                        utilizando alocacao dinamica de memoria e recursividade                  *
 * Data - 01/09/2026                                                                                *
 * Autor : Fillipi Franco                                                                           *
 * - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - -*/

#define VALOR_PREMIUM 100.0

typedef struct {
    char placa[8];
    float valor;
} Veiculo;

void exibirCabecalho(void) {
    printf("=================================\n");
    printf("LAVA - RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
    printf("=================================\n");
}

void preencherFrota(Veiculo *frota, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%7s", (frota + i)->placa);

        printf("Valor do servico ( R$ ) : ");
        scanf("%f", &(frota + i)->valor);
    }
}

void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return;
    }

    printf("%d) Placa : %s | Valor : R$ %.2f\n",
           indice + 1,
           (frota + indice)->placa,
           (frota + indice)->valor);

    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}

float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    /* Caso base: chegou ao final da frota. */
    if (indice == quantidade) {
        return 0.0f;
    }

    /* Passo recursivo: soma o valor atual ao restante da frota. */
    return (frota + indice)->valor
           + calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}

int buscarVeiculoRecursivo(Veiculo *frota, int indice,
                           int quantidade, char placa[8]) {
    /* Caso base 1: percorreu toda a frota sem encontrar a placa. */
    if (indice == quantidade) {
        return -1;
    }

    /* Caso base 2: a placa atual foi encontrada. */
    if (strcmp((frota + indice)->placa, placa) == 0) {
        return indice;
    }

    /* Passo recursivo: verifica o próximo veículo. */
    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}

int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) {
        return 0;
    }

    if ((frota + indice)->valor >= VALOR_PREMIUM) {
        return 1 + contarPremiumRecursivo(frota, indice + 1, quantidade);
    }

    return contarPremiumRecursivo(frota, indice + 1, quantidade);
}

int main(void) {
    int quantidade;
    int posicao;
    int premium;
    float total;
    char placaBusca[8];

    exibirCabecalho();

    printf("Quantos veiculos serao atendidos hoje ? ");
    scanf("%d", &quantidade);

    Veiculo *frota = (Veiculo *)malloc(quantidade * sizeof(Veiculo));

    /* Verifica se a alocacao de memoria foi realizada. */
    if (frota == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    preencherFrota(frota, quantidade);

    printf("--- Veiculos atendidos hoje ---\n");
    exibirFrotaRecursivo(frota, 0, quantidade);

    printf("--- Busca recursiva por placa ---\n");

    printf("Placa a ser pesquisada : ");
    scanf("%7s", placaBusca);

    posicao = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);

    if (posicao == -1) {
        printf("Veiculo nao encontrado na frota.\n");
    } else {
        printf("Veiculo encontrado na posicao %d! Placa : %s | Valor : R$ %.2f\n",
               posicao + 1,
               (frota + posicao)->placa,
               (frota + posicao)->valor);
    }

    printf("--- Resumo do dia ---\n");

    printf("Total de veiculos atendidos : %d\n", quantidade);

    premium = contarPremiumRecursivo(frota, 0, quantidade);
    printf("Servicos premium ( >= R$ 100.00) : %d\n", premium);

    total = calcularValorTotalRecursivo(frota, 0, quantidade);
    printf("Valor total arrecadado : R$ %.2f\n", total);

    free(frota);
    frota = NULL;

    printf("Memoria da frota liberada com sucesso . Sistema encerrado .\n");

    return 0;
}
