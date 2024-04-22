#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações de cada aluno
struct Aluno {
    char nome[100];
    char telefone[20];
    char curso[100];
    float notas[2];  // Alterado para float
    float media;
    char situacao[20];
};

// Função para exibir os resultados
void exibirResultados(struct Aluno aluno) {
    FILE *saida = fopen("situacaoFinal.csv", "a");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo situacaoFinal.csv.\n");
        return;
    }

    fprintf(saida, "%s,%s,%s,%.1f,%s\n",
            aluno.nome, aluno.telefone, aluno.curso,
            aluno.media, aluno.situacao);

    fclose(saida);
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "a");  // Abre o arquivo em modo de adição
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo DadosEntrada.csv.\n");
        return 1;
    }

    // Solicita os detalhes dos alunos
    char linha[256];
    printf("Digite os dados dos alunos (Nome,Telefone,Curso,Nota1,Nota2):\n");
    while (fgets(linha, sizeof(linha), stdin)) {
        struct Aluno aluno;

        // Extrai os dados da linha
        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f",
               aluno.nome, aluno.telefone, aluno.curso,
               &aluno.notas[0], &aluno.notas[1]);

        // Calcula a média e determina a situação
        aluno.media = (aluno.notas[0] + aluno.notas[1]) / 2;

        if (aluno.media >= 7.0) {
            strcpy(aluno.situacao, "APROVADO");
        } else {
            strcpy(aluno.situacao, "REPROVADO");
        }

        // Escreve os detalhes do aluno no arquivo
        fprintf(entrada, "%s,%s,%s,%.1f,%.1f\n",
                aluno.nome, aluno.telefone, aluno.curso,
                aluno.notas[0], aluno.notas[1]);

        // Chama a função para exibir os resultados
        exibirResultados(aluno);

        printf("Aluno %s adicionado.\n", aluno.nome);
    }

    fclose(entrada);
    printf("Informações dos alunos adicionadas ao arquivo DadosEntrada.csv.\n");

    return 0;
}
