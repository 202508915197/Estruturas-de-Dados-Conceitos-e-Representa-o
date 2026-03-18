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

// exibir menu
void exibirMenu()
{
   	imprimirSeparador();
    printf("Menu:\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Realizar Empréstimo\n");
    printf("4. Listar Empréstimos\n");
    printf("5. Sair\n");
    imprimirSeparador();
    printf("Escolha uma opção: ");
    imprimirSeparador();
}

// cadastrar livro
void cadastrarLivro(struct livro *biblioteca, int totalLivros)
{
    if (totalLivros >= MAX_LIVROS)
    {
        printf("Capacidade máxima de livros atingida. Não é possível cadastrar mais livros.\n");
        return;
    }

    printf("Digite o nome do livro: ");
    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0'; // remove o newline

    printf("Digite o autor do livro: ");
    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0'; // remove o newline

    printf("Digite a editora do livro: ");
    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0'; // remove o newline

    printf("Digite a edição do livro: ");
    scanf("%d", &biblioteca[totalLivros].edicao);
    limparBuffer(); // limpa o buffer após a leitura da edição

    biblioteca[totalLivros].disponivel = 1; // marca o livro como disponível
    printf("Livro cadastrado com sucesso!\n");
}

// listar livros
void listarLivros(const struct livro *biblioteca, int totalLivros)
{
    if (totalLivros == 0)
    {
        printf("Nenhum livro cadastrado na biblioteca.\n");
        return;
    }

    printf("Lista de Livros:\n");
    for (int i = 0; i < totalLivros; i++)
    {
        printf("%d. %s - %s (%s, Edição %d) - %s\n", i + 1, biblioteca[i].nome, biblioteca[i].autor, biblioteca[i].editora, biblioteca[i].edicao, biblioteca[i].disponivel ? "Disponível" : "Emprestado");
    }
}

// realizar empréstimo
void realizarEmprestimo(struct livro *biblioteca, struct emprestimo *emprestimos, int totalEmprestimos)
{
    if (totalEmprestimos >= MAX_EMPRESTIMOS)
    { 
        printf("Capacidade máxima de empréstimos atingida. Não é possível realizar mais empréstimos.\n");
        return;
    }
    int indiceLivro;
    printf("Digite o número do livro que deseja emprestar: ");
    scanf("%d", &indiceLivro);
    limparBuffer(); // limpa o buffer após a leitura do índice

    if (indiceLivro < 1 || indiceLivro > totalLivros)
    {
        printf("Índice inválido. Tente novamente.\n");
        return;
    }

    if (!biblioteca[indiceLivro - 1].disponivel)
    {
        printf("O livro selecionado não está disponível para empréstimo.\n");
        return;
    }

    biblioteca[indiceLivro - 1].disponivel = 0; // marca o livro como emprestado
    emprestimos[totalEmprestimos].livro = &biblioteca[indiceLivro - 1];
    emprestimos[totalEmprestimos].dataEmprestimo = time(NULL);
    totalEmprestimos++;
    printf("Empréstimo realizado com sucesso!\n");
}

// listar empréstimos
void listarEmprestimos(const struct livro *biblioteca, const struct emprestimo *emprestimos, int totalEmprestimos)
{
    if (totalEmprestimos == 0)
    {
        printf("Nenhum empréstimo realizado.\n");
        return;
    }
    printf("Lista de Empréstimos:\n");
    for (int i = 0; i < totalEmprestimos; i++)
    {
        printf("%d. %s - %s (%s, Edição %d) - Emprestado para: %s\n", i + 1, emprestimos[i].livro->nome, emprestimos[i].livro->autor, emprestimos[i].livro->editora, emprestimos[i].livro->edicao, emprestimos[i].nomeUsuario);
    }
}

// liberar memória
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos)
{
    free(biblioteca);
    free(emprestimos);
}

//protótipos de funções 
//Declarar as fuções aqui permite que "main" as chame antes de suas definições 
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct livro *biblioteca, int totalLivros);
void listarLivros(const struct livro *biblioteca, int totalLivros); //"const" indica que a função não modificara os dados da biblioteca
void realizarEmprestimo(struct livro *biblioteca, const struct emprestimo *emprestimos, int totalLivros );
void listarEmprestimos(const struct livro *biblioteca, const struct emprestimo *emprestimos, int totalLivros);
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos);

// função principal
//main mais limpa e organizada, delegando tarefas para funções especializadas, seguindo o princípio de responsabilidade única e facilitando a manutenção do código.
//delega as tarefas para funções especializadas, seguindo o princípio de responsabilidade única e facilitando a manutenção do código.

int main(){
    struct livro *biblioteca = (struct livro *)malloc(MAX_LIVROS * sizeof(struct livro)); // alocação dinâmica para a biblioteca
    struct emprestimo *emprestimos = (struct emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo)); // alocação dinâmica para os empréstimos

    if (!biblioteca || !emprestimos)
    {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }
    int totalLivros = 0; // contador de livros cadastrados
    int totalEmprestimos = 0; // contador de empréstimos realizados
    int opcao;
   
    do
    {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer(); // limpa o buffer após a leitura da opção

        switch (opcao)
        {
        case 1:
            cadastrarLivro(biblioteca, totalLivros);
            totalLivros++;
            break;
        case 2:
            listarLivros(biblioteca, totalLivros);
            break;
        case 3:
            realizarEmprestimo(biblioteca, emprestimos, totalEmprestimos);
            totalEmprestimos++;
            break;
        case 4:
            listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
            break;
        case 5:
            printf("Saindo do sistema. Obrigado por usar a biblioteca!\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    }
    

    // código principal
    return 0;
}

