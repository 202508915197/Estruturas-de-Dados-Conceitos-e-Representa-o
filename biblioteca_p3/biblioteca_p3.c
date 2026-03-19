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
#include <time.h>

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

// nova estrutura para representar um empréstimo
struct emprestimo
{
    int indicelivro;              // índice do livro emprestado
    char nomeUsuario[TAM_STRING]; // nome do usuário que fez o empréstimo
    struct livro *livro;          // ponteiro para o livro emprestado
    time_t dataEmprestimo;        // data do empréstimo
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
    printf("\n------------------------------------------------\n");
}

// exibir menu
void exibirMenu()
{
    imprimirSeparador();
    printf("Bem-vindo à Biblioteca!");
    imprimirSeparador();
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Realizar Empréstimo\n");
    printf("4. Listar Empréstimos\n");
    printf("5. Sair");
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
    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';

    printf("Digite a editora do livro: ");
    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

    printf("Digite a edição do livro: ");
    scanf("%d", &biblioteca[totalLivros].edicao);
    limparBuffer();

    biblioteca[totalLivros].disponivel = 1;
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
int realizarEmprestimo(struct livro *biblioteca, struct emprestimo *emprestimos, int totalLivros, int *totalEmprestimos)
{
    if (totalLivros == 0)
    {
        printf("Nenhum livro cadastrado para empréstimo.\n");
        return 0;
    }

    printf("Livros disponíveis:\n\n");
    int disponiveis = 0;
    for (int i = 0; i < totalLivros; i++)
    {
        if (biblioteca[i].disponivel)
        {
            disponiveis = 1;
            printf("[%d] %s - %s\n", i + 1, biblioteca[i].nome, biblioteca[i].autor);
        }
    }

    if (!disponiveis)
    {
        printf("Nenhum livro disponível para empréstimo no momento.\n");
        return 0;
    }

    printf("\nDigite o número do livro que deseja emprestar: ");
    int indiceLivro;
    if (scanf("%d", &indiceLivro) != 1)
    {
        limparBuffer();
        printf("Entrada inválida.\n");
        return 0;
    }
    limparBuffer();

    if (indiceLivro < 1 || indiceLivro > totalLivros)
    {
        printf("\n✗ Índice de livro inválido.\n");
        imprimirSeparador();
        return 0;
    }

    if (!biblioteca[indiceLivro - 1].disponivel)
    {
        printf("\n✗ Livro indisponível para empréstimo.\n");
        imprimirSeparador();
        return 0;
    }

    printf("Digite o nome do usuário: ");
    fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
    emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = '\0';

    emprestimos[*totalEmprestimos].indicelivro = indiceLivro - 1;
    emprestimos[*totalEmprestimos].livro = &biblioteca[indiceLivro - 1];
    emprestimos[*totalEmprestimos].dataEmprestimo = time(NULL);

    biblioteca[indiceLivro - 1].disponivel = 0;
    (*totalEmprestimos)++;

    printf("\n✓ Empréstimo realizado com sucesso!\n");
    imprimirSeparador();
    printf("Pressione ENTER para continuar...\n");
    getchar();

    return 1;
}

// listar empréstimos
void listarEmprestimos(const struct emprestimo *emprestimos, int totalEmprestimos)
{
    if (totalEmprestimos == 0)
    {
        printf("Nenhum empréstimo realizado.\n");
        return;
    }

    printf("Lista de Empréstimos:\n");
    for (int i = 0; i < totalEmprestimos; i++)
    {
        printf("%d. %s - %s (%s, Edição %d) - Emprestado para: %s\n", i + 1,
               emprestimos[i].livro->nome,
               emprestimos[i].livro->autor,
               emprestimos[i].livro->editora,
               emprestimos[i].livro->edicao,
               emprestimos[i].nomeUsuario);
    }
}

// liberar memória
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos)
{
    free(biblioteca);
    free(emprestimos);
    printf("Memória liberada com sucesso.\n");
}

// protótipos de funções
void exibirMenu();
void cadastrarLivro(struct livro *biblioteca, int totalLivros);
void listarLivros(const struct livro *biblioteca, int totalLivros);
int realizarEmprestimo(struct livro *biblioteca, struct emprestimo *emprestimos, int totalLivros, int *totalEmprestimos);
void listarEmprestimos(const struct emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct livro *biblioteca, struct emprestimo *emprestimos);

int main()
{
    struct livro *biblioteca = malloc(MAX_LIVROS * sizeof(struct livro));
    struct emprestimo *emprestimos = malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo));

    if (!biblioteca || !emprestimos)
    {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do
    {
        exibirMenu();
        if (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            printf("Opção inválida. Tente novamente.\n");
            continue;
        }
        limparBuffer();

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
            realizarEmprestimo(biblioteca, emprestimos, totalLivros, &totalEmprestimos);
            break;
        case 4:
            listarEmprestimos(emprestimos, totalEmprestimos);
            break;
        case 5:
            printf("Saindo do sistema. Obrigado por usar a biblioteca!\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcao != 5);

    liberarMemoria(biblioteca, emprestimos);
    return 0;
}
