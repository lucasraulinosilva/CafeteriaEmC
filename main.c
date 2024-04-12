#include <stdio.h>

/*definindo a variável de tamanho máximo*/
#define MAX_SIZE 100
#define TAM_MAX 100

int idFilaSimples = 1;
int idFilaComplexa = 1;
int idProduto = 1;

/*criando a estrutura do pedido*/
struct pedido {
  int idPedido;
  char itemPedido[50];
  char nomeCliente[50];
  char estadoPedido[50];
};

struct listaProdutos {
  int idProduto;
  char nomeProduto[50];
  float precoProduto;
};

struct LstEstc {
  struct pedido pedido[TAM_MAX];
  int tamanho2;
};

struct LstEstcProdutos {
  struct listaProdutos listaProdutos[TAM_MAX];
  int tamanhoListaProdutos;
};

/*criando a estrutura da fila*/
struct Fila {
  int inicio, fim, tamanho;
  int elementos[MAX_SIZE];
};

void inicializarProdutos(struct LstEstcProdutos *produtos) {
  produtos->tamanhoListaProdutos = 0;
};

void inicializar(struct LstEstc *lista) { lista->tamanho2 = 0; };

/*criando a função para inicializar a fila*/
void inicializarFila(struct Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

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

/*função para verificar se a fila está vazia*/
int estaVazia(struct Fila *fila) { return fila->tamanho == 0; }

/*função para verificar se a fila está cheia*/
int estaCheia(struct Fila *fila) { return fila->tamanho == MAX_SIZE; }

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

/*função para inserir pedido(lista) na fila de pedidos*/

void inserir(struct LstEstc *lista, struct Fila *fila, const int *idPedido,
             const char *itemPedido, const char *nomeCliente,
             const char *estadoPedido, const int tipoFila) {
  if (lista->tamanho2 < TAM_MAX) {
    // Se a lista não atingiu tamanho máximo
    // pode inserir

    // O valor do campo tamanho da lista é
    // equivalente à próxima posição livre do vetor
    lista->pedido[lista->tamanho2].idPedido = *idPedido;
    strcpy(lista->pedido[lista->tamanho2].itemPedido, itemPedido);
    strcpy(lista->pedido[lista->tamanho2].nomeCliente, nomeCliente);
    strcpy(lista->pedido[lista->tamanho2].estadoPedido, estadoPedido);
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

void inserirProduto(struct LstEstcProdutos *produtos, char *nomeProduto,
                    float valor) {
  if (produtos->tamanhoListaProdutos < TAM_MAX) {
    // Se a lista não atingiu tamanho máximo
    // pode inserir

    // O valor do campo tamanho da lista é
    // equivalente à próxima posição livre do vetor
    produtos->listaProdutos[produtos->tamanhoListaProdutos].idProduto =
        idProduto;
    strcpy(produtos->listaProdutos[produtos->tamanhoListaProdutos].nomeProduto,
           nomeProduto);
    produtos->listaProdutos[produtos->tamanhoListaProdutos].precoProduto =
        valor;
    // Incrementar o campo tamanho da lista
    produtos->tamanhoListaProdutos++;
    idProduto++;
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
           lista->pedido[i].idPedido, lista->pedido[i].itemPedido,
           lista->pedido[i].nomeCliente, lista->pedido[i].estadoPedido);
  }
}

void exibirProdutos(struct LstEstcProdutos *produtos) {
  printf("Lista de Produtos :\n");
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i = 0; i < produtos->tamanhoListaProdutos; i++) {
    printf("idProduto: %i, Nome Produto: %s, Preço Produto: %.2f \n",
           produtos->listaProdutos[i].idProduto,
           produtos->listaProdutos[i].nomeProduto,
           produtos->listaProdutos[i].precoProduto);
  }
}

float calcularPrecoPedido(struct LstEstcProdutos *produtos,
                          char *nomeProdutoCalcular) {
  float precoTotalPedido = 0;
  for (int i = 0; i < produtos->tamanhoListaProdutos; i++) {
    if (strcmp(produtos->listaProdutos[i].nomeProduto, nomeProdutoCalcular) ==
        0) {
      precoTotalPedido += produtos->listaProdutos[i].precoProduto;
    }
  }
  return precoTotalPedido;
}

void alterarEstadoPedido(struct Fila *fila, struct LstEstc *lista,
                        struct LstEstcProdutos *produtos) {
  int inicioFila = (peek(fila) - 1);
  int condicao2 = 0;
  float valorTotalPedido = 0;
  if (!estaVazia(fila)) {
    for (int i = 0; i < lista->tamanho2; i++) {
      if (lista->pedido[i].idPedido == (inicioFila + 1)) {
        strcpy(lista->pedido[i].estadoPedido, "ENTREGUE");
        printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
               lista->pedido[i].idPedido, lista->pedido[i].itemPedido,
               lista->pedido[i].nomeCliente, lista->pedido[i].estadoPedido);
        valorTotalPedido +=
            calcularPrecoPedido(produtos, lista->pedido[i].itemPedido);
        dequeue(fila);
      }
    }
    condicao2 = 1;
    printf("Valor Total do pedido: %.2f\n", valorTotalPedido);
  } else {
    printf("Erro: Fila vazia.\n");
  }
}

int main() {

  int condicao = 1;
  int quantidadeItensPedido = 0;
  char produto[50];
  char nomeCliente[50];
  int tipoListaEntregarPedido;

  /*Inicia a lista de produtos*/

  struct LstEstcProdutos produtos;
  inicializarProdutos(&produtos);

  /*Inserindo produtos*/

  inserirProduto(&produtos, "Café", 5.0);
  inserirProduto(&produtos, "Cookie", 3.0);
  inserirProduto(&produtos, "Café_com_Leite", 6.0);
  inserirProduto(&produtos, "Audi_A3_1.8_aspirada_2003_Multada_e_Roubada", 6784.00);

  /*Inicia a fila de pedidos*/

  struct Fila filaPedidosSimples;
  inicializarFila(&filaPedidosSimples);

  struct Fila filaPedidosComplexos;
  inicializarFila(&filaPedidosComplexos);

  /*Inicia a lista de pedidos*/

  struct LstEstc dadosPedidosSimples;
  inicializar(&dadosPedidosSimples);

  struct LstEstc dadosPedidosComplexos;
  inicializar(&dadosPedidosComplexos);

  while (condicao != 5) {
    printf("|--------------------------|\n");
    printf("|  MENU CAFETERIA FUMANTE  |\n");
    printf("|--------------------------|\n");
    printf("|         COMANDOS         |\n");
    printf("|--------------------------|\n");
    printf("|1 - INSERIR PEDIDOS       |\n");
    printf("|2 - MOSTRAR PRODUTOS      |\n");
    printf("|3 - MOSTRAR PEDIDOS       |\n");
    printf("|4 - ENTREGAR PEDIDO       |\n");
    printf("|5 - SAIR DO SISTEMA       |\n");
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
          inserir(&dadosPedidosSimples, &filaPedidosSimples, &idFilaSimples,
                  produto, nomeCliente, "PENDENTE", 1);
          printf("|Pedido adicionado a fila  \n");
          printf("\n");
        } else {
          inserir(&dadosPedidosComplexos, &filaPedidosComplexos,
                  &idFilaComplexa, produto, nomeCliente, "PENDENTE", 2);
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
      exibirProdutos(&produtos);
      printf("\n");
    }
    if (condicao == 3) {
      printf("\n");
      exibir(&dadosPedidosSimples, "Simples");
      printf("\n");
      exibir(&dadosPedidosComplexos, "Complexos");
      printf("\n");
    }
    if (condicao == 4) {
      printf("\n");
      printf("|Pedido simples(1) ou complexo(2) ?  \n");
      scanf("%i", &tipoListaEntregarPedido);
      if (tipoListaEntregarPedido == 1) {
        alterarEstadoPedido(&filaPedidosSimples, &dadosPedidosSimples,
                            &produtos);
      } else if (tipoListaEntregarPedido == 2) {
        alterarEstadoPedido(&filaPedidosComplexos, &dadosPedidosComplexos,
                            &produtos);
      }
    }
  }

  return 0;
}
