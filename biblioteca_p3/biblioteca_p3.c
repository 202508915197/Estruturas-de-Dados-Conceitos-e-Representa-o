/*
continuidade ao sistema da biblioteca, mas agora no nível mestre,
aplicando modularização do código com funções especializadas.
Serão utilizados ponteiros, alocação dinâmica com malloc,
calloc e free, além da passagem por valor para exibição
de dados e por referência para atualizar empréstimos,
consolidando boas práticas de estruturação e manipulação
de memória em C.
*/

// bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 // definimos uma capacidade máxima para os empréstimos
#define TAM_STRING 100

// estruturas
struct livro
{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para emprestado
};

// nova strutura para representar um empréstimo
struct emprestimo
{
    int indicelivro;              // índice do livro emprestado
    char nomeUsuario[TAM_STRING]; // nome do usuário que fez o empréstimo
};

// funcao para limpar o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// funcao para limpar a tela
void limparTela()
{
    system("clear");
}

// funcao para imprimir separador visual
void imprimirSeparador()
{
    printf("\n------------------------------------------------\n\n");
}

// protótipos das funções 


// funcao principal


    // alocacao dinamica de memoria
    struct livro *biblioteca;
    struct emprestimo *emprestimos;

    biblioteca = (struct livro *)calloc(MAX_LIVROS, sizeof(struct livro));
    emprestimos = (struct emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo));

    // verificacao: e crucial verificar se a alocacao de memoria deu certo
    if (biblioteca == NULL || emprestimos == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1; // sai do programa com código de erro
    }
