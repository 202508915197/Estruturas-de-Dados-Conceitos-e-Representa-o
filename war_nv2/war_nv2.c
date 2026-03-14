/*
Requisitos funcionais


Veja as funcionalidades essenciais para a implementação de uma simulação de batalha entre territórios.

 

Alocação dinâmica de territórios: utilizar calloc ou malloc para alocar memória para um vetor de struct Territorio com tamanho informado pelo usuário.
 
Simulação de ataques: criar uma função void atacar(Territorio* atacante, Territorio* defensor) que simula um ataque, utilizando números aleatórios como se fossem dados de batalha.
 
Atualização de dados: o território defensor deve mudar de dono (cor do exército) se o atacante vencer, e suas tropas devem ser atualizadas.
 
Exibição pós-ataque: o sistema deve exibir os dados atualizados dos territórios após cada ataque.


Requisitos não funcionais


A implementação deve seguir boas práticas de organização, uso eficiente da memória e interação clara com o usuário. Acompanhe!

 

Modularização: o código deve estar organizado com funções distintas para cadastro, exibição, ataque e liberação de memória.
 
Uso de ponteiros: todos os acessos e modificações aos dados dos territórios devem ser feitos por ponteiros.
 
Gerenciamento de memória: toda memória alocada dinamicamente deve ser liberada ao final do programa utilizando free.
 
Interface amigável: o terminal deve orientar o jogador sobre quais territórios podem ser usados para atacar e defender, com mensagens claras.

Instruções detalhadas


Para que o programa funcione da maneira esperada, alguns elementos e etapas de implementação devem ser seguidos conforme descrito a seguir.

 

Bibliotecas necessárias: inclua stdio.h, stdlib.h, string.h e time.h.
 
Struct atualizada: utilize a struct Territorio com os campos char nome[30], char cor[10], int tropas.
 
Alocação de memória: peça ao usuário o número total de territórios e use calloc ou malloc para alocar esse vetor de forma dinâmica.
 
Função de ataque: implemente void atacar(Territorio* atacante, Territorio* defensor) que utilize rand() para simular um dado de ataque (1 a 6) para cada lado.
 
Atualização dos campos: transfira a cor e metade das tropas para o território defensor se o atacante vencer. Se perder, o atacante perde uma tropa.
 
Liberação de memória: crie uma função void liberarMemoria(Territorio* mapa) para liberar o espaço alocado.

Requisitos técnicos adicionais


Alguns cuidados extras proporcionam o bom funcionamento e a legibilidade do programa. São eles:

 

Utilizar srand(time(NULL)) para garantir aleatoriedade nos dados de ataque.
 
Validar as escolhas de ataque para que o jogador não ataque um território da própria cor.
 
Usar free corretamente ao final do programa.
 
Comentar o código explicando cada função e trecho importante.
*/

//Biblioteca de simulação de batalha entre territórios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//funcao para imprimir separador visual
void imprimirSeparador() {
    printf("\n================================================\n\n");
}

//funcao para limpar a tela
void limparTela() {
    system("clear");
}

//funcao para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//Função para liberar memória alocada
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
};

//funcao para salvar partida em txt
void salvarPartida(struct Territorio* mapa, int totalTerritorios) {
    FILE* arquivo = fopen("partida.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar a partida.\n");
        return;
    }

    fprintf(arquivo, "Partida Salva\n");
    for (int i = 0; i < totalTerritorios; i++) {
        fprintf(arquivo, "%s - Cor: %s, Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    fclose(arquivo);
    printf("Partida salva com sucesso!\n");
}

//Função para simular um ataque entre territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1; // Simula um dado de 1 a 6 para o atacante
    int dadoDefensor = rand() % 6 + 1; // Simula um dado de 1 a 6 para o defensor

    printf("%s ataca %s! (Dado: %d vs %s: %d)\n", atacante->nome, defensor->nome, dadoAtacante, defensor->nome, dadoDefensor);
    if (dadoAtacante > dadoDefensor) {
        printf("O atacante vence! %s conquista %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor); // O defensor muda de cor para a do atacante
        defensor->tropas = atacante->tropas / 2; // O defensor recebe metade das tropas do atacante
    } else {
        printf("O defensor vence! %s mantém o controle de %s!\n", defensor->nome, defensor->nome);
        atacante->tropas -= 1; // O atacante perde 1 tropa se perder o ataque
    }

    printf("Status pós-ataque:\n");
    printf("%s - Cor: %s, Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%s - Cor: %s, Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}

//Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    
    //alocacao dinamica de memoria
    int totalTerritorios = 0; // contador para o número de territórios cadastrados
    int opcao; // variável para armazenar a opção do menu
    int salvarPartidaFlag = 0; // variável para indicar se a partida foi salva
    int indiceAtacante = 0;
    int indiceDefensor = 0;
    
    // Defina o valor máximo de territórios
    #define MAX_TERRITORIOS 100
    // Defina a struct Territorio se não estiver definida
    typedef struct Territorio {
        char nome[30];
        char cor[10];
        int tropas;
    } Territorio;
    Territorio *mapa = malloc(MAX_TERRITORIOS * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // Encerra o programa com código de erro
    }

    do {
        limparTela();
        printf("==================================================\n");
        printf("                       WAR                        \n");
        printf("==================================================\n");
        printf("1. Cadastrar Territorio                           \n");
        printf("2. Listar Territorios cadastrados                 \n");
        printf("3. Escolher Territorio para a guerra              \n");
        printf("4. Realizar ataque                                \n");
        printf("5. Salvar partida                                 \n");
        printf("6. Sair                                           \n");
         printf("=================================================\n");
        printf("Escolha uma opção:                                \n");
         printf("=================================================\n");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o buffer após ler a opção

        switch (opcao) {
            //cadastro de território
            case 1:
                imprimirSeparador();
                printf("         CADASTRO DE NOVO TERRITÓRIO\n");
                imprimirSeparador();
                if (totalTerritorios < MAX_TERRITORIOS) {
                    printf("Digite o nome do território: ");
                    fgets(mapa[totalTerritorios].nome, 30, stdin);
                    mapa[totalTerritorios].nome[strcspn(mapa[totalTerritorios].nome, "\n")] = '\0'; // Remove o caractere de nova linha
                    printf("Digite a cor do exército: ");
                    fgets(mapa[totalTerritorios].cor, 10, stdin);
                    mapa[totalTerritorios].cor[strcspn(mapa[totalTerritorios].cor, "\n")] = '\0'; // Remove o caractere de nova linha
                    printf("Digite o número de tropas: ");
                    scanf("%d", &mapa[totalTerritorios].tropas);
                    limparBuffer(); // Limpa o buffer após ler o número de tropas
                    totalTerritorios++;
                    printf("\n✓ Território cadastrado com sucesso!\n");
                } else {
                    printf("\n✗ Limite de territórios atingido.\n");
                }
                printf("Pressione ENTER para continuar...\n");  
                getchar();
                break;
            //listagem de territórios
            case 2:
                imprimirSeparador();
                printf("         LISTA DE TERRITÓRIOS CADASTRADOS\n");
                imprimirSeparador();
                if (totalTerritorios == 0) {
                    printf("Nenhum território cadastrado.\n");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("[%d] Nome: %s, Cor: %s, Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                    }
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
            //escolha de territórios para guerra
            case 3:
                imprimirSeparador();
                printf("         ESCOLHA DE TERRITÓRIOS PARA A GUERRA\n");
                imprimirSeparador();
                if (totalTerritorios < 2) {
                    printf("É necessário cadastrar pelo menos 2 territórios para realizar um ataque.\n");
                } else {
                    printf("Territórios disponíveis:\n");
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("[%d] Nome: %s, Cor: %s, Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                    }
                    printf("\nDigite o número do território atacante: ");
                    scanf("%d", &indiceAtacante);
                    limparBuffer(); // Limpa o buffer após ler a opção
                    printf("Digite o número do território defensor: ");
                    scanf("%d", &indiceDefensor);
                    limparBuffer(); // Limpa o buffer após ler a opção

                    if (indiceAtacante < 1 || indiceAtacante > totalTerritorios || indiceDefensor < 1 || indiceDefensor > totalTerritorios) {
                        printf("\n✗ Índice inválido. Tente novamente.\n");
                    } else if (strcmp(mapa[indiceAtacante - 1].cor, mapa[indiceDefensor - 1].cor) == 0) {
                        printf("\n✗ Não é permitido atacar um território da mesma cor. Tente novamente.\n");
                    } else {
                        atacar(&mapa[indiceAtacante - 1], &mapa[indiceDefensor - 1]);
                    }
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
            //realização de ataque
            case 4:
                imprimirSeparador();
                printf("         REALIZAÇÃO DE ATAQUE ENTRE TERRITÓRIOS\n");
                imprimirSeparador();
                if (totalTerritorios < 2) {
                    printf("É necessário cadastrar pelo menos 2 territórios para realizar um ataque.\n");
                } else {
                    printf("Territórios disponíveis:\n");
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("[%d] Nome: %s, Cor: %s, Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                    }
                    printf("\nDigite o número do território atacante: ");
                    scanf("%d", &indiceAtacante);
                    limparBuffer(); // Limpa o buffer após ler a opção
                    printf("Digite o número do território defensor: ");
                    scanf("%d", &indiceDefensor);
                    limparBuffer(); // Limpa o buffer após ler a opção
                    if (indiceAtacante < 1 || indiceAtacante > totalTerritorios || indiceDefensor < 1 || indiceDefensor > totalTerritorios) {
                        printf("\n✗ Índice inválido. Tente novamente.\n");
                    } else if (strcmp(mapa[indiceAtacante - 1].cor, mapa[indiceDefensor - 1].cor) == 0) {
                        printf("\n✗ Não é permitido atacar um território da mesma cor. Tente novamente.\n");
                    } else {
                        atacar(&mapa[indiceAtacante - 1], &mapa[indiceDefensor - 1]);
                    }
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
            //salvar partida
            case 5:
                imprimirSeparador();
                printf("         SALVAR PARTIDA EM ARQUIVO\n");
                imprimirSeparador();
                salvarPartida(mapa, totalTerritorios);
                salvarPartidaFlag = 1;
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
            //sair
            case 6:
                imprimirSeparador();
                printf("         SAINDO DO JOGO... OBRIGADO POR JOGAR\n");
                imprimirSeparador();
                if (!salvarPartidaFlag) {
                    printf("Deseja salvar a partida antes de sair? (1 - Sim, 2 - Não): ");
                    int salvarOpcao;
                    scanf("%d", &salvarOpcao);
                    limparBuffer(); // Limpa o buffer após ler a opção
                    if (salvarOpcao == 1) {
                        salvarPartida(mapa, totalTerritorios);
                    }
                }
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
        }
    } while (opcao != 6);

    //liberacao de memoria
    free(mapa);
    return 0;
}
