#include <stdio.h>
#include <stdlib.h>
#include "exe1.h"

int main(){
	struct impressora* IP[3];
	IP[0] = IP[1] = IP[2] = NULL;

	char resp;
	int p;

	AlocaImpressora(IP);
	addPedido(IP,0);
	PrintImpressora(IP);

	do{
		printf("É prioridade? (1/0) ");
		fscanf(stdin,"%d",&p);
		addPedido(IP,p);
		PrintImpressora(IP);
		EsvaziaFila(IP);
		PrintImpressora(IP);
		printf("Deseja continuar enviando pedidos? (s/n): ");
		fscanf(stdin," %c",&resp);
	}while(resp != 'n');	

	return 0;
}	

int EsvaziaFila(struct impressora* IP[]){
	for(int i = 0; i < 3; i++){
		struct pedido* temp = IP[i]->prox;

		if(temp != NULL){
			printf("Pedido %d na impressora %d efetuado.\n",temp->n,i+1);
			temp = temp->next;
			IP[i]->prox = temp;
			IP[i]->qtd -= 1;
		}	

		else{
			printf("Não há mais pedidos para a impressora %d\n",i+1);
		}	
	}	
	printf("\n");
}	

int PrintImpressora(struct impressora* IP[]){
	for(int i = 0; i < 3; i++){
		printf("Impressora %d: ",i+1);
		PrintPedido(IP[i]->prox);
		printf("\n");
	}	

	printf("\n\n");
}	

int PrintPedido(struct pedido* p){
	if(p != NULL){
		printf("->%d",p->n);
		PrintPedido(p->next);
	}	
}	

int AlocaImpressora(struct impressora* IP[]){
	for(int i = 0; i < 3; i++){
		IP[i] = (struct impressora* ) malloc(sizeof(struct impressora));
		IP[i]->qtd = 0;
		IP[i]->prox = NULL;
	}	

	IP[0]->prev = NULL;
	IP[0]->next = IP[1];

	IP[1]->prev = IP[0];
	IP[1]->next = IP[2];

	IP[2]->prev = IP[1];
	IP[2]->next = NULL;
}	

int addPedido(struct impressora* IP[],int prio){
	int m = DefineMenor(IP);

	struct pedido* new = NovoPedido(IP[m]->qtd,prio);
	

	if(IP[m]->prox == NULL){
		IP[m]->prox = new;
		return 1;
	}	

	if(prio == 1){
		addPrio(&IP[m]->prox,&new);
		return 1;	
	}	
	
	addFF(&IP[m]->prox,&new);
	return 1;
	
}	

int addPrio(struct pedido** F,struct pedido** NP){
	(*NP)->next = (*F);
	*F = *NP;

	return 1;
}	

int addFF(struct pedido** F,struct pedido** NP){
	if(*F != NULL){
		addFF(&(*F)->next,NP);

		if((*F)->next == NULL)
			(*F)->next = *NP;

		return 1;
	}	
}	

struct pedido* NovoPedido(int p,int prio){
	struct pedido* new = (struct pedido* ) malloc(sizeof(struct pedido));
	new->prioridade = prio;
	new->n = p;
	new->next = NULL;

	return new;
}	

int DefineMenor(struct impressora* IP[]){
	int menor = IP[0]->qtd;

	for(int i = 0; i < 3; i++){
		if(menor >= IP[i]->qtd)
			menor = IP[i]->qtd;
	}	
	
	for(int i = 0; i < 3; i++){
		if(menor == IP[i]->qtd)
			menor = i;
	}	

	IP[menor]->qtd += 1;
	return menor;

}	
