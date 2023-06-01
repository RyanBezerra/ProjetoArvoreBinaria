#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int rgm;
    string nome;
    Node* left;
    Node* right;
};

Node* criarNo(int rgm, const string& nome) {
    Node* novoNo = new Node;
    novoNo->rgm = rgm;
    novoNo->nome = nome;
    novoNo->left = nullptr;
    novoNo->right = nullptr;
    return novoNo;
}

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

Node* pesquisarNo(Node* raiz, int rgm) {
    if (raiz == nullptr || raiz->rgm == rgm) {
        return raiz;
    }
    if (rgm < raiz->rgm) {
        return pesquisarNo(raiz->left, rgm);
    }
    return pesquisarNo(raiz->right, rgm);
}

Node* encontrarMinimo(Node* raiz) {
    Node* atual = raiz;
    while (atual->left != nullptr) {
        atual = atual->left;
    }
    return atual;
}

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

void liberarArvore(Node* raiz) {
    if (raiz != nullptr) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        delete raiz;
    }
}

void imprimirPreOrdem(Node* raiz) {
    if (raiz != nullptr) {
        cout << "RGM: " << raiz->rgm << ", Nome: " << raiz->nome << endl;
        imprimirPreOrdem(raiz->left);
        imprimirPreOrdem(raiz->right);
    }
}

void imprimirEmOrdem(Node* raiz) {
    if (raiz != nullptr) {
        imprimirEmOrdem(raiz->left);
        cout << "RGM: " << raiz->rgm << ", Nome: " << raiz->nome << endl;
        imprimirEmOrdem(raiz->right);
    }
}

void imprimirPosOrdem(Node* raiz) {
    if (raiz != nullptr) {
        imprimirPosOrdem(raiz->left);
        imprimirPosOrdem(raiz->right);
        cout << "RGM: " << raiz->rgm << ", Nome: " << raiz->nome << endl;
    }
}

void exibirArvoreGraficamente(Node* raiz, int espaco = 0, int incremento = 4) {
    if (raiz == nullptr) {
        return;
    }
    espaco += incremento;
    exibirArvoreGraficamente(raiz->right, espaco);

    cout << endl;
    for (int i = incremento; i < espaco; i++) {
        cout << " ";
    }
    cout << raiz->rgm << "-" << raiz->nome << "\n";

    exibirArvoreGraficamente(raiz->left, espaco);
}

int main() {
    Node* raiz = nullptr;
    int opcao;
    int rgm;
    string nome;

    ifstream arquivoEntrada("alunos.txt");
    if (!arquivoEntrada) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    while (arquivoEntrada >> rgm) {
        arquivoEntrada.ignore();
        getline(arquivoEntrada, nome);
        raiz = inserirNo(raiz, rgm, nome);
    }

    arquivoEntrada.close();

    do {
        cout << "\nALUNO: NOME COMPLETO DO ALUNO" << endl;
        cout << "DISCIPLINA: ESTRUTURA DE DADOS I" << endl;
        cout << "PROFESSOR: WALACE BONFIM" << endl;
        cout << "\nEDITOR DE ARVORE" << endl;
        cout << "1 - INSERIR" << endl;
        cout << "2 - REMOVER UM NO" << endl;
        cout << "3 - PESQUISAR" << endl;
        cout << "4 - ESVAZIAR A ARVORE" << endl;
        cout << "5 - EXIBIR A ARVORE" << endl;
        cout << "0 - SAIR" << endl;
        cout << "\nDIGITE SUA OPCAO: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                cout << "Digite o RGM para inserir: ";
                cin >> rgm;
                cout << "Digite o nome para inserir: ";
                cin.ignore();
                getline(cin, nome);
                raiz = inserirNo(raiz, rgm, nome);
                cout << "No inserido com sucesso." << endl;
                break;
            }
            case 2: {
                cout << "Digite o RGM para remover: ";
                cin >> rgm;
                raiz = removerNo(raiz, rgm);
                cout << "No removido com sucesso." << endl;
                break;
            }
            case 3: {
                cout << "Digite o RGM para pesquisar: ";
                cin >> rgm;
                Node* encontrado = pesquisarNo(raiz, rgm);
                if (encontrado != nullptr) {
                    cout << "No encontrado: RGM: " << encontrado->rgm << ", Nome: " << encontrado->nome << endl;
                } else {
                    cout << "No nao encontrado." << endl;
                }
                break;
            }
            case 4: {
                liberarArvore(raiz);
                raiz = nullptr;
                cout << "Arvore esvaziada." << endl;
                break;
            }
            case 5: {
                cout << "Arvore:" << endl;
                exibirArvoreGraficamente(raiz);
                break;
            }
            case 0: {
                liberarArvore(raiz);
                cout << "Saindo..." << endl;
                break;
            }
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}

