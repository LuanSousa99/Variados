#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe2.h"

int main(){
	PRODUTO P[T];

	char* produto[T] = {"Agua","Suco","Carne","Queijo","Leite","Tomate","Cebola","Picanha","Cafe","Costela"};
	int preco[T] = {10,5,3,15,20,22,17,50,40,25};
	int validade[T] = {31,50,200,33,50,78,10,87,64,32};
	int qtd[T] = {50,100,120,30,64,78,20,10,12,45};
	int op;
	
	DefineProduto(P,produto,preco,validade,qtd);
	
	do{
		menu(&op);
		
		switch(op){
			case 1:
				QuickSortNome(P,0,T-1);
				break;

			case 2:
				QuickSortPreco(P,0,T-1);
				break;

			case 3:
				QuickSortVal(P,0,T-1);
				break;

			case 4:
				QuickSortQTD(P,0,T-1);
				break;

			case 5:
				ImprimeTabela(P);
				break;
			
			default:
				op = 0;
				break;	
		}
	}while(op != 0);	
	return 0;
}	

int QuickSortNome(PRODUTO P[],int inicio,int fim){
	if(inicio < fim){
		int pivo = reparteNome(P,inicio,fim);
		
		QuickSortNome(P,inicio,pivo-1);
		QuickSortNome(P,pivo+1,fim);

	}	
}

int reparteNome(PRODUTO P[],int inicio,int fim){
	int I = inicio;
	int F = fim;
	char* pivo = P[I].nome;	
	PRODUTO aux = P[I];
	PRODUTO temp;

	
	while(I < F){
		while(strncmp(pivo,P[I].nome,3) >= 0){
			I++;
			
			if(I > F)
				break;
		}

		while(strncmp(pivo,P[F].nome,3) <= -1){
			F--;

			if(I > F)
				break;
		}	

		if(I < F){
			temp = P[I];
			P[I] = P[F];
			P[F] = temp;
		}	
	}	

	P[inicio] = P[F];
	P[F] = aux;

	return F;

}	

int QuickSortQTD(PRODUTO P[],int inicio,int fim){
	if(inicio < fim){
		int pivo = reparteQTD(P,inicio,fim);

		QuickSortQTD(P,inicio,pivo-1);
		QuickSortQTD(P,pivo+1,fim);
	}	
}	

int reparteQTD(PRODUTO P[],int inicio,int fim){
	int I = inicio;
	int F = fim;
	int pivo = P[I].qtd;
	PRODUTO aux = P[I];
	PRODUTO temp;

	while(I < F){
		while(pivo >= P[I].qtd)
			I++;

		while(pivo < P[F].qtd)
			F--;

		if(I < F){
			temp = P[I];
			P[I] = P[F];
			P[F] = temp;
		}	
	}	
	P[inicio] = P[F];
	P[F] = aux;

	return F;
}	

int QuickSortVal(PRODUTO P[],int inicio,int fim){
	if(inicio < fim){
		int pivo = reparteVal(P,inicio,fim);

		QuickSortVal(P,inicio,pivo-1);
		QuickSortVal(P,pivo+1,fim);
	}	
}	

int reparteVal(PRODUTO P[],int inicio,int fim){
	int I = inicio;
	int F = fim;
	int pivo = P[I].validade;
	PRODUTO aux = P[I];
	PRODUTO temp;

	while(I < F){
		
		while(pivo >= P[I].validade){
			I++;
		}
		while(pivo < P[F].validade){
			F--;
		}
		if(I < F){
			temp = P[I];
			P[I] = P[F];
			P[F] = temp;
		}	
	}	
	
	P[inicio] = P[F];
	P[F] = aux;

	return F;
}	

void ImprimeTabela(PRODUTO P[]){
	for(int i = 0; i < T; i++){
		printf("%10s | Preco: R$%8d.00 | Validade: %8d dias | quantidade: %8d\n",P[i].nome,P[i].preco,P[i].validade,P[i].qtd);
	}	
}	

int QuickSortPreco(PRODUTO P[],int inicio,int fim){
	if(inicio < fim){	
		
		int pivo = repartePreco(P,inicio,fim);	
	
		QuickSortPreco(P,inicio,pivo-1);
		QuickSortPreco(P,pivo+1,fim);
	}
}	

int repartePreco(PRODUTO P[],int inicio,int fim){
	int i = inicio;
	int f = fim;
	int pivo = P[i].preco;
	PRODUTO temp;
	PRODUTO aux;
	aux = P[i];

	while(i < f){
		while(pivo >= P[i].preco)
			i++;
			

		while(pivo < P[f].preco)
			f--;

		if(i < f){
			temp = P[i];
			P[i] = P[f];
			P[f] = temp;	
		}	


	}	
	
	temp = P[f];
	P[f] = aux;
	P[inicio] = temp;	


	return f;
}	

int menu(int* op){
	printf("Selecione uma das opções abaixo: \n\n\n");

	printf("[1] Ordena por nome;\n");
	printf("[2] Ordena por preco;\n");
	printf("[3] Ordena por validade;\n");
	printf("[4] Ordena por quantidade;\n");
	printf("[5] Imprime Tabela;\n");
	printf("[0] EXIT.");

	fscanf(stdin,"%d",op);
}	

int DefineProduto(PRODUTO P[],char* produto[],int preco[],int validade[],int qtd[]){
	for(int i = 0; i < T; i++){
		int x = RetornaTamanho(produto[i]);
		P[i].nome = (char* ) malloc(x * sizeof(char));
		strcpy(P[i].nome,produto[i]);
		P[i].preco = preco[i];
		P[i].validade = validade[i];
		P[i].qtd = qtd[i];


	}	
	ImprimeTabela(P);
	printf("\n\n");
}	

int RetornaTamanho(char* produto){
	int x = 0;

	while(produto[x] != '\0'){
		x++;
	}	

	return x;
}	
