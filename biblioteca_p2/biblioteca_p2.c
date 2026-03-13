/*
Confira este vídeo, no qual você dará continuidade 
ao desenvolvimento do sistema da biblioteca, 
adicionando a funcionalidade de empréstimo de 
livros. Serão utilizados ponteiros e alocação 
dinâmica de memória com malloc e calloc, além 
de free para liberar recursos. O sistema 
permitirá o cadastro de livros e a realização 
e consulta de empréstimos feitos por usuários.
*/

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 //definimos uma capacidade máxima para os empréstimos
#define TAM_STRING 100

//estruturas
struct livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para emprestado
};

// nova strutura para representar um empréstimo
struct emprestimo {
    int indicelivro; // índice do livro emprestado
    char nomeUsuario[TAM_STRING]; // nome do usuário que fez o empréstimo
};

//funcao para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//funcao para limpar a tela
void limparTela() {
    system("clear");
}

//funcao para imprimir separador visual
void imprimirSeparador() {
    printf("\n================================================\n\n");
}

//funcao principal

int main() {
    //alocacao dinamica de memoria
    struct livro *biblioteca;
    struct emprestimo *emprestimos;

    biblioteca = (struct livro*) calloc(MAX_LIVROS, sizeof(struct livro));
    emprestimos = (struct emprestimo*) malloc(MAX_EMPRESTIMOS * sizeof(struct emprestimo));

    //verificacao: e crucial verificar se a alocacao de memoria deu certo
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // sai do programa com código de erro
    }

    int totalLivros = 0; // contador para o número de livros cadastrados
    int totalEmprestimos = 0; // contador para o número de empréstimos realizados
    int opcao;

    do {
        limparTela();
        printf("================================================\n");
        printf("            SISTEMA DE BIBLIOTECA\n");
        printf("================================================\n\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros cadastrados\n");
        printf("3. Realizar empréstimo\n");
        printf("4. Listar empréstimos realizados\n");
        printf("5. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o buffer após ler a opção

        switch (opcao) {
            //cadastro de livro
            case 1:
                imprimirSeparador();
                printf("         CADASTRO DE NOVO LIVRO\n");
                imprimirSeparador();
                if (totalLivros < MAX_LIVROS) {
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
                    limparBuffer(); // limpa o buffer após ler a edição

                    biblioteca[totalLivros].disponivel = 1; // marca o livro como disponível
                    totalLivros++;
                    printf("\n✓ Livro cadastrado com sucesso!\n");
                    imprimirSeparador();
                    printf("Pressione ENTER para continuar...\n");
                    getchar();
                } else {
                    printf("Capacidade máxima de livros atingida.\n");
                    imprimirSeparador();
                    printf("Pressione ENTER para continuar...\n");
                    getchar();
                }
                break;

            //listagem de livros
            case 2:
                imprimirSeparador();
                printf("       LIVROS DISPONÍVEIS PARA EMPRÉSTIMO\n");
                imprimirSeparador();
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado.\n");
                    imprimirSeparador();
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("[%d] %s\n", i + 1, biblioteca[i].nome);
                            printf("    Autor: %s\n", biblioteca[i].autor);
                            printf("    Editora: %s | Edição: %d\n", biblioteca[i].editora, biblioteca[i].edicao);
                            printf("    Status: Disponível\n\n");
                        }
                    }
                    imprimirSeparador();
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();

            // realização de empréstimo
            case 3:
                imprimirSeparador();
                printf("          REALIZAR EMPRÉSTIMO DE LIVRO\n");
                imprimirSeparador();
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado para empréstimo.\n");
                    imprimirSeparador();
                    printf("Pressione ENTER para continuar...\n");
                    getchar();
                } else if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Capacidade máxima de empréstimos atingida.\n");
                    imprimirSeparador();
                    printf("Pressione ENTER para continuar...\n");
                    getchar();
                } else {
                    printf("Livros disponíveis:\n\n");
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("[%d] %s - %s\n", i + 1, biblioteca[i].nome, biblioteca[i].autor);
                        }
                    }
                    printf("\n");
                    int indiceLivro;
                    printf("Digite o número do livro que deseja emprestar: ");
                    scanf("%d", &indiceLivro);
                    limparBuffer(); // limpa o buffer após ler o índice
                    if (indiceLivro < 1 || indiceLivro > totalLivros) {
                        printf("\n✗ Índice de livro inválido.\n");
                        imprimirSeparador();
                    } else if (!biblioteca[indiceLivro - 1].disponivel) {
                        printf("\n✗ Livro indisponível para empréstimo.\n");
                        imprimirSeparador();
                    } else {
                        printf("Digite o nome do usuário: ");
                        fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                        emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0'; // remove o newline

                        emprestimos[totalEmprestimos].indicelivro = indiceLivro - 1; // armazena o índice do livro emprestado
                        biblioteca[indiceLivro - 1].disponivel = 0; // marca o livro como emprestado
                        totalEmprestimos++;
                        printf("\n✓ Empréstimo realizado com sucesso!\n");
                        imprimirSeparador();
                    }
                    printf("Pressione ENTER para continuar...\n");
                    getchar();
                }

            //listagem de empréstimos
            case 4:
                imprimirSeparador();
                printf("        EMPRÉSTIMOS REALIZADOS\n");
                imprimirSeparador();
                if (totalEmprestimos == 0) {
                    printf("Nenhum empréstimo realizado.\n");
                    imprimirSeparador();
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indicelivro;
                        printf("[%d] Livro: %s\n", i + 1, biblioteca[indiceLivro].nome);
                        printf("    Emprestado para: %s\n\n", emprestimos[i].nomeUsuario);
                    }
                    imprimirSeparador();
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();

            // opção para sair do programa
            case 5:
                imprimirSeparador();
                printf("        Obrigado por usar o Sistema de Biblioteca!\n");
                imprimirSeparador();
                break;

            default:
                imprimirSeparador();
                printf("✗ Opção inválida. Escolha entre 1 e 5.\n");
                imprimirSeparador();
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
        }

    } while (opcao != 5);

    //liberacao de memoria
    free(biblioteca);
    free(emprestimos);

    return 0;
}

    
