#include <stdio.h>

//Adicionando a biblioteca stdio.h para usar as funções de entrada e saída
#include <string.h>

// Definindo a estrutura Pessoa

typedef struct {
    char nome[50];
    int idade[150];
    char alergias[20];
    char tipo_sanguineo[5];
} Pessoa;

int main() {
    // Criando uma variavel do tipo Pessoa
    Pessoa pessoa1;
    // Atribuindo valores aos campos da estrutura
        //fgets para ler nome com espaços
        //sizeof para garantir que não ultrapasse o tamanho do array
        //stdin para ler do teclado
    printf("Digite o nome da pessoa: ");
    scanf("nome: %s", pessoa1.nome);
    fgets(pessoa1.nome, sizeof(pessoa1.nome), stdin);
    printf("Digite a idade da pessoa: ");
    scanf("%d", &pessoa1.idade);
    printf("Digite as alergias da pessoa: ");
    scanf("alergias: %s", pessoa1.alergias);
    printf("Digite o tipo sanguineo da pessoa: ");
    scanf("tipo sanguineo: %s", pessoa1.tipo_sanguineo);
    // Imprimindo os valores dos campos da estrutura
    printf("\nInformações da Pessoa1:\n");
    
}