#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct elementos{
	int rgm;
	char nome[100];
}t_elemento;

typedef struct no{
	struct no * esquerda;
	t_elemento dado;
	struct no * direita;
}t_no;

typedef t_no * t_arvore;

void exibirPreOrdem(t_arvore tree)
{
	if(tree != NULL){
		printf("%d ", tree->dado.rgm);
		exibirPreOrdem(tree->esquerda);
		exibirPreOrdem(tree->direita);
	}
}

void exibirInOrdem(t_arvore tree)
{
	if(tree != NULL){
		exibirInOrdem(tree->esquerda);
		printf("%d ", tree->dado.rgm);
		exibirInOrdem(tree->direita);
	}
}

void exibirPosOrdem(t_arvore tree)
{
	if(tree != NULL){
		exibirPosOrdem(tree->esquerda);
		exibirPosOrdem(tree->direita);
		printf("%d ", tree->dado.rgm);
	}
}

t_no * criar()
{
	t_no * no = (t_no*) malloc(sizeof(t_no));

	if(no)
		no->esquerda = no->direita = NULL;
		no->dado.rgm = -1;

	return no;
}

t_no * pesquisar(t_arvore tree, t_elemento dado)
{	
	if (tree == NULL){	
    	printf ("Nao esta presente na arvore");
        return NULL;
	}
    if (tree->dado.rgm == dado.rgm){    	
    	printf("\nRGM: %d \nNome: %s\n", tree->dado.rgm, tree->dado.nome);
        return tree;
	}
    if (dado.rgm < tree->dado.rgm)
        return pesquisar(tree->esquerda, dado);
    else
        return pesquisar(tree->direita, dado);
}

t_no * buscaSetPai(t_arvore tree, t_elemento dado, t_no ** pai)
{
	if (tree == NULL){	
    	*pai = NULL;
        return NULL;
	}
    if (tree->dado.rgm == dado.rgm){    	
        return tree;
	}
    if (dado.rgm < tree->dado.rgm){
    	*pai = tree;
        return buscaSetPai(tree->esquerda, dado, pai);
    }else{
    	*pai = tree;
        return buscaSetPai(tree->direita, dado, pai);
	}
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 

void exibirGraficamente(t_arvore tree, int col, int lin, int desloc)
{
	if(tree == NULL)
		return;
	gotoxy(col, lin);
	printf("%d", tree->dado.rgm);
	if(tree->esquerda != NULL)
		exibirGraficamente(tree->esquerda, col-desloc, lin+2, desloc/2+1);
	if(tree->direita!= NULL)
		exibirGraficamente(tree->direita, col+desloc, lin+2, desloc/2+1);
	
}

int inserir (t_arvore * tree, t_elemento dado)
{
	int ok;
	
	if(*tree == NULL)
	{
		*tree = criar();
		if(*tree == NULL)
			return 0;
		(*tree)->dado = dado;
		return 1;
	}
	
	if(dado.rgm > (*tree)->dado.rgm)
		ok = inserir(&((*tree)->direita), dado);
	else
		if(dado.rgm < (*tree)->dado.rgm)
			ok = inserir ((&(*tree)->esquerda), dado);
		else
			ok = 0;
	return ok;
}

int remover(t_arvore * tree, t_elemento dado)
{
	t_no * no, *pai, *substituir, * paiSucessor, * sucessor;
	no = * tree;
	pai = NULL;
	
	no = buscaSetPai(*tree, dado, &pai);
	
	if(no == NULL){
		printf("Nao existe");
		return 0;
	}
		
	if(no->esquerda == NULL)
		substituir = no->direita;
	else{
		if(no->direita == NULL)
			substituir =  no->esquerda;
		else{
			paiSucessor = no;
			substituir = no->direita;
			sucessor = substituir->esquerda;
			while (sucessor != NULL){
				paiSucessor = substituir;
				substituir = sucessor;
				sucessor = substituir->esquerda;
			}
			
			if(paiSucessor != no)
			{
				paiSucessor->esquerda = substituir->direita;
				substituir->direita = no->direita;
			}
			
			substituir->esquerda = no->esquerda;
		}
	}
	
	if(pai == NULL)
		*tree = substituir;
	else
		if(no == pai->esquerda)
			pai->esquerda = substituir;
		else
			pai->direita = substituir;
	printf("\nRGM: %d \nNome: %s foi removido\n", no->dado.rgm, no->dado.nome);
	free(no);
	return 1;
}

void esvaziarArvore(t_arvore * tree)
{
    if(*tree != NULL)
    {
    	esvaziarArvore(&(*tree)->esquerda);
    	esvaziarArvore(&(*tree)->direita);
    	free(*tree);
    	*tree = NULL;
	}
}

void Menu(t_arvore arvore)
{	
	t_elemento dado;	
	int opcao, sim;
		
	system("cls");
	printf("ALUNO: NOME COMPLETO DO ALUNO");
	printf("\nDISCIPLINA: ESTRUTURA DE DADOS I");
	printf("\nPROFESSOR: WALECE BONFIM");
	printf("\n\n\tEDITOR DE ARVORE");
	printf("\n\n1 - INSERIR\n2 - REMOVER UM NO\n3 - PESQUISAR\n4 - ESVAZIAR A ARVORE\n5 - EXIBIR A ARVORE\n0 - SAIR\n");
	printf("\n\tDIGITE SUA OPCAO: \n");
	scanf("%d", &opcao);
	switch(opcao)
	{
		case 1:
			system("cls");
			printf("\nDigite seu RGM: ");
			scanf("%d", &dado.rgm);
			fflush(stdin);
			printf("\nDigite seu nome: ");
			gets(dado.nome);
			inserir(&arvore, dado);
			printf("\n1 - Voltar menu\n");
			scanf("%d", &sim);
			if(sim == 1)
				Menu(arvore);
		case 2:
			system("cls");
			printf("\nRemove dado: ");
			scanf("%d", &dado);
			remover(&arvore, dado);
			printf("\n1 - Voltar menu\n");
			scanf("%d", &sim);
			if(sim == 1)
				Menu(arvore);
		case 3:	
			system("cls");
			printf("\nPesquisar RGM: ");
			scanf("%d", &dado);
			pesquisar(arvore, dado);
			printf("\n1 - Voltar menu\n");
			scanf("%d", &sim);
			if(sim == 1)
				Menu(arvore);
		case 4:
			system("cls");
			esvaziarArvore(&arvore);
			printf("Arvore esvaziada");
			printf("\n1 - Voltar menu\n");
			scanf("%d", &sim);
			if(sim == 1)
				Menu(arvore);
		case 5:
			system("cls");
			
			printf("\nExibir em Pre ordem: ");
			exibirPreOrdem(arvore);
			printf("\nExibir em In ordem: ");
			exibirInOrdem(arvore);
			printf("\nExibir em Pos ordem: ");
			exibirPosOrdem(arvore);
			exibirGraficamente(arvore, 30, 10, 10);
			printf("\n1 - Voltar menu\n");
			scanf("%d", &sim);
			if(sim == 1)
				Menu(arvore);
			case 0 :
				system("cls");
				break;
				
	}
}

int main(){
	
	t_arvore arvore = NULL;
	t_elemento dado;
	
	ifstream arquivoEntrada("alunos.txt");
	
	 if (!arquivoEntrada) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }
	
	int rgm;
	string nome;
	
    while (arquivoEntrada >> rgm) {
        arquivoEntrada.ignore();
        getline(arquivoEntrada, nome);
        dado.rgm = rgm;
        
        for(int i = 0; i < nome.length()+1; i++)
    		dado.nome[i] = nome[i];
        
        inserir(&arvore, dado);
    }
	
    arquivoEntrada.close();
	
	Menu(arvore);
	
}
