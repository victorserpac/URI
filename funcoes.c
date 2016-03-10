/**
 * Funções de C
 * =====================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>


/** Getch - reads from keypress, doesn't echo
 * ------------------------------------------ */
int getch(void){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

/** Getche - reads from keypress, echoes
 * ------------------------------------------ */
int getche(void){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

/** Substitui as ocorrencias da palavra 1 pela palavra 2 na frase
 * ------------------------------------------ */
void trocarPalavraFrase(char *frase, char *palavra1, char *palavra2){
	char *p, *q;
	int diff;

	diff = strlen(palavra2) - strlen(palavra1);

	p = strstr(frase, palavra1);
	while(p!=NULL){
		q = &frase[strlen(frase)];
		
		/* Move a String */
		while(q!=p){
			*(q+diff) = *q;
			q--;
		}
		for(int i=0; i<strlen(palavra2); ++i){
			*p = palavra2[i];
			p++;
		}

		p = strstr(p, palavra1);
	}
}

/** Deleta as ocorrencias da palavra na frase
 * ------------------------------------------ */
void excluiPalavraFrase(char *frase, char *palavra){
	char *p, *q;

	p = strstr(frase, palavra);
	while(p!=NULL){
		q = p;
		p++;
		while(*q!='\0'){
			*q = *(q+strlen(palavra));
			q++;
		}
		p = strstr(p, palavra);
	}
}

/** Troca todas as ocorrências da palavra pela sua versão em letras maiúsculas na frase
 * ------------------------------------------ */
void uppercasePalavraNaFrase(char *frase, char *palavra){
	char *p;
	p = strstr(frase, palavra);
	while(p!=NULL){
		for(int i=0; i<strlen(palavra); ++i){
			if(*p >= 97 && *p <=122){
				*p = *p-32;
			}
			p++;
		}
		p = strstr(p, palavra);
	}
}

/** Retorna o número de ocorrencias da palavra na frase
 * ------------------------------------------ */
int ocorrenciasPalavraFrase(char *frase, char *palavra){
	char *p;
	int cont=0;

	p = strstr(frase, palavra);
	while(p!=NULL){
		cont++;
		p++;
		p = strstr(p, palavra);
	}

	return cont;
}

/** Ordena o vetor em ordem crescente
 * ------------------------------------------ */
void ordenarVetor(int *vet, int tamanho){
	int cont, aux;
	
	do{
		cont=0;
		for( int i=0; i<tamanho-1; ++i){
			if( vet[i]>vet[i+1] ){
				aux = vet[i];
				vet[i] = vet[i+1];
				vet[i+1] = aux;
				cont++;
			}
		}
	}while(cont!=0);
}

/** Uppercase e Lowercase
 * ------------------------------------------ */
char upperCase(char carac){
	if( carac>=97 && carac<=122 ){
		carac -= 32;
	}
	return carac;
}
char lowerCase(char carac){
	if( carac>=65 && carac<=90 ){
		carac += 32;
	}
	return carac;
}

/** Imprimir vetor
 * ------------------------------------------ */
void imprimeVetor(int *vet, int tam){
	for( int i=0; i<tam; ++i){
		printf("%i ", *vet);
		vet++;
	}
	printf("\n");
}

/** Verifica se número é primo
 * ------------------------------------------ */
int isPrimo(int num){
	int cont=0;
	for(int i=1; i<=num; ++i){
		if( num%i==0 ){
			cont++;
		}
	}
	if( cont==2 ){
		return 1;
	}else{
		return 0;
	}
}

/** Mesma função do gets(), porem dinamicamente. Retorna uma posição de memória
  * Uso: 
 * ------------------------------------------ */
void getsDinamico(char **p){
	char letra;
	
	int i=1;
	do{
		letra = getche();
		if( letra!=10 ){
			if( i==1 )
				*p = (char*)malloc(sizeof(char)*i);
			else
				*p = (char*)realloc(*p, sizeof(char)*i);

			*(*p+i-1) = letra;
			i++;
		}
	}while( letra!=10 );
}

/** Pega todo o conteúdo do nome do arquivo enviado por parametro, retorna uma posição de memória
 * ------------------------------------------ */
void getAllFromFile(char **string, char *arquivo){
	FILE *arq;
	int tamanho;

	arq = fopen(arquivo, "r+");
	if( arq ){
		
		fseek(arq, 0, SEEK_END); /* Aponta para a ultima posição do arquivo */
		tamanho = ftell(arq); /* Retorna a posição atual, que no caso é a ultima */
		fseek(arq, 0, SEEK_SET); /* Aponta novamete para a primeira posição do arquivo */

		*string = (char*)malloc(sizeof(char)*tamanho);
		if( *string ){
			fread(*string, 1, tamanho, arq);
		}

	}else{
		printf("Arquivo não existe\n");
	}
	fclose(arq);
}

/** Escreve arquivo conforme permissão.
 * ------------------------------------------ */
void escreverArquivo(char *arquivo, char *conteudo, char permissao[2]){
	FILE *arq;
	arq = fopen(arquivo, permissao);
	fputs(conteudo, arq);
	fclose(arq);
}

int numDigitos(int num){
	if(num==0)
		return 1;
	int cont=0;
	while(num>0){
		num /=10;
		cont++;
	}
	return cont;
}

char convertIntChar(int num){
	return (char)num + '0';
}
void convertIntToString(char **teste, int num){
	int digitos = numDigitos(num);
	*teste = (char*)malloc(sizeof(char)*digitos);

	if( digitos==1 ){
		**teste = convertIntChar(num);
	}else{
		int i = digitos-1;
		while(num>0){
			*(*teste+i) = (char)(num%10) + '0';
			num /= 10;
			i--;
		}
	}
}
int calcularIdade(int dia, int mes, int ano){
	struct data{
		int dia;
		int mes;
		int ano;
	};
	struct data nascimento, dia_atual;

	nascimento.dia = dia;
	nascimento.mes = mes;
	nascimento.ano = ano;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	dia_atual.dia = tm.tm_mday;
	dia_atual.mes = tm.tm_mon+1;
	dia_atual.ano = tm.tm_year+1900;

	int idade = dia_atual.ano - nascimento.ano;
	if( dia_atual.mes < nascimento.mes ){
		idade--;
	}else if( dia_atual.mes==nascimento.mes && dia_atual.dia<nascimento.dia){
		idade--;
	}
	return idade;
}





/**
 * Implementando Fila - Maneira facil para usar
 * =====================================================================
 * 
*/
typedef struct Fila{
	int capacidade;
	int tamanho;
	int inicio;
	int fim;
	int *elementos;
}Fila;

Fila* criarFila(int maxElementos){
	Fila *F = (Fila*)malloc(sizeof(Fila));	/* Criando a Fila */
	
	/* Iniciando suas propriedades */
	F->elementos = (int *)malloc(sizeof(int)*maxElementos);
	F->tamanho = 0;
	F->capacidade = maxElementos;
	F->inicio = 0;
	F->fim = -1;
	
	/* Retorna o ponteiro */
	return F;
}

void inserirFila(Fila *F, int valor){
	/* Testar se a fila está cheia */
	if(F->tamanho == F->capacidade){
		printf("Capacidade da fila estourou.\n");
	}else{
		F->tamanho++;
		F->fim = F->fim + 1;
		/* Preencher a fila no modo */
		if(F->fim == F->capacidade){
			F->fim = 0;
		}
		/* Inserir valor no fim da fila */ 
		F->elementos[F->fim] = valor;
	}
}

void removerFila(Fila *F){
	/* If Queue size is zero then it is empty. So we cannot pop */
	if(F->tamanho==0){
		printf("Fila está vazia\n");
	}else{
        /* Removing an element is equivalent to incrementing index of front by one */
		F->tamanho--;
		F->inicio++;
		/* As we fill elements in circular fashion */
		if(F->inicio==F->capacidade){
			F->inicio=0;
		}
	}
}

void imprimirFila(Fila *F){
	int i, j, nth=1;

	if(F->tamanho==0){
		printf("Fila está vazia\n");
		exit(0);
	}else{
		if(F->fim >= F->inicio){
			for(i=F->inicio; i<=F->fim; ++i){
				printf("(%i): %i\n", nth, F->elementos[i]);
				nth++;
			}
		}else{
			for(i=F->inicio; i<=F->capacidade-1; i++){
				printf("(%i): %i\n", nth, F->elementos[i]);
				nth++;
			}
			for(i=0; i<=F->fim; i++){
				printf("(%i): %i\n", nth, F->elementos[i]);
				nth++;
			}
		}
	}
	printf("\n");
}



/**
 * Implementando Listas Encadeadas
 * =====================================================================
 * 
*/

typedef struct Lista{
	int val;
	struct Lista* next;
}Lista;

Lista* criarLista(){
	return NULL;
}

int isListaVazia(Lista *L){
	return (L == NULL);
}

Lista* inserirLista(Lista *L, int val){
	Lista *node = (Lista*)malloc(sizeof(Lista));
	node->val = val;
	node->next = L;
	
	return node;
}

void imprimirLista(Lista *L){	
	if ( !isListaVazia(L) ) {
		printf("%i\n", L->val);
		imprimirLista(L->next);
	}
}
void imprimirListaInvertido(Lista *L){	
	if ( !isListaVazia(L) ) {
		imprimirListaInvertido(L->next);
		printf("%i\n", L->val);
	}
}

Lista* buscarLista(Lista *L, int val){
	if (L == NULL)
		return NULL;
	if (L->val == val)
		return L;
	
	return buscarLista(L->next, val);
}

Lista* retirarLista(Lista *L, int val){
	if ( !isListaVazia(L) ){
		if (L->val == val){
			Lista* t = L;
			L = L->next;
			free(t);
		}else{
			L->next = retirarLista(L->next, val);
		}

	}
	return L;
}

void destruitLista(Lista *L){
	if (L != NULL)
		destruitLista(L->next);
	
	free(L);
}


/**
 * Implementando Listas Duplamente Encadeadas
 * =====================================================================
 * 
*/

typedef struct ListaDupla{
	int val;
	struct ListaDupla* prev;
	struct ListaDupla* next;
}ListaDupla;

ListaDupla* criarListaDupla(){
	return NULL;
}

int isListaDuplaVazia(ListaDupla *L){
	return (L == NULL);
}

ListaDupla* inserirListaDupla(ListaDupla *L, int val){
	ListaDupla *node = (ListaDupla*)malloc(sizeof(ListaDupla));
	node->val = val;
	node->next = L;
	node->prev = NULL;

	if ( !isListaDuplaVazia(L) ) {
		L->prev = node;
	}
	
	return node;
}

void imprimirListaDupla(ListaDupla *L){	
	if ( !isListaDuplaVazia(L) ) {
		printf("%i\n", L->val);
		imprimirListaDupla(L->next);
	}
}
void imprimirListaDuplaInvertido(ListaDupla *L){	
	if ( !isListaDuplaVazia(L) ) {
		imprimirListaDuplaInvertido(L->next);
		printf("%i\n", L->val);
	}
}

ListaDupla* buscarListaDupla(ListaDupla *L, int val){
	if (L == NULL)
		return NULL;
	if (L->val == val)
		return L;
	
	return buscarListaDupla(L->next, val);
}

ListaDupla* retirarListaDupla(ListaDupla *L, int val){

	ListaDupla *p = buscarListaDupla(L, val);
	if (p) {
		if ( !isListaDuplaVazia(L) ){
			if (p->prev != NULL)
				p->prev->next = p->next;
			else
				L = p->next;

			if (p->next != NULL)
				p->next->prev = p->prev;
			else
				p->prev->next = NULL;
		}
		free(p);
	}
	return L;
}

void destruitListaDupla(ListaDupla *L){
	if (L != NULL)
		destruitListaDupla(L->next);
	
	free(L);
}

