#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe3.h"

int main(){
	struct regiao* R[T];	
	char c[T] = {'N','L','S','O'};
	int op;

	for(int i = 0; i < T; i++)
		R[i] = AlocaRegiao(c[i]);
	
	do{
		menu(&op);

		switch(op){
			case 1:
				addEnt(R);
				break;

			case 2:
				DeletaEnt(R);
				break;

			case 3:
				AlteraEnt(R);
				break;

			case 4:
				BuscaEnt(R);
				break;

			case 5:	
				OrdenaEnt(R);
				break;

			case 6:
				Tabela(R);
				break;

			default:
				op = 0;
				break;	
		}	

	}while(op != 0);	
		
	
	return 0;
}

struct entidade* BuscaEnt(struct regiao* R[]){
	char buf[50];
	char nome[50];

	printf("Digite o nome da entidade que você deseja buscar: ");
	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%s",nome);
	
	struct entidade* E = NULL;

	for(int i = 0; i < T; i++){
		E = search(R[i]->next,nome);
		if(E != NULL)
			break;
	}	

	if(E == NULL){
		printf("Entidade não encontrada!\n\n");
		return (NULL);
	}	
	
	printf("Nome da entidade: %s || Endereço: %s || Telefone: %d\n",E->nome,E->endereco,E->telefone);
	return E;


}	

struct entidade* search(struct entidade* E,char nome[]){
	if(E == NULL)
		return (NULL);
	
	if(E != NULL){
		printf("search %s\n",E->nome);
		if(strcmp((E)->nome,nome) == 0){
			printf("Entidade %s encontrada!\n\n",(E)->nome);
			return E;
		}

		else{
			struct entidade* X = search((E)->prox,nome);
			return X;
		}	
	}		
}	

int AlteraEnt(struct regiao* R[]){
	struct entidade* E = BuscaEnt(R);

	if(E != NULL){
		char buf[50];
		char c[50];
		int tp;

		int x = SelecionaOrdenacao();
		
		if(x == 1){
			printf("Digite o novo nome da entidade: ");
			
			if(fgets(buf,sizeof(buf),stdin))
				sscanf(buf,"%s",c);
			
			strcpy(E->nome,c);
			return 1;
		}	

		if(x == 2){
			printf("Digite o novo endereço da entidade: ");

			if(fgets(buf,sizeof(buf),stdin))
				sscanf(buf,"%s",c);
			
			strcpy(E->endereco,c);
			return 1;
		}

		if(x == 3){
			printf("Digite o novo número de telefone da entidade: ");

			if(fgets(buf,sizeof(buf),stdin))
				sscanf(buf,"%d",&tp);

			E->telefone = tp;
			return 1;
		}	
			
	}	
}	

int OrdenaEnt(struct regiao* R[]){
	char buf[50];
	int x;
	printf("Quantas regiões você deseja ordenar? ");

	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",&x);
	
	if(x <= 0){
		printf("%d, sair da função\n",x);
		return -1;
	}	

	if(x > 4){
		printf("O número máximo de regiões é %d\n",T);
		x = T;
	}	

	int array[x];
	
	

	for(int i = 0; i < x; i++){
		printf("%do. Região: \n",i+1);
		int y = SelecionaRegiao();
		int z = SelecionaOrdenacao();

		switch(z){
			case 1:
				OrdenaNome(&R[y]->next,&R[y]->next);
				break;

			case 2:
				OrdenaEndereco(&R[y]->next,&R[y]->next);
				break;
			
			case 3:
				OrdenaTelefone(&R[y]->next,&R[y]->next);
				break;

			default:
				break;	
		}	

	}	

}	
int OrdenaNome(struct entidade** head,struct entidade** E){
	if(*E != NULL){
		
		ComparaNome(head,E,&(*E)->prox);
		OrdenaNome(head,&(*E)->prox);

	}	
}

int ComparaNome(struct entidade** head, struct entidade** E,struct entidade** aux){
	if(*E != NULL){
		if(*aux != NULL){
			printf("head: %s || E: %s || aux: %s\n",(*head)->nome,(*E)->nome,(*aux)->nome);
			
			if(strcmp((*E)->nome,(*aux)->nome) >= 1){
				struct entidade* temp;

				printf("Depois do if || head: %s || E: %s || aux: %s\n",(*head)->nome,(*E)->nome,(*aux)->nome);
				
				if(*head == *E){
					if((*E)->prox == *aux){
						temp = *head;
						(*head) = (*head)->prox;
						temp->prox = (*aux)->prox;

						(*head)->prox = temp;
						*E = *head;
						
						ComparaNome(head,E,&(*E)->prox);	
						return 1;
					}	

					else{
						temp = *head;
						
						while(*head != *aux){
							*head = (*head)->prox;
						}	


						DeletaAux(&temp,aux);

						printf("2\n");

						(*head)->prox = temp;
						*E = *head;
							
						ComparaNome(head,E,&(*E)->prox);
						return 1;

					}	
				}

				else{
					if((*E)->prox == *aux){
						ChangeNode1(head,E,aux);
							
						ComparaNome(head,head,&(*head)->prox);
						return 1;
					}

					else{
						ChangeNode2(head,E,aux);

						ComparaNome(head,head,&(*head)->prox);
						return 1;

					}	
				}		


			}	
			ComparaNome(head,E,&(*aux)->prox);
			return 1;
		}	
	}	
}	
	
int OrdenaEndereco(struct entidade** head,struct entidade** E){
	if(*E != NULL){
		
		ComparaEndereco(head,E,&(*E)->prox);
		OrdenaEndereco(head,&(*E)->prox);

	}	
}	

int ComparaEndereco(struct entidade** head, struct entidade** E,struct entidade** aux){
	if(*E != NULL){
		if(*aux != NULL){
			printf("head: %s || E: %s || aux: %s\n",(*head)->endereco,(*E)->endereco,(*aux)->endereco);
			
			if(strcmp((*E)->endereco,(*aux)->endereco) >= 1){
				struct entidade* temp;

				printf("Depois do if || head: %s || E: %s || aux: %s\n",(*head)->endereco,(*E)->endereco,(*aux)->endereco);
				
				if(*head == *E){
					if((*E)->prox == *aux){
						temp = *head;
						(*head) = (*head)->prox;
						temp->prox = (*aux)->prox;

						(*head)->prox = temp;
						*E = *head;
						
						ComparaEndereco(head,E,&(*E)->prox);	
						return 1;
					}	

					else{
						temp = *head;
						
						while(*head != *aux){
							*head = (*head)->prox;
						}	


						DeletaAux(&temp,aux);

						printf("2\n");

						(*head)->prox = temp;
						*E = *head;
							
						ComparaEndereco(head,E,&(*E)->prox);
						return 1;

					}	
				}

				else{
					if((*E)->prox == *aux){
						ChangeNode1(head,E,aux);
							
						ComparaEndereco(head,head,&(*head)->prox);
						return 1;
					}

					else{
						ChangeNode2(head,E,aux);

						ComparaEndereco(head,head,&(*head)->prox);
						return 1;

					}	
				}		


			}	
			ComparaEndereco(head,E,&(*aux)->prox);
			return 1;
		}	
	}	
}	
int OrdenaTelefone(struct entidade** head,struct entidade** E){
	if(*E != NULL){
		
		ComparaTelefone(head,E,&(*E)->prox);
		OrdenaTelefone(head,&(*E)->prox);

	}	
}	

int ComparaTelefone(struct entidade** head, struct entidade** E,struct entidade** aux){
	if(*E != NULL){
		if(*aux != NULL){
			printf("head: %d || E: %d || aux: %d\n",(*head)->telefone,(*E)->telefone,(*aux)->telefone);
			
			if((*E)->telefone > (*aux)->telefone){
				struct entidade* temp;

				printf("Depois do if || head: %d || E: %d || aux: %d\n",(*head)->telefone,(*E)->telefone,(*aux)->telefone);
				
				if(*head == *E){
					if((*E)->prox == *aux){
						temp = *head;
						(*head) = (*head)->prox;
						temp->prox = (*aux)->prox;

						(*head)->prox = temp;
						*E = *head;
						
						ComparaTelefone(head,E,&(*E)->prox);	
						return 1;
					}	

					else{
						temp = *head;
						
						while(*head != *aux){
							*head = (*head)->prox;
						}	


						DeletaAux(&temp,aux);

						printf("2\n");

						(*head)->prox = temp;
						*E = *head;
							
						ComparaTelefone(head,E,&(*E)->prox);
						return 1;

					}	
				}

				else{
					if((*E)->prox == *aux){
						ChangeNode1(head,E,aux);
							
						ComparaTelefone(head,head,&(*head)->prox);
						return 1;
					}

					else{
						ChangeNode2(head,E,aux);

						ComparaTelefone(head,head,&(*head)->prox);
						return 1;

					}	
				}		


			}	
			ComparaTelefone(head,E,&(*aux)->prox);
			return 1;
		}	
	}	
}	

int ChangeNode2(struct entidade** head,struct entidade** E,struct entidade** aux){
	if(*head != NULL){
		if((*head)->prox == *E){
			printf("HERE WE ARE MOTHERFUCKER! aux: %d\n",(*aux)->telefone);
			struct entidade* temp;
			struct entidade* temp2;
			temp = *E;
			temp2 = *aux;
			(*head)->prox = (*head)->prox->prox;

			temp = CN2(head,&temp,aux);
			printf("Voltastes\n");
			
			printf("aux: %d OK\n",temp2->telefone);
			temp2->prox = (*head)->prox;
			(*head)->prox = temp2;		
			return 1;
		}	
		
		else{
			ChangeNode2(&(*head)->prox,E,aux);
		}	
	}
}

struct entidade* CN2(struct entidade** head,struct entidade** E,struct entidade** aux){
	if(*head != NULL){
		if((*head)->prox == *aux){
			(*head)->prox = (*head)->prox->prox;
			struct entidade* temp;
			struct entidade* aux2;

			aux2 = *aux;
			temp = *E;
			temp->prox = (*head)->prox;
			
			(*head)->prox = temp;
			return aux2;
		}

		else{
			CN2(&(*head)->prox,E,aux);
		}	
	}	
}	

int ChangeNode1(struct entidade** head,struct entidade** E,struct entidade** aux){
	if(*head != NULL){
		if((*head)->prox == *E){
			printf("Teste caminho: head: %d || E: %d || aux: %d\n",(*head)->telefone,(*E)->telefone,(*aux)->telefone);
			struct entidade* temp = *aux;
			
			if(temp->prox != NULL){
				(*E)->prox = temp->prox;
			}	

			else{
				(*E)->prox = NULL;
			}	

			temp->prox = *E;

			(*head)->prox = temp;

			return 1;
		}	

		else{
			ChangeNode1(&(*head)->prox,E,aux);
		}	
	}	
}	

int DeletaAux(struct entidade** temp,struct entidade** aux){
	if(*temp != NULL){
		if((*temp)->prox == *aux){
			printf("Deleta Aux\n");
			(*temp)->prox = (*temp)->prox->prox;
			return 1;
		}

		else{
			DeletaAux(&(*temp)->prox,&(*aux));
		}	
	}	

}	

int SelecionaOrdenacao(){
	char buf[10];
	int x;

	printf("Selecione uma das opções abaixo: \n\n\n");

	printf("[1] Nome;\n");
	printf("[2] Endereço;\n");
	printf("[3] Telefone;\n");

	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",&x);
	
	if(x < 1 && x > 3){
		printf("Número %d inexistente na lista! 1 será reposto no lugar\n",x);
		x = 1;
	}	

	return x;
}	

int DeletaEnt(struct regiao* R[]){
	printf("Selecione a região da entidade que você deseja deletar: \n\n\n");
	
	char buf[50];
	char nome[30];
	int x = SelecionaRegiao();
	int ent;


	if(x >= 0 && x < T){
		if(R[x]->next == NULL){
			printf("***Região sem entidades*** Não há o que deletar!!!\n\n");
			return -1;
		}

		ImprimeEnt(R[x]->next);
		printf("\n\n");

		ent = SelecionaEnt();

		printf("Digite o nome da entidade a ser deletada: ");
		
		if(fgets(buf,sizeof(buf),stdin))
			sscanf(buf,"%s",nome);

		int y = DeleteNode(&R[x]->next,nome,ent);
		
		if(y == -1)
			R[x]->next = R[x]->next->prox;

	}
	
	else{
		printf("Número %d inexistente na lista de regiões!!! Região Norte será escolhida no lugar.\n");

		if(R[0]->next == NULL){
			printf("***Região sem entidades*** Não há o que deletar!!!\n\n");
		}

		ImprimeEnt(R[0]->next);
		printf("\n\n");

		ent = SelecionaEnt();

		printf("Digite o nome da entidade a ser deletada: ");

		if(fgets(buf,sizeof(buf),stdin))
			sscanf(buf,"%s",nome);

		x = DeleteNode(&R[0]->next,nome,ent);
		
		if(x == -1)
			R[0]->next = R[0]->next->prox;

	}	


}	

int DeleteNode(struct entidade** E,char nome[],int ent){
	if(*E != NULL){
		int x = strcmp((*E)->nome,nome);

		if(x == 0){
			printf("%s == %s\n",(*E)->nome,nome);

			if(ent == 1 && (*E)->escola == 1){
				printf("Entidade %s deletada!\n",(*E)->nome);
				return -1;
			}	

			if(ent == 2 && (*E)->hospital == 1){
				printf("Entidade %s deletada!\n",(*E)->nome);
				return -1;
			}	

			if(ent == 3 && (*E)->delegacia == 1){
				printf("Entidade %s deletada!\n",(*E)->nome);
				return -1;
			}

			if(ent == 4 && (*E)->bombeiros == 1){
				printf("Entidade %s deletada!\n",(*E)->nome);
				return -1;
			}	
		}	
		x = DeleteNode(&(*E)->prox,nome,ent);
		
		if(x == -1){
			struct entidade* aux;
			aux = (*E)->prox;
			(*E)->prox = (*E)->prox->prox;
			free(aux);
		}	

		return 1;
	}	

}	

int Tabela(struct regiao* R[]){
		for(int i = 0; i < T; i++){
			printf("#Região (%c): \n\n",R[i]->cardeal);
			
			if(R[i]->next != NULL){
				ImprimeEnt(R[i]->next);
			}

			else{
				printf("***Região sem entidades***\n");
			}	
			
			printf("\n\n");
		}	
}	

int ImprimeEnt(struct entidade* E){
	if(E != NULL){
		int x = 0;
		char* ent[T] = {"Escola","Hospital","Delegacia","Corpo_de_bombeiros"};
		
		if((E)->escola == 1)
			x = 0;

		if((E)->hospital == 1)
			x = 1;

		if((E)->delegacia == 1)
			x = 2;

		if((E)->bombeiros == 1)
			x = 3;

		printf("%s %s | Endereço: %s | Telefone: %d\n",ent[x],E->nome,E->endereco,E->telefone);

		ImprimeEnt(E->prox);


	}		
}	

int addEnt(struct regiao* R[]){
	char buf[50];
	char nome[20];
	char endereco[20];
	int x = 0;
	int telefone;

	printf("Digite o nome da entidade (use _ para espaço): ");
	fflush(stdin);

	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%s",nome);
	
	
	printf("Digite o endereço da entidade: ");
	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%s",endereco);
		
	printf("Digite o telefone da entidade: ");
	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",&telefone);

	printf("Nome: %s\n",nome);
	printf("Endereco: %s\n",endereco);
	printf("Telefone: %d\n",telefone);
	
	struct entidade *new = NewEnt(nome,endereco,telefone);

	printf("Em qual região você deseja adicionar essa nova entidade?  \n\n");
	x = SelecionaRegiao();
	
	if(x >= 0 && x < T){
		if(R[x]->next == NULL){
			R[x]->next = new;
			return 1;
		}	

		InsertEnt(&(R[x])->next,&new);
		return 1;
	}	

	else{
		printf("Número %d inexistente na lista acima!!! Região Norte será adicionada no lugar!\n\n",x);
		if(R[0]->next == NULL){
			R[0]->next = new;
			return 1;
		}	
		
		InsertEnt(&(R[0])->next,&new);
	}	

}	

int InsertEnt(struct entidade** E,struct entidade** new){
	if(*E == NULL)
		return -1;
	
	else{
		int x = InsertEnt(&(*E)->prox,new);

		if(x == -1){
			(*E)->prox = *new;	
		}	

		return 1;
	}	
}	

int SelecionaEnt(){
	char buf[10];
	int x;
	printf("Selecione uma das opções abaixo: \n\n\n");

	printf("[1] Escola\n");
	printf("[2] Hospital\n");
	printf("[3] Delegacia\n");
	printf("[4] Corpo de bombeiros\n");

	fflush(stdin);
	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",&x);

	if(x < 1 && x > 4){
		printf("Esse número %d não existe na lista!!!, Escola será retornado no lugar.\n",x);
		return 1;
	}	


	return x;

}	

int SelecionaRegiao(){
	char buf[10];
	int x;

	printf("[1] Norte\n");
	printf("[2] Leste\n");
	printf("[3] Sul\n");
	printf("[4] Oeste\n");

	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",&x);
	x--;
	return x;
}	

struct entidade* NewEnt(char nome[],char endereco[],int telefone){
	char buf[10];
	struct entidade *new = (struct entidade* ) malloc(sizeof(struct entidade));
	int x = retornaTamanho(nome);
	new->nome = (char* ) malloc(x * sizeof(char));
	strcpy(new->nome,nome);
	printf("new->nome: %s\n",new->nome);

	x = retornaTamanho(endereco);
	new->endereco = (char* ) malloc(x * sizeof(char));
	strcpy(new->endereco,endereco);
	printf("new->endereco: %s\n",new->endereco);

	new->telefone = telefone;
	new->escola = 0;
	new->hospital = 0;
	new->delegacia = 0;
	new->bombeiros = 0;

	new->prox = NULL;

	x = SelecionaEnt();

	switch(x){
		case 1:
			new->escola = 1;
			break;

		case 2:
			new->hospital = 1;
			break;

		case 3:
			new->delegacia = 1;
			break;

		case 4:
			new->bombeiros = 1;
			break;

		default:
			printf("Item selecionado inexistente, escola será escolhida no lugar!\n\n");
			new->escola = 1;
			break;	
	}	

	return new;
	

}	

int retornaTamanho(char string[]){
	int x = 0;

	while(string[x] != '\0'){
		x++;
	}	

	return x;
}	

struct regiao* AlocaRegiao(char c){
	struct regiao* new;
	new = (struct regiao* ) malloc(sizeof(struct regiao));
	new->cardeal = c;
	new->next = NULL;

	return new;

}	

void menu(int* op){
	printf("Selecione uma das opções abaixo: \n\n\n");
	char buf[20];

	printf("[1] Adicionar entidade;\n"); 
	printf("[2] Deletar entidade;\n"); 
	printf("[3] Alterar entidade;\n");
	printf("[4] Buscar informação;\n");
	printf("[5] Ordenar entidades;\n"); 
	printf("[6] Imprimir tabela;\n"); 
	printf("[0] EXIT.\n\n");
	
	if(fgets(buf,sizeof(buf),stdin))
		sscanf(buf,"%d",op);
}	
