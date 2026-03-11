/*

Requisitos funcionais


Veja os passos para criar e manipular uma estrutura que representa territórios em um sistema simples.

 

 Criação da struct: definir uma struct chamada Territorio com os campos 
 char nome[30], 
 char cor[10] e 
 int tropas.
  
  Cadastro dos territórios: o sistema deve permitir que o usuário cadastre cinco territórios informando o nome, cor do exército e o número de tropas de cada um.
   
   Exibição dos dados: o sistema deve exibir as informações de todos os territórios registrados após o cadastro.

   Requisitos não funcionais


   Inclua também os seguintes critérios para ter um código funcional, eficiente e fácil de entender:

    

    Usabilidade: a interface de entrada deve ser simples e clara, com mensagens que orientem o usuário sobre o que digitar.
     
     Desempenho: o sistema deve apresentar os dados logo após o cadastro, com tempo de resposta inferior a 2 segundos.
      
      Documentação: o código deve conter comentários explicativos sobre a criação da struct, entrada e exibição de dados.
       
       Manutenibilidade: os nomes das variáveis e funções devem ser claros e representativos, facilitando a leitura e manutenção do código.

*/

/*

Instruções detalhadas


Siga os passos a seguir para implementar o programa de cadastro de territórios:

 

 Bibliotecas necessárias: inclua as bibliotecas stdio.h e string.h.
  
  Definição da struct: crie a struct Territorio com os campos mencionados.
   
   Declaração de vetor de structs: crie um vetor com capacidade para armazenar 5 estruturas do tipo Territorio.
    
    Entrada dos dados: utilize um laço for para preencher os dados dos 5 territórios.
     
     Exibição: percorra, após o cadastro, o vetor e exiba os dados de cada território com formatação clara.

     Requisitos técnicos adicionais


     Aqui estão algumas orientações adicionais para uma implementação correta e bem documentada:

      

      Use scanf para ler o nome e o número de tropas.
       
       Utilize fgets ou scanf("%s", ...) com cuidado para strings.
        
        Comente seu código explicando a criação e o uso da struct e a lógica do laço de entrada e saída.

*/

//bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes

#define MAX_TERRITORIOS 5

//estrutura

struct territorio
{
   char nome [30];
   char cor [10];
   int tropas;
};

//funcao limpa_buffer

void limpa_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//funcao principal

int main()
{
    struct territorio territorios[MAX_TERRITORIOS];
    int totalCadastrados = 0;           // contador de territórios já gravados
    int opcao;

    // laço principal com menu de opções
    do {
        // exibe menu de opções
        printf("----------------------------------------\n");
        printf("1. Cadastrar territorio\n");
        printf("2. Exibir territorios\n");
        printf("3. Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        // lê a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            limpa_buffer();
            opcao = -1; // força case default
        }
        limpa_buffer(); // limpa o '\n' deixado pelo scanf

        // processamento da opção
        switch (opcao)
        {
            case 1: // cadastro de territorio
                if (totalCadastrados < MAX_TERRITORIOS)
                {
                    printf("Digite o nome do territorio: Exemplo 'Europa'\n");
                    fgets(territorios[totalCadastrados].nome,
                          sizeof(territorios[totalCadastrados].nome),
                          stdin);
                    printf("Digite a cor do exército: Exemplo 'Azul'\n");
                    fgets(territorios[totalCadastrados].cor,
                          sizeof(territorios[totalCadastrados].cor),
                          stdin);
                    printf("Digite o número de tropas: Exemplo '1000'\n");
                    scanf("%d", &territorios[totalCadastrados].tropas);
                    limpa_buffer();

                    // remover nova linha deixada por fgets
                    territorios[totalCadastrados].nome[
                        strcspn(territorios[totalCadastrados].nome, "\n")
                    ] = '\0';
                    territorios[totalCadastrados].cor[
                        strcspn(territorios[totalCadastrados].cor, "\n")
                    ] = '\0';

                    totalCadastrados++;
                    printf("Território cadastrado com sucesso!\n");
                }
                else
                {
                    printf("Número máximo de territórios atingido.\n");
                }
                break;

            case 2: // exibir territorios
                if (totalCadastrados == 0) {
                    printf("Nenhum território cadastrado.\n");
                } else {
                    printf("Territórios cadastrados:\n");
                    for (int j = 0; j < totalCadastrados; j++)
                    {
                        printf("Território %d:\n", j + 1);
                        printf("Nome: %s\n", territorios[j].nome);
                        printf("Cor do exército: %s\n", territorios[j].cor);
                        printf("Número de tropas: %d\n", territorios[j].tropas);
                        printf("-----------------------------\n");
                    }
                }
                break;

            case 3: // sair
                printf("Saindo do programa...\n");
                break;

            default: // opção inválida
                printf("Opção inválida, tente novamente.\n");
                break;
        }

    } while (opcao != 3);

    return 0;
}
