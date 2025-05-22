#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura do item armazenado, representando um carro
typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;  // 1 para prioridade, 0 para não prioritário
} TipoItem;

// Estrutura da célula das filas
typedef struct Celula {
    TipoItem item;
    struct Celula* prox;
} Celula;

// Estrutura da fila
typedef struct {
    Celula* frente;
    Celula* tras;
} TipoFila;

// Função para inicializar uma fila
void inicializaFila(TipoFila* fila) {
    fila->frente = (Celula*)malloc(sizeof(Celula));
    fila->tras = fila->frente;
    fila->frente->prox = NULL;
}

// Função para verificar se a fila está vazia
int filaVazia(TipoFila* fila) {
    return (fila->frente == fila->tras);
}

// Função para inserir um carro na fila
void enfileira(TipoItem x, TipoFila* fila) {
    fila->tras->prox = (Celula*)malloc(sizeof(Celula));
    fila->tras = fila->tras->prox;
    fila->tras->item = x;
    fila->tras->prox = NULL;
}

// Função para desenfileirar um carro
void desenfileira(TipoFila* fila, TipoItem* x) {
    if (filaVazia(fila)) {
        printf("Erro: fila vazia\n");
        return;
    }
    Celula* aux = fila->frente;
    fila->frente = fila->frente->prox;
    *x = fila->frente->item;
    free(aux);
}

// Função para verificar se existe carro prioritário na fila de espera
int temPrioridade(TipoFila* fila) {
    Celula* aux = fila->frente->prox;
    while (aux != NULL) {
        if (aux->item.prioridade == 1) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

// Função para mover um carro prioritário da fila de espera para o estacionamento
void movePrioritario(TipoFila* filaEspera, TipoFila* estacionamento) {
    Celula* aux = filaEspera->frente->prox;
    Celula* anterior = filaEspera->frente;

    // Busca o primeiro carro prioritário
    while (aux != NULL) {
        if (aux->item.prioridade == 1) {
            if (anterior == filaEspera->frente) {
                desenfileira(filaEspera, &aux->item);
                enfileira(aux->item, estacionamento);
                return;
            } else {
                anterior->prox = aux->prox;
                if (aux == filaEspera->tras) {
                    filaEspera->tras = anterior;
                }
                enfileira(aux->item, estacionamento);
                free(aux);
            }
            return;
        }
        anterior = aux;
        aux = aux->prox;
    }
}

// Função para remover um carro do estacionamento
void removeCarroEstacionamento(TipoFila* estacionamento, TipoFila* ruaAuxiliar, char* placa) {
    TipoItem carro;
    int encontrou = 0;

    // Remover carros até encontrar o desejado
    while (!filaVazia(estacionamento)) {
        desenfileira(estacionamento, &carro);
        if (strcmp(carro.placa, placa) == 0) {
            encontrou = 1;
            break;
        } else {
            enfileira(carro, ruaAuxiliar);
        }
    }

    // Retornar carros ao estacionamento
    while (!filaVazia(ruaAuxiliar)) {
        desenfileira(ruaAuxiliar, &carro);
        carro.deslocamento++;
        enfileira(carro, estacionamento);
    }

    if (encontrou) {
        printf("Carro %s removido com sucesso\n", placa);
    } else {
        printf("Carro %s não encontrado.\n", placa);
    }
}

// função para exibir os estacionamentos
void exibeEstacionamento(TipoFila* fila, const char* nomeFila) {
    Celula* aux = fila->frente->prox;
    printf("\n%s:\n", nomeFila);
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
    } else {
        while (aux != NULL) {
            printf("Placa: %s, Deslocamentos: %d, Prioridade: %s\n",
                   aux->item.placa,
                   aux->item.deslocamento,
                   aux->item.prioridade ? "Sim" : "Não");
            aux = aux->prox;
        }
    }
}

// função para verificar a quantidade de carros no estacionamento
int tamanhoEstacionamento(TipoFila fila) {
    Celula* aux = fila.frente; 
    int cont = 0;
    
    while (aux->prox != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

// Função principal para simulação
int main() {
    setlocale(LC_ALL, "Portuguese");
    TipoFila estacionamento, filaEspera, ruaAuxiliar;
    inicializaFila(&estacionamento);
    inicializaFila(&filaEspera);
    inicializaFila(&ruaAuxiliar);

    int opcao;
    char placa[10];
    int prioridade;
    int negado;
	
    while (1) {
        printf("\n\tEscolha uma opção\n");
        printf("1. Chegar um carro para estacionar\n");
        printf("2. Retirar um carro do estacionamento\n");
        printf("3. Exibir estado das filas\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a placa do carro: ");
                scanf("%s", placa);
				negado =0;
				do{
                	if(negado>0){
                		system("cls");
                		printf("Essa opção não existe. Digite uma existente.\n\n");
					}	
					printf("Prioridade (1 - sim, 0 - não): ");
                	scanf("%d", &prioridade);
                	negado++;
                }while (prioridade<0 || prioridade>1);

                TipoItem novoCarro;
                strcpy(novoCarro.placa, placa);
                novoCarro.deslocamento = 0;
                novoCarro.prioridade = prioridade;

                if (tamanhoEstacionamento(estacionamento) < 5) {
                    enfileira(novoCarro, &estacionamento);
                    printf("Carro %s estacionado.\n", placa);
                } else {
                    enfileira(novoCarro, &filaEspera);
                    printf("Estacionamento cheio. Carro %s está na fila de espera.\n", placa);
                }
                break;

            case 2:
                printf("Digite a placa do carro a ser removido: ");
                scanf("%s", placa);
                removeCarroEstacionamento(&estacionamento, &ruaAuxiliar, placa);

                if (temPrioridade(&filaEspera)) {
                    movePrioritario(&filaEspera, &estacionamento);
                } else if (!filaVazia(&filaEspera)) {
                    TipoItem carroSaindo;
                    desenfileira(&filaEspera, &carroSaindo);
                    enfileira(carroSaindo, &estacionamento);
                }
                break;

            case 3:
                exibeEstacionamento(&estacionamento, "Estacionamento");
                exibeEstacionamento(&filaEspera, "Fila de Espera");
                exibeEstacionamento(&ruaAuxiliar, "Rua Auxiliar");
                break;
                
            case 4:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        
        printf("Pressione Enter para continuar...");
        getchar();
        getchar();
        system("cls"); 
    }

    return 0;
}

