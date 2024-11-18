#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Paulo Hudson 22.222.013-9
// Danillo 22.222.008-9

// Estruturas
typedef struct Data {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Registro {
  char nome[50];
  int idade;
  char rg[15];
  Data entrada;
} Registro;

typedef struct Elista {
  Registro dados;
  struct Elista *proximo;
} Elista;

typedef struct Lista {
  Elista *inicio;
  int qtde;
} Lista;

typedef struct Efila {
  Registro dados;
  struct Efila *proximo;
} Efila;

typedef struct Fila {
  Efila *head;
  Efila *tail;
  int qtde;
} Fila;

typedef struct EStack {
  Registro dados;
  struct EStack *proximo;
} EStack;

typedef struct Stack {
  EStack *topo;
  int qtde;
} Stack;

typedef struct Vertice {
  int dadosPesq;
  Registro dados;
  struct Vertice *esq;
  struct Vertice *dir;
  struct Vertice *pai;
} Vertice;

typedef struct Arvore {
  Vertice *raiz;
  int qtde;
} Arvore;

Vertice *cria_vertice(int valor);
Vertice *inserirNoArvore(Vertice *raiz, Registro dados, int valorFiltro);
void mostrarListaFiltrada(Lista *lista);

//-----------------------------------------
void inicializarLista(Lista *lista) {
  lista->inicio = NULL;
  lista->qtde = 0;
}

void inicializarFila(Fila *fila) {
  fila->head = NULL;
  fila->tail = NULL;
  fila->qtde = 0;
}

void inicializarStack(Stack *stack) {
  stack->topo = NULL;
  stack->qtde = 0;
}

//-------Funções da fila atendimento-------------
void enfileirarPaciente(Fila *fila, Lista *lista) {
  char nome[50];
  printf("Digite o nome do paciente para enfileirar: ");
  scanf(" %[^\n]s", nome);

  Elista *paciente = lista->inicio;
  while (paciente) {
    if (strcmp(paciente->dados.nome, nome) == 0) {
      Efila *novo = (Efila *)malloc(sizeof(Efila));
      if (!novo) {
        printf("Erro ao alocar memoria.\n");
        return;
      }
      novo->dados = paciente->dados;
      novo->proximo = NULL;

      if (fila->head == NULL) {
        fila->head = novo;
        fila->tail = novo;
      } else {
        fila->tail->proximo = novo;
        fila->tail = novo;
      }
      fila->qtde++;
      printf("Paciente '%s' enfileirado com sucesso!\n", nome);
      return;
    }
    paciente = paciente->proximo;
  }
  printf("Paciente nao encontrado no cadastro.\n");
}

void desenfileirarPaciente(Fila *fila, Stack *stack) {
  if (fila->head == NULL) {
    printf("Fila vazia.\n");
    return;
  }

  Efila *remover = fila->head;
  fila->head = fila->head->proximo;
  if (fila->head == NULL) {
    fila->tail = NULL;
  }
  printf("Paciente '%s' atendido e removido.\n", remover->dados.nome);

  // Empilhar o paciente atendido na pilha
  EStack *novoNo = (EStack *)malloc(sizeof(EStack));
  if (!novoNo) {
    printf("Erro ao alocar memoria.\n");
    free(remover);
    fila->qtde--;
    return;
  }
  novoNo->dados = remover->dados;
  novoNo->proximo = stack->topo;
  stack->topo = novoNo;
  stack->qtde++;

  free(remover);
  fila->qtde--;
}

void desfazerAtendimento(Fila *fila, Stack *stack) {
  if (stack->topo == NULL) {
    printf("Nao ha atendimentos.\n");
    return;
  }

  // Desempilhar o uultimo atendimento
  EStack *remover = stack->topo;
  stack->topo = stack->topo->proximo;
  stack->qtde--;

  // Reenfilirar o paciente no início da fila
  Efila *novo = (Efila *)malloc(sizeof(Efila));
  if (!novo) {
    printf("Erro ao alocar memória.\n");
    free(remover);
    return;
  }
  novo->dados = remover->dados;
  novo->proximo = fila->head;
  fila->head = novo;
  if (fila->tail == NULL) {
    fila->tail = novo;
  }
  fila->qtde++;

  printf("Atendimento do paciente '%s' desfeito e paciente reenfileirado.\n", remover->dados.nome);
  free(remover);
}

void mostrarFila(Fila *fila) {
  if (fila->head == NULL) {
    printf("A fila Fila Vazia.\n");
    return;
  }

  Efila *aux = fila->head;
  printf("Fila de Atendimento:\n");
  while (aux) {
    printf("Nome: %s | Idade: %d | RG: %s | Data de Entrada: %02d/%02d/%04d\n",
           aux->dados.nome, aux->dados.idade, aux->dados.rg,
           aux->dados.entrada.dia, aux->dados.entrada.mes,
           aux->dados.entrada.ano);
    aux = aux->proximo;
  }
}

void menuAtendimento(Fila *fila, Lista *lista, Stack *stack) {
  int opcao;
  do {
    printf("\n============================\n");
    printf("       Menu Atendimento         \n");
    printf("============================\n");
    printf("1. Enfileirar paciente\n");
    printf("2. Desenfileirar paciente\n");
    printf("3. Mostrar fila\n");
    printf("4. Desfazer ultimo atendimento\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma option: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      enfileirarPaciente(fila, lista);
      break;
    case 2:
      desenfileirarPaciente(fila, stack);
      break;
    case 3:
      mostrarFila(fila);
      break;
    case 4:
      desfazerAtendimento(fila, stack);
      break;
    case 0:
      printf("Voltando ao menu principal...\n");
      break;
    default:
      printf("Opcao inválida.\n");
    }
  } while (opcao != 0);
}

void Sobre() {
  printf("\n============================\n");
  printf("         Sobre Nos         \n");
  printf("============================\n");
  printf("1. Desenvolvedores: Paulo e Danillo\n");
  printf("2. Curso: Ciencia da Computação - 4º Ciclo\n");
  printf("3. Disciplina: Estrutura de Dados\n");
  printf("4. Data: 18/11/2024\n");
  printf("============================\n");
}

//------- Funções da lista de pacientes -------
void cadastrarPaciente(Lista *lista) {
  Elista *novo = (Elista *)malloc(sizeof(Elista));
  if (!novo) {
    printf("Erro ao alocar memória.\n");
    return;
  }

  printf("Nome: ");
  scanf(" %[^\n]s", novo->dados.nome);
  printf("Idade: ");
  scanf("%d", &novo->dados.idade);
  printf("RG: ");
  scanf(" %[^\n]s", novo->dados.rg);
  printf("Data de Entrada (dd mm aaaa): ");
  scanf("%d %d %d", &novo->dados.entrada.dia, &novo->dados.entrada.mes,
        &novo->dados.entrada.ano);

  novo->proximo = lista->inicio;
  lista->inicio = novo;
  lista->qtde++;

  printf("Cadastrado com sucesso!\n");
}

void mostrarListaCompleta(Lista *lista) {
  if (lista->inicio == NULL) {
    printf("Fila Vazia.\n");
    return;
  }
  Elista *aux = lista->inicio;
  printf("Lista de Pacientes:\n");
  printf("=============================:\n\n");
  while (aux) {
    printf("Nome: %s | Idade: %d | RG: %s | Data de Entrada: %02d/%02d/%04d\n",
           aux->dados.nome, aux->dados.idade, aux->dados.rg,
           aux->dados.entrada.dia, aux->dados.entrada.mes,
           aux->dados.entrada.ano);
    aux = aux->proximo;
  }
}

void removerPaciente(Lista *lista) {
  char nome[50];
  printf("Digite o nome do paciente a remover: ");
  scanf(" %[^\n]s", nome);

  Elista *aux = lista->inicio;
  Elista *anterior = NULL;

  while (aux) {
    if (strcmp(aux->dados.nome, nome) == 0) {
      if (anterior == NULL) {
        lista->inicio = aux->proximo;
      } else {
        anterior->proximo = aux->proximo;
      }
      free(aux);
      lista->qtde--;
      printf("Paciente removido com sucesso!\n");
      return;
    }
    anterior = aux;
    aux = aux->proximo;
  }
  printf("Paciente nao encontrado.\n");
}

void atualizarPaciente(Lista *lista) {
  char nome[50];
  printf("Digite o nome do paciente para atualizar: ");
  scanf(" %[^\n]s", nome);

  Elista *aux = lista->inicio;
  while (aux) {
    if (strcmp(aux->dados.nome, nome) == 0) {
      printf("Atualizando dados do paciente...\n");
      printf("Novo nome: ");
      scanf(" %[^\n]s", aux->dados.nome);
      printf("Nova idade: ");
      scanf("%d", &aux->dados.idade);
      printf("Novo RG: ");
      scanf(" %[^\n]s", aux->dados.rg);
      printf("Nova data de entrada (dd mm aaaa): ");
      scanf("%d %d %d", &aux->dados.entrada.dia, &aux->dados.entrada.mes,
            &aux->dados.entrada.ano);

      printf("Dados atualizados com sucesso!\n");
      return;
    }
    aux = aux->proximo;
  }
  printf("Paciente não encontrado.\n");
}

void consultarPaciente(Lista *lista) {
  char nome[50];
  printf("Digite o nome do paciente para consulta: ");
  scanf(" %[^\n]s", nome);

  Elista *aux = lista->inicio;
  while (aux) {
    if (strcmp(aux->dados.nome, nome) == 0) {
      printf("Paciente encontrado:\n");
      printf(
          "Nome: %s | Idade: %d | RG: %s | Data de Entrada: %02d/%02d/%04d\n",
          aux->dados.nome, aux->dados.idade, aux->dados.rg,
          aux->dados.entrada.dia, aux->dados.entrada.mes,
          aux->dados.entrada.ano);
      return;
    }
    aux = aux->proximo;
  }
  printf("Paciente nao encontrado.\n");
}

// Funções para pesquisa e mostra de dados
Vertice *cria_vertice(int valor) {
  Vertice *novo = malloc(sizeof(Vertice));
  if (!novo) {
    printf("Erro ao alocar memória para o vertice.\n");
    return NULL;
  }
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = NULL;
  novo->dadosPesq = valor;
  return novo;
}

Vertice *inserirNoArvore(Vertice *raiz, Registro dados, int valorFiltro) {
  if (raiz == NULL) {
    Vertice *novo = cria_vertice(valorFiltro);
    if (!novo) {
      printf("Erro ao alocar memoria.\n");
      return NULL;
    }
    novo->dados = dados;
    return novo;
  }

  if (valorFiltro < raiz->dadosPesq) {
    raiz->esq = inserirNoArvore(raiz->esq, dados, valorFiltro);
  } else if (valorFiltro > raiz->dadosPesq) {
    raiz->dir = inserirNoArvore(raiz->dir, dados, valorFiltro);
  } else {
    raiz->esq = inserirNoArvore(raiz->esq, dados, valorFiltro);
  }

  return raiz;
}

void mostrarEmOrdem(Vertice *raiz) {
  if (raiz != NULL) {
    mostrarEmOrdem(raiz->esq);
    printf("Nome: %s | Idade: %d | RG: %s | Data de Entrada: %02d/%02d/%04d\n",
           raiz->dados.nome, raiz->dados.idade, raiz->dados.rg,
           raiz->dados.entrada.dia, raiz->dados.entrada.mes,
           raiz->dados.entrada.ano);
    mostrarEmOrdem(raiz->dir);
  }
}

void liberar_arvore(Vertice *vertice) {
  if (vertice != NULL) {
    liberar_arvore(vertice->esq);
    liberar_arvore(vertice->dir);
    free(vertice);
  }
}

void mostrarListaFiltrada(Lista *lista) {
  if (lista->inicio == NULL) {
    printf("Fila Vazia.\n");
    return;
  }

  int opcaoFiltro;
  do {
    printf("\n--- Escolha o filtro de pesquisa ---\n");
    printf("1. Filtrar por ano de registro\n");
    printf("2. Filtrar por mes de registro\n");
    printf("3. Filtrar por dia de registro\n");
    printf("4. Filtrar por idade do paciente\n");
    printf("0. Sair\n");
    printf("Digite a option: ");
    scanf("%d", &opcaoFiltro);

    if (opcaoFiltro == 0) {
      printf("Operacao cancelada pelo usuário.\n");
      return;
    } else if (opcaoFiltro < 0 || opcaoFiltro > 4) {
      printf("Opcao invalida. Tente novamente.\n");
    } else {
      break;
    }
  } while (1);

  Arvore arvoreFiltrada;
  arvoreFiltrada.raiz = NULL;
  arvoreFiltrada.qtde = 0;

  Elista *aux = lista->inicio;
  while (aux) {
    int valorFiltro;
    switch (opcaoFiltro) {
    case 1:
      valorFiltro = aux->dados.entrada.ano;
      break;
    case 2:
      valorFiltro = aux->dados.entrada.mes;
      break;
    case 3:
      valorFiltro = aux->dados.entrada.dia;
      break;
    case 4:
      valorFiltro = aux->dados.idade;
      break;
    default:
      valorFiltro = 0;
      break;
    }
    arvoreFiltrada.raiz =
        inserirNoArvore(arvoreFiltrada.raiz, aux->dados, valorFiltro);
    arvoreFiltrada.qtde++;
    aux = aux->proximo;
  }

  printf("Registros ordenados:\n");
  mostrarEmOrdem(arvoreFiltrada.raiz);
  liberar_arvore(arvoreFiltrada.raiz);
}

// --------- Funções de leitura/escrita no arquivo --------------
void salvarEmArquivo(Lista *lista) {
  FILE *arquivo = fopen("pacientes.txt", "w");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  Elista *aux = lista->inicio;
  while (aux) {
    fprintf(arquivo, "%s\n%d\n%s\n%d %d %d\n", aux->dados.nome,
            aux->dados.idade, aux->dados.rg, aux->dados.entrada.dia,
            aux->dados.entrada.mes, aux->dados.entrada.ano);
    aux = aux->proximo;
  }

  fclose(arquivo);
  printf("Dados salvos com sucesso!\n");
}

void lerDoArquivo(Lista *lista) {
  FILE *arquivo = fopen("pacientes.txt", "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo para leitura.\n");
    return;
  }

  Registro dados;
  while (fscanf(arquivo, " %[^\n]s", dados.nome) != EOF) {
    fscanf(arquivo, "%d", &dados.idade);
    fscanf(arquivo, " %[^\n]s", dados.rg);
    fscanf(arquivo, "%d %d %d", &dados.entrada.dia, &dados.entrada.mes,
           &dados.entrada.ano);

    Elista *novo = (Elista *)malloc(sizeof(Elista));
    if (!novo) {
      printf("Erro de alocação.\n");
      fclose(arquivo);
      return;
    }

    novo->dados = dados;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->qtde++;
  }

  fclose(arquivo);
  printf("Dados carregados com sucesso!\n");
}

int main() {
  Lista lista;
  Fila fila;
  Stack stack;

  inicializarLista(&lista);
  inicializarFila(&fila);
  inicializarStack(&stack);

  int opcao;

  do {
    printf("\n=============================\n");
    printf("     Atendimento Medico        \n");
    printf("=============================\n");
    printf("1. Cadastrar novo paciente\n");
    printf("2. Consultar paciente cadastrado\n");
    printf("3. Mostrar lista completa\n");
    printf("4. Mostrar lista filtrada\n");
    printf("5. Atualizar dados de paciente\n");
    printf("6. Remover paciente\n");
    printf("7. Salvar dados em arquivo\n");
    printf("8. Carregar dados de arquivo\n");
    printf("9. Atendimento\n");
    printf("10. Sobre\n");
    printf("0. Sair\n");
    printf("Escolha uma option: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      cadastrarPaciente(&lista);
      break;
    case 2:
      consultarPaciente(&lista);
      break;
    case 3:
      mostrarListaCompleta(&lista);
      break;
    case 4:
      mostrarListaFiltrada(&lista);
      break;
    case 5:
      atualizarPaciente(&lista);
      break;
    case 6:
      removerPaciente(&lista);
      break;
    case 7:
      salvarEmArquivo(&lista);
      break;
    case 8:
      lerDoArquivo(&lista);
      break;
    case 9:
      menuAtendimento(&fila, &lista, &stack);
      break;
    case 10:
      Sobre();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);

  return 0;
}
