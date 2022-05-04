#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int soma = 0;
int **matriz;
int n = 0;
int i = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *soma_linhas(void *arg);

int main(void){

	scanf("%d", &n);
	matriz = (int **)malloc(n * sizeof(int *));
	for(int i = 0; i < n; i++){
		matriz[i] = (int*)malloc(n*sizeof(int));
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &matriz[i][j]);
		}
	}
	
	
	pthread_t threads[n];
	for (int i = 0; i < n; i++){
		if(pthread_create(&(threads[i]), NULL, soma_linhas, (void *)matriz)){
			printf("ERRO");
		}
	}
	
	
	for (int i = 0; i < n; i++){
		pthread_join(threads[i], NULL);
	}
	
	printf("Soma da linha = %d", soma);
	return 0;
}

void *soma_linhas(void *arg){
	pthread_mutex_lock(&mutex);
	
	for(int j = 0; j < n; j++){
		soma = soma + matriz[i][j];
	}
	
	i++;
	
	pthread_mutex_unlock(&mutex);
	return arg;	
} 
