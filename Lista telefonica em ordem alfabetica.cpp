#include <stdio.h>
#include <string.h>

// Definir a estrutura para um contato na lista telefônica
struct Contato {
    char nome[50];
    char telefone[15];
};

// Função para adicionar um novo contato à lista
void adicionarContato(struct Contato lista[], int *tamanho) {
    if (*tamanho < 100) { // Certifique-se de que a lista não esteja cheia
        struct Contato novoContato;
        
        printf("Digite o nome do contato: ");
        scanf("%s", novoContato.nome);
        
        printf("Digite o telefone do contato: ");
        scanf("%s", novoContato.telefone);
        
        lista[*tamanho] = novoContato; // Adicione o novo contato à lista
        (*tamanho)++;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("A lista está cheia. Não é possível adicionar mais contatos.\n");
    }
}

// Função para exibir a lista de contatos em ordem alfabética
void exibirLista(struct Contato lista[], int tamanho) {
    if (tamanho > 0) {
        printf("Lista Telefonica:\n");
        
        // Ordenar a lista em ordem alfabética (usando Bubble Sort para simplicidade)
        for (int i = 0; i < tamanho - 1; i++) {
            for (int j = 0; j < tamanho - i - 1; j++) {
                if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                    // Trocar os contatos
                    struct Contato temp = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = temp;
                }
            }
        }
        
        // Exibir a lista ordenada
        for (int i = 0; i < tamanho; i++) {
            printf("%s: %s\n", lista[i].nome, lista[i].telefone);
        }
    } else {
        printf("A lista telefonica está vazia.\n");
    }
}

int main() {
	
    struct Contato listaTelefonica[100]; // Crie uma lista de contatos com capacidade para 100 contatos
    int tamanho = 0; // Mantenha o controle do tamanho atual da lista
    
    int escolha;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Adicionar contato\n");
        printf("2. Exibir lista telefonica\n");
        printf("3. Sair\n");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                adicionarContato(listaTelefonica, &tamanho);
                break;
            case 2:
                exibirLista(listaTelefonica, tamanho);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 3);
    
    return 0;
}