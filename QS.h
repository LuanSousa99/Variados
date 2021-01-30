#define T 10

struct produto{
	char* nome;
	int preco;
	int validade;
	int qtd;

};	

typedef struct produto PRODUTO;

int DefineProduto(PRODUTO P[],char* produto[],int preco[],int validade[],int qtd[]);
int RetornaTamanho(char* produto);
int menu(int* op);
void ImprimeTabela(PRODUTO P[]);
int QuickSortPreco(PRODUTO P[],int inicio,int fim);
int repartePreco(PRODUTO P[],int inicio,int fim);
int QuickSortVal(PRODUTO P[],int inicio,int fim);
int reparteVal(PRODUTO P[],int inicio,int fim);
int QuickSortQTD(PRODUTO P[],int inicio,int fim);
int reparteQTD(PRODUTO P[],int inicio,int fim);
int QuickSortNome(PRODUTO P[],int inicio,int fim);
int reparteNome(PRODUTO P[],int inicio,int fim);
