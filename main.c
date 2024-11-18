#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Paulo Hudson 22.222.013-9
// Danillo

// Estrutura....
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

typedef struct Vertice {
  int dadosPesq;
  struct Vertice *esq;
  struct Vertice *dir;
  struct Vertice *pai;
} Vertice;

typedef struct Arvore {
  Vertice *raiz;
  int qtde;
} Arvore;

Vertice *cria_vertice(int valor);
Vertice *inserirNoArvore(Vertice *raiz, Registro dados);
void mostrarListaFiltrada(Lista *lista, Arvore *arvore);

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
        printf("Erro ao alocar memória.\n");
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
  printf("Paciente não encontrado no cadastro.\n");
}

void desenfileirarPaciente(Fila *fila) {
  if (fila->head == NULL) {
    printf("A fila esta vazia.\n");
    return;
  }

  Efila *remover = fila->head;
  fila->head = fila->head->proximo;
  if (fila->head == NULL) {
    fila->tail = NULL;
  }
  printf("Paciente '%s' desenfileirado.\n", remover->dados.nome);
  free(remover);
  fila->qtde--;
}

void mostrarFila(Fila *fila) {
  if (fila->head == NULL) {
    printf("A fila esta vazia.\n");
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

void menuAtendimento(Fila *fila, Lista *lista) {
  int opcao;
  do {
    printf("\n--- Menu de Atendimento ---\n");
    printf("1. Enfileirar paciente\n");
    printf("2. Desenfileirar paciente\n");
    printf("3. Mostrar fila\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma option: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      enfileirarPaciente(fila, lista);
      break;
    case 2:
      desenfileirarPaciente(fila);
      break;
    case 3:
      mostrarFila(fila);
      break;
    case 0:
      printf("voltar a menu principal...\n");
      break;
    default:
      printf("Option invalida, try again.\n");
    }
  } while (opcao != 0);
}

void Sobre() {
  printf("\n============================\n");
  printf("         Sobre Nos         \n");
  printf("============================\n");
  printf("1. Desenvolvedores: Paulo e Danillo\n");
  printf("2. Curso: Ciencia da Computacao - 4 Ciclo\n");
  printf("3. Disciplina: Estrutura de Dados\n");
  printf("4. Data: 18/11/2024\n");
  printf("============================\n");
}

//-------
void cadastrarPaciente(Lista *lista) {
  Elista *novo = (Elista *)malloc(sizeof(Elista));
  if (!novo) {
    printf("Erro alocar.\n");
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
  Elista *aux = lista->inicio;
  printf("Lista de Pacientes:\n");
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
  printf("Digite o nome do paciente A remover: ");
  scanf(" %[^\n]s", nome);

  Elista *aux = lista->inicio;
  Elista *anterior = NULL;

  while (aux) {
    if (strcmp(aux->dados.nome, nome) == 0) {
      if (anterior == NULL) { // remover o primeiro elemento
        lista->inicio = aux->proximo;
      } else {
        anterior->proximo = aux->proximo;
      }
      free(aux);
      lista->qtde--;
      printf("paciente removido com sucesso!\n");
      return;
    }
    anterior = aux;
    aux = aux->proximo;
  }
  printf("paciente nao encontrado.\n");
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
  printf("Paciente nao encontrado.\n");
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
  printf("Paciente não encontrado.\n");
}

// Funcoes para pesquisa e mostra de dados

void mostrarEmOrdem(Vertice *raiz) {
  if (raiz != NULL) {
    mostrarEmOrdem(raiz->esq);
    printf("%d ", raiz->dadosPesq);
    mostrarEmOrdem(raiz->dir);
  }
}

void mostrarRegistrosOrdenados(Arvore *arvore) {
  if (arvore->raiz == NULL) {
    printf("A árvore está vazia.\n");
    return;
  }
  printf("Registros ordenados:\n");
  mostrarEmOrdem(arvore->raiz);
}

Vertice *cria_vertice(int valor) {
  Vertice *novo = malloc(sizeof(Vertice));
  if (!novo) {
    printf("Erro ao alocar memória para o vértice.\n");
    return NULL;
  }
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = NULL;
  novo->dadosPesq = valor;
  return novo;
}

Arvore *cria_arvore() {
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;
  return arvore;
}

int calcularFiltro(Registro dados) {
  int opcao;
  int filtro;

  do {
    printf("\n--- Escolha o filtro de pesquisa ---\n");
    printf("1. Filtrar por ano de registro\n");
    printf("2. Filtrar por mês de registro\n");
    printf("3. Filtrar por dia de registro\n");
    printf("4. Filtrar por idade do paciente\n");
    printf("0. Sair\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      return dados.entrada.ano;
    case 2:
      return dados.entrada.mes;
    case 3:
      return dados.entrada.dia;
    case 4:
      return dados.idade;
    case 0:
      printf("Saindo...\n");
      return -1;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (1);
}

Vertice *inserirNoArvore(Vertice *raiz, Registro dados) {
  int filtro = calcularFiltro(dados);

  if (filtro == -1) {
    printf("Inserção cancelada pelo usuário.\n");
    return raiz;
  }

  if (raiz == NULL) {
    Vertice *novo = cria_vertice(filtro);
    if (!novo) {
      printf("Erro ao alocar memória.\n");
      return NULL;
    }
    return novo;
  }

  if (filtro < raiz->dadosPesq) {
    raiz->esq = inserirNoArvore(raiz->esq, dados);
  } else {
    raiz->dir = inserirNoArvore(raiz->dir, dados);
  }

  return raiz;
}

void liberar_arvore(Vertice *vertice) {
  if (vertice != NULL) {
    liberar_arvore(vertice->esq);
    liberar_arvore(vertice->dir);
    free(vertice);
  }
}

void mostrarListaFiltrada(Lista *lista, Arvore *arvore) {
  Elista *aux = lista->inicio;
  Vertice *arvoreFiltrada = NULL;
  while (aux) {
    arvoreFiltrada = inserirNoArvore(arvoreFiltrada, aux->dados);
    aux = aux->proximo;
  }
  mostrarRegistrosOrdenados(arvore);
}

// --------- fincoes de leitura/escrita no arquivo --------------
void salvarEmArquivo(Lista *lista) {
  FILE *arquivo = fopen("pacientes.txt", "w");
  if (!arquivo) {
    printf("Erro ao abrir.\n");
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
  printf("Dados salvos !\n");
}

void lerDoArquivo(Lista *lista) {
  FILE *arquivo = fopen("pacientes.txt", "r");
  if (!arquivo) {
    printf("Erro ao abrir.\n");
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
  printf("Dados carregados!\n");
}

int main() {
  Lista lista;
  Fila fila;
  inicializarLista(&lista);
  inicializarFila(&fila);
  int opcao;

  Arvore arvore;
  arvore.raiz = NULL;
  arvore.qtde = 0;

  do {
    printf("\n--- Atendimento Medico ---\n");
    printf("1. Cadastrar novo paciente\n");
    printf("2. Consultar paciente cadastrado\n");
    printf("3. Mostrar lista completa\n");
    printf("4. Atualizar dados de paciente\n");
    printf("5. Remover paciente\n");
    printf("6. Salvar dados em arquivo\n");
    printf("7. Carregar dados de arquivo\n");
    printf("8. Atendimento\n");
    printf("9. Sobre\n");
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
      mostrarListaFiltrada(&lista, &arvore);
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
      menuAtendimento(&fila, &lista);
      break;
    case 10:
      Sobre();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida. Try again.\n");
    }
  } while (opcao != 0);

  return 0;
}
