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

//Constantes

//Estruturas

//Funções

// protótipos de funções

//função principal