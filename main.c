#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*definindo a variável de tamanho máximo*/
#define MAX_SIZE 100
#define TAM_MAX 100

int idFilaSimples = 1;
int idFilaComplexa = 1;
int idProduto = 1;
int idFuncionario = 1;
char senha[50];

/*criando a estrutura de funcionarios*/
struct funcionario {
  int idFuncionario;
  char nomeFuncionario[50];
  char cargoFuncionario[50];
  char turno[50];
  float salario;
};

struct LstFunc {
  struct funcionario funcionario[TAM_MAX];
  int tamanhoListaFuncionarios;
};

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

void inicializarFuncionarios(struct LstFunc *funcionarios) {
  funcionarios->tamanhoListaFuncionarios = 0;
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
    printf("Fila vazia.\n");
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

/*função para inserir um funcionário*/

void inserirFuncionario(struct LstFunc *funcionarios, char *nomeFuncionario,
                        char *cargoFuncionario, char *turno, float salario) {
  if (funcionarios->tamanhoListaFuncionarios < TAM_MAX) {
    // Se a lista não atingiu tamanho máximo
    // pode inserir

    // O valor do campo tamanho da lista é
    // equivalente à próxima posição livre do vetor

    funcionarios->funcionario[funcionarios->tamanhoListaFuncionarios]
        .idFuncionario = idFuncionario;
    strcpy(funcionarios->funcionario[funcionarios->tamanhoListaFuncionarios]
               .nomeFuncionario,
           nomeFuncionario);
    strcpy(funcionarios->funcionario[funcionarios->tamanhoListaFuncionarios]
               .cargoFuncionario,
           cargoFuncionario);
    strcpy(
        funcionarios->funcionario[funcionarios->tamanhoListaFuncionarios].turno,
        turno);
    funcionarios->funcionario[funcionarios->tamanhoListaFuncionarios].salario =
        salario;
    // Incrementar o campo tamanho da lista
    funcionarios->tamanhoListaFuncionarios++;
    idFuncionario++;
  } else {
    // Se a lista já atingiu seu limite
    printf("Lista cheia. Impossível adicionar\n");
  }
}

/*função para procurar funcionário*/

int procurarFuncionario(struct LstFunc *funcionarios, int idFuncionario) {
  int validadorProcurarFuncionario = 0;

  if (idFuncionario <= funcionarios->tamanhoListaFuncionarios) {
    for (int i = 0; i <= idFuncionario; i++) {
      if ((i + 1) == funcionarios->funcionario[i].idFuncionario) {
        validadorProcurarFuncionario = 1;
      }
    }
  }

  return validadorProcurarFuncionario;
}

/*função para remover um funcionário*/

void removerFuncionario(struct LstFunc *funcionarios,
                        int idFuncionarioRemover) {
  /*if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida. Impossível remover.\n");
    return;
  }*/

  int resultadoProcuraFuncionario =
      procurarFuncionario(funcionarios, idFuncionarioRemover);

  if (resultadoProcuraFuncionario == 1) {
    for (int i = (idFuncionarioRemover - 1);
         i < funcionarios->tamanhoListaFuncionarios - 1; i++) {
      funcionarios->funcionario[i] = funcionarios->funcionario[i + 1];
    }

    funcionarios->tamanhoListaFuncionarios--;
    printf("Funcionário removido com sucesso \n");
  } else {
    printf("Funcionário com id não identificado \n");
  }
}

/*função para inserir um produto*/

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

/*void exibir(struct LstEstc *lista, char *TipoLista) {
  printf("Lista de Pedidos %s :\n", TipoLista);
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i = 0; i < lista->tamanho2; i++) {
    printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
           lista->pedido[i].idPedido, lista->pedido[i].itemPedido,
           lista->pedido[i].nomeCliente, lista->pedido[i].estadoPedido);
  }
}*/

void exibirHistorico(struct LstEstc *lista, char *TipoLista) {
  printf("Lista de Pedidos %s :\n", TipoLista);
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i = 0; i < lista->tamanho2; i++) {
    if (strcmp(lista->pedido[i].estadoPedido, "ENTREGUE") == 0) {
        printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
               lista->pedido[i].idPedido, lista->pedido[i].itemPedido,
               lista->pedido[i].nomeCliente, lista->pedido[i].estadoPedido);
      }
    }
}

void exibirProximoPedido(struct LstEstc *lista, char *TipoLista, struct Fila *Fila) {
  printf("Lista de Pedidos %s :\n", TipoLista);
  // Percorre do primeiro elemento até o último
  // que é aquele apontado pelo campo ‘tamanho’
  for (int i = 0; i < lista->tamanho2; i++) {
    if (lista->pedido[i].idPedido == peek(Fila)) {
      printf("idPedido: %i, Item: %s, Nome Cliente: %s, Estado Pedido: %s\n",
       lista->pedido[i].idPedido, lista->pedido[i].itemPedido,
       lista->pedido[i].nomeCliente, lista->pedido[i].estadoPedido);
    }
  }
}

void exibirFuncionarios(struct LstFunc *funcionarios) {
  printf("Lista de Funcionarios :\n");

  for (int i = 0; i < funcionarios->tamanhoListaFuncionarios; i++) {
    printf(
        "idFuncionario: %i, Nome: %s, Cargo: %s, Turno: %s, Salario: %.2f \n",
        funcionarios->funcionario[i].idFuncionario,
        funcionarios->funcionario[i].nomeFuncionario,
        funcionarios->funcionario[i].cargoFuncionario,
        funcionarios->funcionario[i].turno,
        funcionarios->funcionario[i].salario);
  }
}

void exibirFuncionariosPorTurno(struct LstFunc *funcionarios) {
  printf("Turno Matutino: \n");
  for (int i = 0; i < funcionarios->tamanhoListaFuncionarios; i++) {
    if (strcmp(funcionarios->funcionario[i].turno, "Matutino") == 0) {
      printf(
          "idFuncionario: %i, Nome: %s, Cargo: %s, Turno: %s, Salario: %.2f \n",
          funcionarios->funcionario[i].idFuncionario,
          funcionarios->funcionario[i].nomeFuncionario,
          funcionarios->funcionario[i].cargoFuncionario,
          funcionarios->funcionario[i].turno,
          funcionarios->funcionario[i].salario);
    }
  }
  printf("\n");
  printf("Turno Noturno: \n");
  for (int i = 0; i < funcionarios->tamanhoListaFuncionarios; i++) {
    if (strcmp(funcionarios->funcionario[i].turno, "Noturno") == 0) {
      printf(
          "idFuncionario: %i, Nome: %s, Cargo: %s, Turno: %s, Salario: %.2f \n",
          funcionarios->funcionario[i].idFuncionario,
          funcionarios->funcionario[i].nomeFuncionario,
          funcionarios->funcionario[i].cargoFuncionario,
          funcionarios->funcionario[i].turno,
          funcionarios->funcionario[i].salario);
    }
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

char *calcularPrecoPedidoId(struct LstEstcProdutos *produtos,
                            int idProdutoCalcular) {
  float precoTotalPedido = 0;
  static char nomeProduto[50];
  for (int i = 0; i < produtos->tamanhoListaProdutos; i++) {
    if (produtos->listaProdutos[i].idProduto == idProdutoCalcular) {
      precoTotalPedido += produtos->listaProdutos[i].precoProduto;
      strcpy(nomeProduto, produtos->listaProdutos[i].nomeProduto);
    }
  }
  return nomeProduto;
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

void definirSenha(char novaSenha[]) { strcpy(senha, novaSenha); }

void menuPedidos() {
  printf("|----------------------------|\n");
  printf("|  MENU CAFETERIA FUMEGANTE  |\n");
  printf("|----------------------------|\n");
  printf("|          COMANDOS          |\n");
  printf("|----------------------------|\n");
  printf("|1 - INSERIR PEDIDOS         |\n");
  printf("|2 - MOSTRAR PRODUTOS        |\n");
  printf("|3 - PROXIMO PEDIDO          |\n");
  printf("|4 - ENTREGAR PEDIDO         |\n");
  printf("|5 - HISTORICO               |\n");
  printf("|6 - MUDAR MENU              |\n");
  printf("|7 - SAIR DO SISTEMA         |\n");
  printf("|----------------------------|\n");
}

void menuPrincipal() {
  printf("|----------------------------|\n");
  printf("|  MENU CAFETERIA FUMEGANTE  |\n");
  printf("|----------------------------|\n");
  printf("|          COMANDOS          |\n");
  printf("|----------------------------|\n");
  printf("|1 - MENU PEDIDOS            |\n");
  printf("|2 - MENU FUNCIONÁRIOS       |\n");
  printf("|----------------------------|\n");
}

void menuFuncionarios() {
  printf("|----------------------------|\n");
  printf("|  MENU CAFETERIA FUMEGANTE  |\n");
  printf("|----------------------------|\n");
  printf("|          COMANDOS          |\n");
  printf("|----------------------------|\n");
  printf("|1 - EXIBIR FUNCIONÁRIOS     |\n");
  printf("|2 - INSERIR FUNCIONÁRIO     |\n");
  printf("|3 - REMOVER FUNCIONÁRIO     |\n");
  printf("|4 - FUNCIONÁRIOS POR TURNO  |\n");
  printf("|5 - MUDAR MENU              |\n");
  printf("|6 - SAIR DO SISTEMA         |\n");
  printf("|----------------------------|\n");
}

int main() {

  int condicao;
  int quantidadeItensPedido = 0;
  char produto[50];
  char nomeCliente[50];
  int tipoListaEntregarPedido;
  int validador = 0;
  char verificarSenha[50];
  int validadorMenuPrincipal;
  int validadorMenuFuncionarios = 0;
  char nomeFuncionario[50];
  char cargoFuncionario[50];
  char turnoFuncionario[50];
  float salarioFuncionario;
  int idFuncionarioExcluido;
  int loopMenuPrincipal = 0;

  /*Definindo a senha do sistema*/

  definirSenha("123");

  /*Inicia a lista de funcionários*/

  struct LstFunc funcionarios;
  inicializarFuncionarios(&funcionarios);

  /*Inserindo funcionários*/

  inserirFuncionario(&funcionarios, "Pedrão", "Atendente", "Matutino", 1300.00);
  inserirFuncionario(&funcionarios, "Fefo", "Atendente", "Noturno", 1300.00);
  inserirFuncionario(&funcionarios, "Kevin", "Operador de Caixa", "Matutino",
                     1500.00);
  inserirFuncionario(&funcionarios, "Fernanda", "Operador de Caixa", "Noturno",
                     1500.00);

  /*Inicia a lista de produtos*/

  struct LstEstcProdutos produtos;
  inicializarProdutos(&produtos);

  /*Inserindo produtos*/

  inserirProduto(&produtos, "Café", 5.0);
  inserirProduto(&produtos, "Cookie", 3.0);
  inserirProduto(&produtos, "Café_com_Leite", 6.0);

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

  printf("Digite a senha\n");
  scanf("%s", verificarSenha);

  while (loopMenuPrincipal == 0) {
    if (strcmp(verificarSenha, senha) == 0) {
      printf("\n");
      menuPrincipal();
      scanf("%i", &validadorMenuPrincipal);
      if (validadorMenuPrincipal == 1) {
        while (condicao != 7) {
          printf("\n");
          menuPedidos();
          scanf("%i", &condicao);
          if (condicao == 1) {
            printf("\n");
            printf("|Digite o nome do cliente  \n");
            scanf("%s", nomeCliente);
            printf("|Digite a quantidade de itens no pedido  \n");
            scanf("%i", &quantidadeItensPedido);
            for (int p = 0; p < quantidadeItensPedido; p++) {
              while (validador == 0) {
                printf("|Digite o nome do produto ou seu Id \n");
                scanf("%s", produto);
                if (calcularPrecoPedido(&produtos, produto)) {
                  validador = 1;
                } else if (calcularPrecoPedidoId(&produtos, atoi(produto))) {
                  strcpy(produto,
                         calcularPrecoPedidoId(&produtos, atoi(produto)));
                  validador = 1;
                } else {
                  printf("Produto não identificado \n");
                  printf("\n");
                  validador = 0;
                }
              }
              validador = 0;
              if (quantidadeItensPedido <= 3) {
                inserir(&dadosPedidosSimples, &filaPedidosSimples,
                        &idFilaSimples, produto, nomeCliente, "PENDENTE", 1);
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
          } else if (condicao == 2) {
            printf("\n");
            exibirProdutos(&produtos);
            printf("\n");
          } else if (condicao == 3) {
            printf("\n");
            exibirProximoPedido(&dadosPedidosSimples, "Simples", &filaPedidosSimples);
            printf("\n");
            exibirProximoPedido(&dadosPedidosComplexos, "Complexos", &filaPedidosComplexos);
            printf("\n");
          } else if (condicao == 4) {
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
          } else if (condicao == 5) {
            printf("\n");
            exibirHistorico(&dadosPedidosSimples, "Simples");
            printf("\n");
            exibirHistorico(&dadosPedidosComplexos, "Complexos");
            printf("\n");
          } else if (condicao == 6) {
            printf("\n");
            break;
            printf("\n");
          } else if (condicao == 7) {
            printf("\n");
            loopMenuPrincipal = 1;
            printf("Programa desligado");
            printf("\n");
            break;
          } else {
            loopMenuPrincipal = 1;
            printf("\n");
            printf("Caractere inválido \n");
            printf("Programa desligado");
            break;
          }
          condicao = 0;
        }
      } else if (validadorMenuPrincipal == 2) {
        while (validadorMenuFuncionarios != 6) {
          printf("\n");
          menuFuncionarios();
          scanf("%i", &validadorMenuFuncionarios);
          if (validadorMenuFuncionarios == 1) {
            printf("\n");
            exibirFuncionarios(&funcionarios);
            printf("\n");
          } else if (validadorMenuFuncionarios == 2) {
            printf("\n");
            printf("Digite o nome do funcionário: \n");
            scanf("%s", nomeFuncionario);
            printf("Digite o cargo: \n");
            scanf("%s", cargoFuncionario);
            printf("Digite o turno: \n");
            scanf("%s", turnoFuncionario);
            printf("Digite o salario: \n");
            scanf("%f", &salarioFuncionario);
            inserirFuncionario(&funcionarios, nomeFuncionario, cargoFuncionario,
                               turnoFuncionario, salarioFuncionario);
            printf("\n");
          } else if (validadorMenuFuncionarios == 3) {
            printf("\n");
            printf("Digite o id do funcionário a ser removido: \n");
            scanf("%i", &idFuncionarioExcluido);
            removerFuncionario(&funcionarios, idFuncionarioExcluido);
            printf("\n");
          } else if (validadorMenuFuncionarios == 4) {
            printf("\n");
            exibirFuncionariosPorTurno(&funcionarios);
            printf("\n");
          } else if (validadorMenuFuncionarios == 5) {
            printf("\n");
            break;
            printf("\n");
          } else if (validadorMenuFuncionarios == 6) {
            printf("\n");
            loopMenuPrincipal = 1;
            printf("Programa desligado");
            printf("\n");
            break;
          } else {
            loopMenuPrincipal = 1;
            printf("\n");
            printf("Caractere inválido \n");
            printf("Programa desligado");
            break;
          }
          validadorMenuFuncionarios = 0;
        }
      } else {
        printf("Caractere inválido \n");
      }
    }
  }

  return 0;
}
