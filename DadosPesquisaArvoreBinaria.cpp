#include <iostream>
#include <string>

using namespace std;

// Definição da estrutura do nó da árvore
struct Node {
    int rgm;
    string nome;
    Node* left;
    Node* right;
};

// Função para criar um novo nó
Node* criarNo(int rgm, const string& nome) {
    Node* novoNo = new Node;
    novoNo->rgm = rgm;
    novoNo->nome = nome;
    novoNo->left = nullptr;
    novoNo->right = nullptr;
    return novoNo;
}

// Função para inserir um novo nó na árvore
Node* inserirNo(Node* raiz, int rgm, const string& nome) {
    if (raiz == nullptr) {
        return criarNo(rgm, nome);
    }
    if (rgm < raiz->rgm) {
        raiz->left = inserirNo(raiz->left, rgm, nome);
    } else if (rgm > raiz->rgm) {
        raiz->right = inserirNo(raiz->right, rgm, nome);
    }
    return raiz;
}

// Função para pesquisar um nó na árvore
Node* pesquisarNo(Node* raiz, int rgm) {
    if (raiz == nullptr || raiz->rgm == rgm) {
        return raiz;
    }
    if (rgm < raiz->rgm) {
        return pesquisarNo(raiz->left, rgm);
    }
    return pesquisarNo(raiz->right, rgm);
}

// Função para encontrar o nó com o valor mínimo (utilizada na remoção)
Node* encontrarMinimo(Node* raiz) {
    Node* atual = raiz;
    while (atual->left != nullptr) {
        atual = atual->left;
    }
    return atual;
}

// Função para remover um nó da árvore
Node* removerNo(Node* raiz, int rgm) {
    if (raiz == nullptr) {
        return raiz;
    }
    if (rgm < raiz->rgm) {
        raiz->left = removerNo(raiz->left, rgm);
    } else if (rgm > raiz->rgm) {
        raiz->right = removerNo(raiz->right, rgm);
    } else {
        if (raiz->left == nullptr) {
            Node* temp = raiz->right;
            delete raiz;
            return temp;
        } else if (raiz->right == nullptr) {
            Node* temp = raiz->left;
            delete raiz;
            return temp;
        }
        Node* temp = encontrarMinimo(raiz->right);
        raiz->rgm = temp->rgm;
        raiz->nome = temp->nome;
        raiz->right = removerNo(raiz->right, temp->rgm);
    }
    return raiz;
}

// Função para liberar a memória ocupada pela árvore
void liberarArvore(Node* raiz) {
    if (raiz != nullptr) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        delete raiz;
    }
}

// Função para imprimir a árvore em ordem
void imprimirArvore(Node* raiz) {
    if (raiz != nullptr) {
        imprimirArvore(raiz->left);
        cout << "RGM: " << raiz->rgm << ", Nome: " << raiz->nome << endl;
        imprimirArvore(raiz->right);
    }
}

int main() {
    Node* raiz = nullptr;
    int opcao;
    int rgm;
    string nome;

    do {
        cout << "\n1. Pesquisar " << endl;
        cout << "2. Inserir " << endl;
        cout << "3. Remover " << endl;
        cout << "4. Imprimir arvore" << endl;
        cout << "5. Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                cout << "Digite o RGM para pesquisa: ";
                cin >> rgm;
                Node* resultado = pesquisarNo(raiz, rgm);
                if (resultado != nullptr) {
                    cout << "RGM: " << resultado->rgm << ", Nome: " << resultado->nome << endl;
                } else {
                    cout << "No nao encontrado." << endl;
                }
                break;
            }
            case 2: {
                cout << "Digite o RGM para insercao: ";
                cin >> rgm;
                cout << "Digite o nome para insercao: ";
                cin.ignore();
                getline(cin, nome);
                raiz = inserirNo(raiz, rgm, nome);
                cout << "No inserido com sucesso." << endl;
                break;
            }
            case 3: {
                cout << "Digite o RGM para remocao: ";
                cin >> rgm;
                raiz = removerNo(raiz, rgm);
                cout << "No removido com sucesso." << endl;
                break;
            }
            case 4: {
                imprimirArvore(raiz);
                break;
            }
            case 5:
                liberarArvore(raiz);
                cout << "Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
        }
    } while (opcao != 5);

    return 0;
}