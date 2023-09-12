/*
Listas encadeadas são estruturas de dados que permitem armazenar uma coleção
 de elementos de um mesmo tipo.

Neste arquivo, temos a implementação de uma lista encadeada simples de inteiros.
*/

#include "lista.h"

// struct que armazena um úmero inteiro e o id da próxima celular
struct lista
{
	int info; // armazena um inteiro
	struct lista *prox; // armazena o id do próximo valor
};

// Função que cria uma lista e retorna atribuindo NULL a ela
Lista *lst_cria(void)
{
	return NULL; // retorna NULL para a lista 
}

// Função para inserir um novo item a lista
Lista *lst_insere(Lista *l, int v)
{
	Lista *novo = (Lista *)malloc(sizeof(Lista)); // Aloca mémoria para o novo elemento
	if (novo == NULL) // verifica se a mémoria do novo elemento foi alocada com sucesso, caso não tenha sido, será parado a execução  
	{
		printf("[ERRO] memoria insuficiente!"); // imprime mensagem de erro
		exit(1); // para a execução
	}
	novo->info = v; // atribui o valor inteiro
	novo->prox = l; // atribui o id do próximo elemento 
	return novo; // retorna o novo elemento

	/* Ou para alterar diretamente

	void lst_insere(Lista** t, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = *t;
	*t = novo; */
}

// Função que verifica se a lista está vazia
int lst_vazia(Lista *l)
{
	return (l == NULL); // retorna TRUE(1) caso a lista esteja vazia, e FALSE(0) casa não esteja
}

// Função para imprimir a lista 
void lst_imprime(Lista *l)
{
	Lista *p; // criando um novo ponteiro do tipo lista
	for (p = l; p != NULL; p = p->prox) // laço for para percorrer toda a lista até encotrar NULL 
	{
		printf("\tInfo = %d \n", p->info); // imprime info na tela
	}
}

// Função para buscar um elemento específico na lista 
Lista *lst_busca(int elemento, Lista *l)
{
	Lista *p; // criando um novo ponteiro do tipo lista
	for (p = l; p != NULL; p = p->prox) // laço for para percorrer toda a lista até encotrar NULL 
	{
		if (p->info == elemento) // verifica se achou o elemento específico 
			return p; // retorna o endereço do elemento, caso ele esteja na lista 
	}

	return NULL; // caso o elemento nao esteja na lista, retornará NULL
}

// Função para retirar um elemento da lista 
Lista *lst_retira(Lista *l, int v)
{
	Lista *ant = NULL; /* ponteiro para elemento anterior */  // cria um ponteiro do tipo lista que apontará para o endereço anterior e atribui NULL a ele
	Lista *p = l;	   /* ponteiro para percorrer a lista*/  // cria um ponteiro do tipo lista que aponta para a lista
	/* procura elemento na lista, guardando anterior */
	while (p->info != v)
	{
		if (p == NULL)
			return l; /* n�o achou: retorna lista original */
		ant = p;
		p = p->prox;
		/* verifica se achou elemento */
	}
	/* retira elemento */
	if (ant == NULL)
		/* retira elemento do inicio */
		l = p->prox;
	else
		/* retira elemento do meio da lista */
		ant->prox = p->prox;
	free(p);
	return l;
}

// Função para liberar o espaço na mémoria que esta armazenando a lista 
void lst_libera(Lista *l)
{
	Lista *p = l; // declarando um ponteiro do tipo Lista que apontará para a lista original
	Lista *t;  // declarando um ponteiro do tipo Lista
	while (p != NULL) // laço que percorrerá toda a lista
	{
		t = p->prox; // o ponteiro t apontará para o prócimo elemento
		free(p); // o elemento que p está apontando é liberado 
		p = t; // p recebe o endereço do próximo elemento 
	}
}

// Função que insere um elemento ordenadamente 
Lista *lst_insere_ordenada(Lista *l, int v)
{
	Lista *novo; // declarando um ponteiro do tipo Lista
	Lista *ant = NULL; // cria um ponteiro do tipo Lista que apontará para o endereço anterior e atribui NULL a ele
	Lista *p = l; // declarando um ponteiro do tipo Lista que apontará para a lista original
	while (p != NULL && p->info < v) // laço que parará no final da lista ou quando o valor armazenado em info for maior que v 
	{
		ant = p; // o ponteiro anterior recebe o endereço de p
		p = p->prox; // o ponteiro p recebe o endereço do próximo valor
	}
	novo = (Lista *)malloc(sizeof(Lista)); // alocando mémoria para o novo elemento
	novo->info = v; // adiciona o valor para o info do novo elemento 
	if (ant == NULL) // verifica se ant é NULL
	{
		novo->prox = l; // caso seja NULL: o prox do novo elemento recerá o endereço da lista original  
		l = novo; // a lista recebe o endereço de novo 
	}
	else // caso ant não seja NULL
	{    
		novo->prox = ant->prox; // prox do novo elemento recebe o endereço de prox do ant
		ant->prox = novo; // prox de ant recebe o enderço de novo 
	}
	return l; // retorna o endereço do valor inicial da lista modificada 
}

// Função que ler um arquivo e adiciona os valor em uma lista
Lista *lst_ler_arquivo(char *nome_arquivo)
{
	FILE *arquivo; // cria um ponteiro do tipo FILE
	int valor; // declarando uma variavel do tipo inteiro 
	Lista *l = lst_cria(); // criando a lista 
	arquivo = fopen(nome_arquivo, "r"); // abrindo o arquivo para leitura 
	if (arquivo == NULL) // verifica se o arquivo foi aberto com sucesso
	{
		printf("Erro ao abrir o arquivo!\n"); // meagem de erro caso o arquivo não seja aberto
		exit(1); // para a execução
	}
	while (fscanf(arquivo, "%d", &valor) != EOF) // lê o valor que está no arquivo e verifica se ele é diferente de EOF
	{
		l = lst_insere_ordenada(l, valor); // caso seja diferente: adiciona na lista o valor lido
	}
	fclose(arquivo); // fecha arquivo 
	return l; // retorna o endereço do valor inicial da lista
}
