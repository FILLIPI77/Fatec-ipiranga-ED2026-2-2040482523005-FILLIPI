#include <stdio.h>
#define TAMANHO_TURMA 5 // define quantidade de alunos na turma, sendo possivel facilitar a alteração depois

    void exibirCabecalho(void) {
    printf("E.E.F.I ");
    printf("Sistema de Lançamento de Notas ");
    }   
        float calcularMedia(float vetor[] , int tamanho) {
        float soma = 0;

        //for pois ja sabemos quantiade de alunos e funcao que percorre o as notas para calcular a soma
        for(int i = 0; i < tamanho; i++){   
        soma = soma + vetor[i];
    }
    
     return soma / tamanho;
}
    void simularAjuste(float notaORIGINAL, float bonus) {
    // altera apenas a copia da nota original, utiliza a variavel guardada, nao original
    // nao altera a nota original, apenas simula como seria o ajuste
    notaORIGINAL = notaORIGINAL + bonus;
    printf("Nota ajustada: %.2f\n", notaORIGINAL);
}

void aplicarBonus(float *nota, float bonus) {
    //altera a nota original utilizando ponteiro
    *nota = *nota + bonus;
}

int main(void)
{
    exibirCabecalho();
    
    float notas[TAMANHO_TURMA];
    // pega. anota de cada aluno sem \n para digitar ao lado do texto
        for(int i =0; i < TAMANHO_TURMA; i++){
            printf("Digite a nota %d: " , i + 1);
            scanf("%f", &notas[i]);
        }

    float mediaAntes = calcularMedia (notas , TAMANHO_TURMA);
    printf("Media antes do ajuste: %.2f", mediaAntes);

    float bonus;
    printf("Digite o Valor do bonus:");
    scanf("%f", &bonus);

    simularAjuste(notas[0], bonus);
    //somente simula ajuste nas notas
    printf("Nota ajustada: %.2f", notas[0]);

    // aplica bonus para os alunos 
    for(int i = 0; i < TAMANHO_TURMA; i++){
        aplicarBonus(&notas[i], bonus);
    }
    // exibe as notas ajustadas 
    for( int i = 0; i < TAMANHO_TURMA; i++){
        printf("Nota ajustada do aluno %d: %.2f", i + 1, notas[i]);    
    }

    float mediaDepois = calcularMedia(notas, TAMANHO_TURMA);
    printf("Media depois do ajusto: %.2f", mediaDepois); 
    

    return 0;
}