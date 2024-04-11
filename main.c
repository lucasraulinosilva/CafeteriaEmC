#include <stdio.h>

/*definindo a variável de tamanho máximo*/
#define MAX_SIZE 100
#define TAM_MAX 10

int id = 1;

/*criando a estrutura do pedido*/
struct pedidoSimples {
  int idPedido;
  char itemPedido[50];
  char nomeCliente[50];
};

struct LstEstc {
  struct pedidoSimples pedidosSimples[TAM_MAX];
  int tamanho2;
};

/*criando a estrutura da fila*/
struct Fila {
  int inicio, fim, tamanho;
  int elementos[MAX_SIZE];
};

void inicializar(struct LstEstc* lista) {
  lista->tamanho2 = 0;
};

/*criando a função para inicializar a fila*/
void inicializarFila(struct Fila* fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

/*função para verificar se a fila está vazia*/
int estaVazia(struct Fila* fila) {
  return fila->tamanho == 0;
}

/*função para verificar se a fila está cheia*/
int estaCheia(struct Fila* fila) {
  return fila->tamanho == MAX_SIZE;
}

/*função para inserir um pedido*/
void inserirPedido(struct Fila* fila, int valor) {
  if (!estaCheia(fila)) {
    fila->fim = (fila->fim + 1) % MAX_SIZE;
    fila->elementos[fila->fim] = valor;
    fila->tamanho++;
  } else {
    printf("Erro: Fila cheia.\n");
  }
}

int dequeue(struct Fila* fila) {
  if (!estaVazia(fila)) {
    int valor = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_SIZE;
    fila->tamanho--;
    return valor;
  } else {
    printf("Erro: Fila vazia.\n");
    return -1;
  }
}

int peek(struct Fila* fila) {
  if (!estaVazia(fila)) {
    return fila->elementos[fila->inicio];
  } else {
    printf("Erro: Fila vazia.\n");
    return -1;
  }
}

/*função para imprimir a fila*/

int todosOsElementosDaFila(struct Fila* fila) {
  if (!estaVazia(fila)) {
    for(int i = 0; i < (id - 1); i++) {
      printf("%i\n", fila->elementos[i]);
    }
  } else {
    printf("Erro: Fila vazia.\n");
    return -1; // Return -1 to indicate error
  }
}

/*função para inserir pedido(lista) na fila de pedidos*/

void inserir(struct LstEstc* lista, struct Fila* fila, const int* idPedido, const char* itemPedido, const char* nomeCliente) { 
  if (lista->tamanho2 < TAM_MAX) { 
    // Se a lista não atingiu tamanho máximo
    // pode inserir

    // O valor do campo tamanho da lista é
    // equivalente à próxima posição livre do vetor
    lista->pedidosSimples[lista->tamanho2].idPedido = *idPedido;
    strcpy(lista->pedidosSimples[lista->tamanho2].itemPedido, itemPedido);
    strcpy(lista->pedidosSimples[lista->tamanho2].nomeCliente, nomeCliente);
    // Incrementar o campo tamanho da lista 
    lista->tamanho2++; 
    fila->fim = (fila->fim + 1) % MAX_SIZE;
    fila->elementos[fila->fim] = id;
    fila->tamanho++;
  } else { 
    // Se a lista já atingiu seu limite
    printf("Lista cheia. Impossível adicionar\n");
  }
}

void exibir(struct LstEstc* lista) { 
  printf("Lista de Pedidos:\n"); 
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i=0; i < lista->tamanho2; i++) { 
    printf("idPedido: %i, Item: %s, Nome Cliente: %s\n", 
      lista->pedidosSimples[i].idPedido, lista->pedidosSimples[i].itemPedido, lista->pedidosSimples[i].nomeCliente); 
  } 
} 

int main() {

  int condicao = 1;
  int quantidadeItensPedido = 0;
  char produto[50];
  char nomeCliente[50];

  /*Inicia a fila de pedidos*/
  
  struct Fila minhaFila;
  inicializarFila(&minhaFila);

  /*Inicia a lista de pedidos simples*/
  
  struct LstEstc pedidosSimples1;
  inicializar(&pedidosSimples1);

  /*inserir(&pedidosSimples1, &minhaFila, &id, "Café");
  inserir(&pedidosSimples1, &minhaFila, &id, "Café com leite");
  inserir(&pedidosSimples1, &minhaFila, &id, "Cookie");
  inserir(&pedidosSimples1, &minhaFila, &id, "Pão de queijo");*/

  while( condicao != 3 ) {
    printf("|--------------------------|\n");
    printf("|  MENU CAFETERIA FUMANTE  |\n");
    printf("|--------------------------|\n");
    printf("|         COMANDOS         |\n");
    printf("|--------------------------|\n");
    printf("|1 - INSERIR PEDIDOS       |\n");
    printf("|2 - MOSTRAR PEDIDOS       |\n");
    printf("|3 - SAIR DO SISTEMA       |\n");
    printf("|--------------------------|\n");
    scanf("%i", &condicao);
    if(condicao == 1 ) {
      printf("\n");
      printf("|Digite o nome do cliente  \n");
      scanf("%s", nomeCliente);
      printf("|Digite a quantidade de itens no pedido  \n");
      scanf("%i", &quantidadeItensPedido);
      for(int p = 0; p < quantidadeItensPedido; p++) {
        printf("|Digite o nome do produto  \n");
        scanf("%s", produto);
        inserir(&pedidosSimples1, &minhaFila, &id, produto, nomeCliente);
      }
      printf("|Pedido adicionado a fila  \n");
      printf("\n");
      id++;
    }
    if(condicao == 2) {
      printf("\n");
      exibir(&pedidosSimples1);
      printf("\n");
    }
  }

  /*cria os pedidos

  printf("Elemento no início da fila: %d\n", 
    peek(&minhaFila));

  printf("Removendo elemento: %d\n", dequeue(&minhaFila));
  printf("Elemento no início da fila após remoção: %d\n", 
    peek(&minhaFila));

  printf("Todos os elementos da fila:\n");
  todosOsElementosDaFila(&minhaFila);
    */
  
  // Exibir lista
  /*exibir(&pedidosSimples1);*/
  
  /*--------*/

  return 0;
}
