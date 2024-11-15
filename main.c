#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Paulo Hudson 22.222.013-9
//Danillo

//Estrutura....
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
//-----------------------------------------

//Funções----------------------------------

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->qtde = 0;
}

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
    scanf("%d %d %d", &novo->dados.entrada.dia, &novo->dados.entrada.mes, &novo->dados.entrada.ano);

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
               aux->dados.entrada.dia, aux->dados.entrada.mes, aux->dados.entrada.ano);
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
            if (anterior == NULL) {  // remover o primeiro elemento
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
    printf("paciente não encontrado.\n");
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
            scanf("%d %d %d", &aux->dados.entrada.dia, &aux->dados.entrada.mes, &aux->dados.entrada.ano);

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
            printf("Nome: %s | Idade: %d | RG: %s | Data de Entrada: %02d/%02d/%04d\n",
                   aux->dados.nome, aux->dados.idade, aux->dados.rg,
                   aux->dados.entrada.dia, aux->dados.entrada.mes, aux->dados.entrada.ano);
            return;
        }
        aux = aux->proximo;
    }
    printf("Paciente não encontrado.\n");
}

void salvarEmArquivo(Lista *lista) {
    FILE *arquivo = fopen("pacientes.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir.\n");
        return;
    }

    Elista *aux = lista->inicio;
    while (aux) {
        fprintf(arquivo, "%s\n%d\n%s\n%d %d %d\n",
                aux->dados.nome,
                aux->dados.idade,
                aux->dados.rg,
                aux->dados.entrada.dia,
                aux->dados.entrada.mes,
                aux->dados.entrada.ano);
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
        fscanf(arquivo, "%d %d %d", &dados.entrada.dia, &dados.entrada.mes, &dados.entrada.ano);

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
    inicializarLista(&lista);
    int opcao;

    do {
        printf("\n--- Atendimento Medico ---\n");
        printf("1. Cadastrar novo paciente\n");
        printf("2. Consultar paciente cadastrado\n");
        printf("3. Mostrar lista completa\n");
        printf("4. Atualizar dados de paciente\n");
        printf("5. Remover paciente\n");
        printf("6. Salvar dados em arquivo\n");
        printf("7. Carregar dados de arquivo\n");
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
                atualizarPaciente(&lista);
            break;
            case 5:
                removerPaciente(&lista);
            break;
            case 6:
                salvarEmArquivo(&lista);
            break;
            case 7:
                lerDoArquivo(&lista);
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

