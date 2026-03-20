/*
Requisitos funcionais


A seguir, são apresentadas as etapas para implementar o sistema de missões dos jogadores, desde a criação até a verificação de objetivos.

 

Criação do vetor de missões: declarar um vetor de strings contendo ao menos cinco descrições diferentes de missões estratégicas (ex: Conquistar 3 territórios seguidos, Eliminar todas as tropas da cor vermelha etc.).
  
Sorteio da missão: implementar a função void atribuirMissao(char* destino, char* missoes[], int totalMissoes) que sorteia uma missão e copia para a variável de missão do jogador usando strcpy.
   
Armazenamento e acesso: a missão de cada jogador deve ser armazenada dinamicamente utilizando malloc.
    
Verificação da missão: implementar a função int verificarMissao(char* missao, Territorio* mapa, int tamanho), que avalia se a missão do jogador foi cumprida (crie uma lógica simples inicial para verificação).
     
Exibição condicional: o sistema deve verificar, ao final de cada turno, se algum jogador cumpriu sua missão e declarar o vencedor.

Requisitos não funcionais


Para garantir organização e clareza na execução das missões, algumas práticas e estruturas devem ser seguidas durante a implementação. Vamos lá!

      

Modularização: o código deve estar dividido em funções específicas, como atribuirMissao, verificarMissao, exibirMissao, atacar, exibirMapa, liberarMemoria, e a main.
       
Uso de ponteiros: as missões dos jogadores devem ser manipuladas por meio de ponteiros.
        
Passagem por valor e referência: a missão deve ser passada por valor para exibição e por referência para atribuição e verificação.
         
Interface intuitiva: o sistema deve exibir a missão ao jogador apenas uma vez (no início) e verificar silenciosamente se ela foi cumprida ao longo da execução.

Instruções detalhadas


Os elementos a seguir ajudam a estruturar corretamente o funcionamento do jogo e o gerenciamento da memória. Veja!

          

Bibliotecas necessárias: inclua stdio.h, stdlib.h, string.h e time.h.
           
Estrutura dos territórios: utilize a struct Territorio com os campos char nome[30], char cor[10], int tropas.
            
Alocação de memória: use calloc ou malloc para alocar os vetores de territórios e armazenar a missão de cada jogador.
             
Função de ataque: implemente void atacar(Territorio* atacante, Territorio* defensor) usando rand() para simular uma rolagem de dados (valores entre 1 e 6).
              
Atualização de campos: transfira a cor e metade das tropas para o território defensor se o atacante vencer. Caso contrário, o atacante perde uma tropa.
               
Função de liberação: implemente void liberarMemoria(...) para liberar toda a memória alocada dinamicamente (territórios e missões).

Requisitos técnicos adicionais

Para finalizar a implementação com boas práticas, siga os cuidados técnicos adiante:

Use srand(time(NULL)) para gerar números aleatórios.
                 
Valide os ataques para que o jogador só possa atacar territórios inimigos.
                  
Utilize free() ao final para evitar vazamentos de memória.
                   
Comente o código explicando o papel de cada função e lógica importante.
*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Constantes
#define MAX_MISSOES 5 // Total de 5 missões diferentes
#define MAX_TERRITORIOS 10 // Exemplo de mapa com 10 territórios
#define MAX_JOGADORES 4 // Total de 4 jogadores
#define MAX_PAIS 30 // Tamanho máximo para o nome do país
#define MAX_NOME 30 // Tamanho máximo para o nome do jogador
#define MAX_COR 10 // Tamanho máximo para a cor do território, países podem ter cores iguals, mas cada jogador tem uma cor diferente
#define MAX_TROPAS 100 // Número máximo de tropas em um território
#define MAX_TURNOS 10 // Número máximo de turnos para o jogo, para evitar loops infinitos
#define MAX_MAPA 10 // Exemplo de mapa com 10 territórios

//Vetor de missões
const char* missoes[MAX_MISSOES] = {
    "Conquistar 3 territórios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar 5 territórios diferentes",
    "Conquistar o território do adversário",
    "Manter pelo menos 10 tropas em um território"
};

//Vetor de cores. Total de 4 cores, cada jogador terá uma cor diferente
const char* cores[MAX_COR] = {
    "Vermelho",
    "Azul",
    "Verde",
    "Amarelo"
};

//Vetor de territórios. Exemplo de mapa com 10 territórios
const char* territorios[MAX_TERRITORIOS] = {
    "China",
    "Estados Unidos",
    "Rússia",
    "Brasil",
    "Índia",
    "Austrália",
    "Canadá",
    "França",
    "Alemanha",
    "Japão"
};

//Vetor de jogadores
const char* jogadores[MAX_JOGADORES] = {
    "Jogador 1",
    "Jogador 2",
    "Jogador 3",
    "Jogador 4"
};

//Vetor do menu do jogo
const char* menu[MAX_TURNOS] = {
    "1. Atacar",
    "2. Exibir Mapa",
    "3. Exibir Missão",
    "4. Salvar Partida",
    "5. Carregar Partida",
    "6. Sair do Jogo"
};

//Vetor de opções do menu
const char* opcoesMenu[MAX_TURNOS] = {
    "Atacar",
    "Exibir Mapa",
    "Exibir Missão",
    "Salvar Partida",
    "Carregar Partida",
    "Sair do Jogo"
};

//Estruturas

//Definição da struct Territorio
struct TERRITORIO {
    char pais[MAX_PAIS];
    char cor[MAX_COR];
    int mapa[MAX_MAPA];
    int tropas[MAX_TROPAS];
};

//Definição da struct Jogador
struct JOGADOR {
    char nome[MAX_NOME];
    char* missao; // Ponteiro para a missão do jogador
};

//Definição da struct missão
struct MISSAO {
    char descricao[MAX_NOME];
};


//Funções

//Função para imprimir separador visual
void imprimirSeparador() {
    printf("\n================================================\n\n");
} 

//Função para limpar a tela
void limparTela() {
    system("clear");
}

//Função para exibir o menu do jogo com as opções disponíveis para o jogador
void exibirMenu() {
    imprimirSeparador();
    printf(".          WAR       \n");  
	imprimirSeparador();
    printf ("1. Atacar\n");
    printf ("2. Exibir Mapa\n");
    printf ("3. Exibir Missão\n");
    printf ("4. Salvar Partida\n");
    printf ("5. Carregar Partida\n");
    printf ("6. Sair do Jogo\n");
    imprimirSeparador();
    printf("Digite o número da opção desejada: ");
    imprimirSeparador();
}

  
//Função para exibir o mapa do jogo
void exibirMapa(struct TERRITORIO* territorios, int totalTerritorios) {
    printf("Mapa do Jogo:\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Território: %s | Cor: %s | Tropas: %d\n", territorios[i].pais, territorios[i].cor, territorios[i].tropas);
    }
}

//Função para exibir a missão do jogador
void exibirMissao(struct JOGADOR* jogador) {
    printf("Missão de %s: %s\n", jogador->nome, jogador->missao);
}

//Função para atribuir uma missão ao jogador
void atribuirMissao(struct JOGADOR* jogador, const char* missao) {
    jogador->missao = malloc(strlen(missao) + 1);
    strcpy(jogador->missao, missao);
}

//Função para verificar se a missão do jogador foi cumprida (lógica simples para exemplo)
int verificarMissao(struct JOGADOR* jogador, struct TERRITORIO* territorios, int totalTerritorios) {
    // Lógica simples: verificar se o jogador controla pelo menos 3 territórios seguidos
    int contagem = 0;
    for (int i = 0; i < totalTerritorios; i++) {
        if (strcmp(territorios[i].cor, jogador->nome) == 0) {
            contagem++;
            if (contagem >= 3) {
                return 1; // Missão cumprida
            }
        } else {
            contagem = 0; // Resetar contagem se encontrar um território de outra cor
        }
    }
    return 0; // Missão não cumprida
}

//Função para simular um ataque entre territórios
void atacar(struct TERRITORIO* atacante, struct TERRITORIO* defensor) {
    int dadoAtacante = rand() % 6 + 1; // Valor entre 1 e 6
    int dadoDefensor = rand() % 6 + 1; // Valor entre 1 e 6
    printf("%s ataca %s! (Dado Atacante: %d, Dado Defensor: %d)\n", atacante->pais, defensor->pais, dadoAtacante, dadoDefensor);
    if (dadoAtacante > dadoDefensor) {
        printf("Atacante vence! %s conquista %s\n", atacante->pais, defensor->pais);
        strcpy(defensor->cor, atacante->cor); // Transferir cor
        defensor->tropas = atacante->tropas / 2; // Transferir metade das tropas
        atacante->tropas /= 2; // Atacante perde metade
    } else {
        printf("Defensor vence! %s mantém o controle de %s\n", defensor->pais, defensor->pais);
        atacante->tropas--; // Atacante perde uma tropa
    }
}

//Função para liberar a memória alocada dinamicamente
void liberarMemoria(struct JOGADOR* jogadores, int totalJogadores) {
    for (int i = 0; i < totalJogadores; i++) {
        free(jogadores[i].missao); // Liberar memória da missão de cada jogador
    }
}

//Função para alocar memória de forma dinâmica para os jogadores
struct JOGADOR* criarJogadores(int totalJogadores) {
    struct JOGADOR* jogadores = malloc(totalJogadores * sizeof(struct JOGADOR));
    if (jogadores == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os jogadores.\n");
        exit(1);
    }
    return jogadores;
}

//Função para alocar memória de forma dinâmica para os territórios
struct TERRITORIO* criarTerritorios(int totalTerritorios) {
    struct TERRITORIO* territorios = malloc(totalTerritorios * sizeof(struct TERRITORIO));
    if (territorios == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os territórios.\n");
        exit(1);
    }
    return territorios;
}

//Função para alocar de forma dinâmica para as missões
struct MISSAO* criarMissões(int totalMissões) {
    struct MISSAO* missões = malloc(totalMissões * sizeof(struct MISSAO));
    if (missões == NULL) {
        fprintf(stderr, "Erro ao alocar memória para as missões.\n");
        exit(1);
    }
    return missões;
}

//Função para atualização de campos após um ataque
void atualizarCampos(struct TERRITORIO* atacante, struct TERRITORIO* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        defensor->tropas += atacante->tropas / 2; // Transferir metade das tropas para o defensor
        atacante->tropas /= 2; // Atacante perde metade das tropas
    }
}

//Função para validar ataques, garantindo que o jogador só possa atacar territórios inimigos
int validarAtaque(struct JOGADOR* jogador, struct TERRITORIO* atacante, struct TERRITORIO* defensor) {
    if (strcmp(atacante->cor, jogador->nome) != 0) {
        printf("Você só pode atacar com territórios que controla!\n");
        return 0; // Ataque inválido
    }
    if (strcmp(defensor->cor, jogador->nome) == 0) {
        printf("Você não pode atacar seus próprios territórios!\n");
        return 0; // Ataque inválido
    }
    return 1; // Ataque válido
}

//Função para exibir o status do jogo ao final de cada turno
void exibirStatus(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    printf("Status do Jogo:\n");
    for (int i = 0; i < totalJogadores; i++) {
        printf("%s - Missão: %s\n", jogadores[i].nome, jogadores[i].missao);
    }
    exibirMapa(territorios, totalTerritorios);
}

//Função para transferir tropas entre territórios após um ataque bem-sucedido
void transferirTropas(struct TERRITORIO* atacante, struct TERRITORIO* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        defensor->tropas += atacante->tropas / 2; // Transferir metade das tropas para o defensor
        atacante->tropas /= 2; // Atacante perde metade das tropas
    }
}

//Função para passagem por valor para exibição da missão
void exibirMissaoValor(char* missao) {
    printf("Missão: %s\n", missao);
}

//Função para passagem por referência para atribuição da missão
void atribuirMissaoReferencia(char** missao, const char* novaMissao) {
    *missao = malloc(strlen(novaMissao) + 1);
    strcpy(*missao, novaMissao);
}

//Função para sorteio de missão para o jogador
void sortearMissao(struct JOGADOR* jogador) {
    int indice = rand() % MAX_MISSOES; // Sorteia um índice para a missão
    atribuirMissao(jogador, missoes[indice]); // Atribui a missão sorteada ao jogador
}

//Função para verificar se algum jogador cumpriu sua missão ao final de cada turno
void verificarVencedor(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    for (int i = 0; i < totalJogadores; i++) {
        if (verificarMissao(&jogadores[i], territorios, totalTerritorios)) {
            printf("Parabéns, %s! Você cumpriu sua missão e venceu o jogo!\n", jogadores[i].nome);
            exit(0); // Encerra o jogo ao encontrar um vencedor
        }
    }
}

//Função para salvar partidas, você pode implementar funções para salvar e carregar o estado do jogo usando arquivos. Isso pode incluir a escrita dos dados dos jogadores, territórios e missões em um arquivo de texto ou binário, e a leitura desses dados para restaurar o estado do jogo posteriormente.
void salvarPartida(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    //Salvar o estado do jogo em um arquivo de texto
    //nome do arquivo: partida_01.txt, partida_02.txt, etc. Você pode usar um contador para criar arquivos com nomes únicos a cada vez que salvar a partida.
    FILE* arquivo = fopen("partida_01.txt", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar a partida.\n");
        return;
    }
    //Escrever os dados dos jogadores no arquivo
    for (int i = 0; i < totalJogadores; i++) {
        fprintf(arquivo, "Jogador: %s\n", jogadores[i].nome);
        fprintf(arquivo, "Missão: %s\n", jogadores[i].missao);
    }
    //Escrever os dados dos territórios no arquivo
    for (int i = 0; i < totalTerritorios; i++) {
        fprintf(arquivo, "Território: %s | Cor: %s | Tropas: %d\n", territorios[i].pais, territorios[i].cor, territorios[i].tropas);
    }
    fclose(arquivo);
}

//Função para carregar partidas, você pode implementar uma função para ler o estado do jogo a partir de um arquivo e restaurar os dados dos jogadores, territórios e missões. Isso pode envolver a leitura dos dados do arquivo e a atribuição desses dados às estruturas correspondentes no programa.
void carregarPartida(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    //Carregar o estado do jogo a partir de um arquivo de texto
    FILE* arquivo = fopen("partida_01.txt", "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para carregar a partida.\n");
        return;
    }
    // Ler os dados dos jogadores do arquivo
    for (int i = 0; i < totalJogadores; i++) {
        fscanf(arquivo, "Jogador: %s\n", jogadores[i].nome);
        fscanf(arquivo, "Missão: %s\n", jogadores[i].missao);
    }
    // Ler os dados dos territórios do arquivo
    for (int i = 0; i < totalTerritorios; i++) {
        fscanf(arquivo, "Território: %s | Cor: %s | Tropas: %d\n", territorios[i].pais, territorios[i].cor, &territorios[i].tropas);
    }
    fclose(arquivo);
}

//Função para inicializar o jogo, configurando os jogadores, territórios e missões
void inicializarJogo(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    //Configurar os jogadores
    for (int i = 0; i < totalJogadores; i++) {
        strcpy(jogadores[i].nome, jogadores[i].nome); // Atribuir o nome do jogador
        sortearMissao(&jogadores[i]); // Sortear e atribuir uma missão para cada jogador
    }
    //Configurar os territórios
    for (int i = 0; i < totalTerritorios; i++) {
        strcpy(territorios[i].pais, territorios[i].pais); // Atribuir o nome do país ao território
        strcpy(territorios[i].cor, cores[i % MAX_COR]); // Atribuir uma cor ao território (pode ser repetida)
        territorios[i].tropas = rand() % MAX_TROPAS + 1; // Atribuir um número aleatório de tropas para o território
    }
}

//Função para a lógica do jogo, onde você pode implementar os turnos de ataque, verificação de missões e exibição do status do jogo
void logicaDoJogo(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios) {
    for (int turno = 0; turno < MAX_TURNOS; turno++) {
        printf("Turno %d\n", turno + 1);
        for (int i = 0; i < totalJogadores; i++) {
            printf("Vez de %s\n", jogadores[i].nome);
            //Aqui você pode implementar a lógica para o jogador escolher um território para atacar, validar o ataque, realizar o ataque e verificar se a missão foi cumprida ao final do turno.
            //Exemplo de lógica para ataque (você pode expandir isso para permitir que o jogador escolha os territórios de ataque e defesa):
            int atacanteIndex = rand() % totalTerritorios; // Índice aleatório para o território atacante
            int defensorIndex = rand() % totalTerritorios; // Índice aleatório para o território defensor
            if (validarAtaque(&jogadores[i], &territorios[atacanteIndex], &territorios[defensorIndex])) {
                atacar(&territorios[atacanteIndex], &territorios[defensorIndex]);
                atualizarCampos(&territorios[atacanteIndex], &territorios[defensorIndex]);
            }
            verificarVencedor(jogadores, totalJogadores, territorios, totalTerritorios);
            exibirStatus(jogadores, totalJogadores, territorios, totalTerritorios);
        }
    }
}

//Ponteiros para as funções, para garantir que elas sejam reconhecidas antes de serem chamadas na função main. Isso é importante para evitar erros de compilação relacionados a funções não declaradas.

//case 1
switch (opcoesMenu)
{
case 1:
    //Lógica para o ataque, onde o jogador escolhe um território para atacar e outro
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
    break;
}
}

//case 2
switch (opcoesMenu)
{case 2:
                imprimirSeparador();
                printf("         EXIBIÇÃO DO MAPA DO JOGO\n");
                imprimirSeparador();
                if (totalTerritorios == 0) {
                    printf("Nenhum território cadastrado. O mapa está vazio.\n");
                } else {
                    printf("Mapa do Jogo:\n");
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("[%d] Nome: %s, Cor: %s, Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                    }
                }
                printf("Pressione ENTER para continuar...\n");
                getchar();
                break;
}

//Protótipos das funções
void imprimirSeparador();
void limparTela();
void exibirMapa(struct TERRITORIO* territorios, int totalTerritorios);
void exibirMissao(struct JOGADOR* jogador);
void atribuirMissao(struct JOGADOR* jogador, const char* missao);
int verificarMissao(struct JOGADOR* jogador, struct TERRITORIO* territorios, int totalTerritorios);
void atacar(struct TERRITORIO* atacante, struct TERRITORIO* defensor);
void liberarMemoria(struct JOGADOR* jogadores, int totalJogadores);
struct JOGADOR* criarJogadores(int totalJogadores);
struct TERRITORIO* criarTerritorios(int totalTerritorios);
struct MISSAO* criarMissões(int totalMissões);
void atualizarCampos(struct TERRITORIO* atacante, struct TERRITORIO* defensor);
int validarAtaque(struct JOGADOR* jogador, struct TERRITORIO* atacante, struct TERRITORIO* defensor);
void exibirStatus(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void transferirTropas(struct TERRITORIO* atacante, struct TERRITORIO* defensor);
void exibirMissaoValor(char* missao);
void atribuirMissaoReferencia(char** missao, const char* novaMissao);
void sortearMissao(struct JOGADOR* jogador);
void verificarVencedor(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void salvarPartida(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void carregarPartida(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void inicializarJogo(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void logicaDoJogo(struct JOGADOR* jogadores, int totalJogadores, struct TERRITORIO* territorios, int totalTerritorios);
void exibirMenu();

//função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    struct JOGADOR* jogadores = criarJogadores(MAX_JOGADORES);
    struct TERRITORIO* territorios = criarTerritorios(MAX_TERRITORIOS);
    struct MISSAO* missoes = criarMissões(MAX_MISSOES);
    inicializarJogo(jogadores, MAX_JOGADORES, territorios, MAX_TERRITORIOS);
    //Aqui você pode chamar a função para exibir o menu e iniciar a lógica do jogo
    exibirMenu();
    // case 1, case 2, case 3, etc. para as opções do menu, onde você pode implementar as ações correspondentes para cada opção, como atacar, exibir o mapa, exibir a missão, salvar a partida, carregar a partida e sair do jogo.
    
   

    //cadastro de territórios, listagem de territórios, escolha de territórios para guerra, etc. Você pode implementar um loop para permitir que os jogadores escolham as opções do menu e interajam com o jogo.

    //Registro da lógica do jogo, onde você pode implementar a interação com o menu e as ações dos jogadores
    logicaDoJogo(jogadores, MAX_JOGADORES, territorios, MAX_TERRITORIOS);
    liberarMemoria(jogadores, MAX_JOGADORES);
    free(territorios);
    free(missoes);
    return 0;
}