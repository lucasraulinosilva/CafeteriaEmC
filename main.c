#include <stdio.h>

/*definindo a variável de tamanho máximo*/
#define MAX_SIZE 100
#define TAM_MAX 10

int idFilaSimples = 1;
int idFilaComplexa = 1;

/*criando a estrutura do pedido*/
struct pedidoSimples {
  int idPedido;
  char itemPedido[50];
  char nomeCliente[50];
  char estadoPedido[50];
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

void inicializar(struct LstEstc *lista) { lista->tamanho2 = 0; };

/*criando a função para inicializar a fila*/
void inicializarFila(struct Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

/*função para verificar se a fila está vazia*/
int estaVazia(struct Fila *fila) { return fila->tamanho == 0; }

/*função para verificar se a fila está cheia*/
int estaCheia(struct Fila *fila) { return fila->tamanho == MAX_SIZE; }

/*função para inserir um pedido*/
void inserirPedido(struct Fila *fila, int valor) {
  if (!estaCheia(fila)) {
    fila->fim = (fila->fim + 1) % MAX_SIZE;
    fila->elementos[fila->fim] = valor;
    fila->tamanho++;
  } else {
    printf("Erro: Fila cheia.\n");
  }
}

int dequeue(struct Fila *fila) {
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

int peek(struct Fila *fila) {
  if (!estaVazia(fila)) {
    return fila->elementos[fila->inicio];
  } else {
    printf("Erro: Fila vazia.\n");
    return -1;
  }
}

/*função para imprimir a fila*/

/*int todosOsElementosDaFila(struct Fila *fila) {
  if (!estaVazia(fila)) {
    for (int i = 0; i < (id - 1); i++) {
      printf("%i\n", fila->elementos[i]);
    }
  } else {
    printf("Erro: Fila vazia.\n");
    return -1; // Return -1 to indicate error
  }
}*/

/*função para inserir pedido(lista) na fila de pedidos*/

void inserir(struct LstEstc *lista, struct Fila *fila, const int *idPedido,
             const char *itemPedido, const char *nomeCliente,
             const char *estadoPedido, const int tipoFila) {
  if (lista->tamanho2 < TAM_MAX) {
    // Se a lista não atingiu tamanho máximo
    // pode inserir

    // O valor do campo tamanho da lista é
    // equivalente à próxima posição livre do vetor
    lista->pedidosSimples[lista->tamanho2].idPedido = *idPedido;
    strcpy(lista->pedidosSimples[lista->tamanho2].itemPedido, itemPedido);
    strcpy(lista->pedidosSimples[lista->tamanho2].nomeCliente, nomeCliente);
    strcpy(lista->pedidosSimples[lista->tamanho2].estadoPedido, estadoPedido);
    // Incrementar o campo tamanho da lista
    lista->tamanho2++;
    fila->fim = (fila->fim + 1) % MAX_SIZE;
    if (tipoFila == 1) {
      fila->elementos[fila->fim] = idFilaSimples;
    } else {
      fila->elementos[fila->fim] = idFilaComplexa;
    }
    fila->tamanho++;
  } else {
    // Se a lista já atingiu seu limite
    printf("Lista cheia. Impossível adicionar\n");
  }
}

void exibir(struct LstEstc *lista, char *TipoLista) {
  printf("Lista de Pedidos %s :\n", TipoLista);
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i = 0; i < lista->tamanho2; i++) {
    printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
           lista->pedidosSimples[i].idPedido,
           lista->pedidosSimples[i].itemPedido,
           lista->pedidosSimples[i].nomeCliente,
           lista->pedidosSimples[i].estadoPedido);
  }
}

/*int dequeue(struct Fila *fila) {
  if (!estaVazia(fila)) {
    int valor = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_SIZE;
    fila->tamanho--;
    return valor;
  } else {
    printf("Erro: Fila vazia.\n");
    return -1;
  }
}*/

int alterarEstadoPedido(struct Fila *fila, struct LstEstc *lista, int tipoLista) {
  int inicioFila = (peek(fila) - 1);
  int condicao2 = 0;
  if (!estaVazia(fila)) {
    if ( tipoLista == 1 ) {
       strcpy(lista->pedidosSimples[inicioFila].estadoPedido, "ENTREGUE");
       printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
          lista->pedidosSimples[inicioFila].idPedido,
          lista->pedidosSimples[inicioFila].itemPedido,
          lista->pedidosSimples[inicioFila].nomeCliente,
          lista->pedidosSimples[inicioFila].estadoPedido);
    } else if ( tipoLista == 2 ) {
        while( condicao2 == 0 ) {
          for( int i = 0; i < lista->tamanho2; i++ ) {
            if (lista->pedidosSimples[i].idPedido == (inicioFila + 1)){
              strcpy(lista->pedidosSimples[i].estadoPedido, "ENTREGUE");
              printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
                 lista->pedidosSimples[i].idPedido,
                 lista->pedidosSimples[i].itemPedido,
                 lista->pedidosSimples[i].nomeCliente,
                 lista->pedidosSimples[i].estadoPedido);
              dequeue(fila);
            }
          }
          condicao2 = 1;
        }

    }
  } else {
    printf("Erro: Fila vazia.\n");
    return -1;
  }
}

int main() {

  int condicao = 1;
  int quantidadeItensPedido = 0;
  char produto[50];
  char nomeCliente[50];
  int tipoListaEntregarPedido;

  /*Inicia a fila de pedidos*/

  struct Fila filaPedidosSimples;
  inicializarFila(&filaPedidosSimples);

  struct Fila filaPedidosComplexos;
  inicializarFila(&filaPedidosComplexos);

  /*Inicia a lista de pedidos*/

  struct LstEstc dadosPedidoSimples;
  inicializar(&dadosPedidoSimples);

  struct LstEstc dadosPedidosComplexos;
  inicializar(&dadosPedidosComplexos);
  

  while (condicao != 4) {
    printf("|--------------------------|\n");
    printf("|  MENU CAFETERIA FUMANTE  |\n");
    printf("|--------------------------|\n");
    printf("|         COMANDOS         |\n");
    printf("|--------------------------|\n");
    printf("|1 - INSERIR PEDIDOS       |\n");
    printf("|2 - MOSTRAR PEDIDOS       |\n");
    printf("|3 - ENTREGAR PEDIDO       |\n");
    printf("|4 - SAIR DO SISTEMA       |\n");
    printf("|--------------------------|\n");
    scanf("%i", &condicao);
    if (condicao == 1) {
      printf("\n");
      printf("|Digite o nome do cliente  \n");
      scanf("%s", nomeCliente);
      printf("|Digite a quantidade de itens no pedido  \n");
      scanf("%i", &quantidadeItensPedido);
      for (int p = 0; p < quantidadeItensPedido; p++) {
        printf("|Digite o nome do produto  \n");
        scanf("%s", produto);
        if (quantidadeItensPedido <= 3) {
          inserir(&dadosPedidoSimples, &filaPedidosSimples, &idFilaSimples, produto,
                  nomeCliente, "PENDENTE", 1);
          printf("|Pedido adicionado a fila  \n");
          printf("\n");
        } else {
          inserir(&dadosPedidosComplexos, &filaPedidosComplexos, &idFilaComplexa, produto,
                  nomeCliente, "PENDENTE", 2);
          printf("|Pedido adicionado a fila  \n");
          printf("\n");
        }
      }
      if (quantidadeItensPedido <= 3) {
        idFilaSimples++;
      } else {
        idFilaComplexa++;
      }
    }
    if (condicao == 2) {
      printf("\n");
      exibir(&dadosPedidoSimples, "Simples");
      printf("\n");
      exibir(&dadosPedidosComplexos, "Complexos");
    }
    if (condicao == 3) {
      printf("\n");
      printf("|Pedido simples(1) ou complexo(2) ?  \n");
      scanf("%i", &tipoListaEntregarPedido);
      if (tipoListaEntregarPedido == 1) {
        alterarEstadoPedido(&filaPedidosSimples, &dadosPedidoSimples, 1);
      } else if (tipoListaEntregarPedido == 2) {
        alterarEstadoPedido(&filaPedidosComplexos, &dadosPedidosComplexos, 2);
      } else {
        printf("número invalido");
        condicao = 4;
      }
      printf("\n");
    }
  }

  printf("Elemento no início da fila: %d\n",
    peek(&filaPedidosSimples));

  printf("Elemento no início da fila: %d\n",
    peek(&filaPedidosComplexos));

  /*cria os pedidos

  printf("Elemento no início da fila: %d\n",
    peek(&filaPedidosSimples));

  printf("Removendo elemento: %d\n", dequeue(&filaPedidosSimples));
  printf("Elemento no início da fila após remoção: %d\n",
    peek(&filaPedidosSimples));

  printf("Todos os elementos da fila:\n");
  todosOsElementosDaFila(&filaPedidosSimples);
    */

  // Exibir lista
  /*exibir(&dadosPedido);*/

  return 0;
}

