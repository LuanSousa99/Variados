#define T 4

struct regiao{
	char cardeal;
	
	struct entidade *next;
	
};	

struct entidade{
	char* nome;
	char* endereco;
	int telefone;

	int escola;
	int hospital;
	int delegacia;
	int bombeiros;

	struct entidade *prox;
};	

int addEnt(struct regiao* R[]);
struct entidade* NewEnt(char nome[],char endereco[],int telefone);
int retornaTamanho(char string[]);
struct regiao* AlocaRegiao(char c);
void menu(int* op);
int InsertEnt(struct entidade** E,struct entidade** new);
int Tabela(struct regiao* R[]);
int ImprimeEnt(struct entidade* E);
int DeletaEnt(struct regiao* R[]);
int DeleteNode(struct entidade** E,char nome[],int ent);
int SelecionaRegiao();
int SelecionaEnt();
int OrdenaEnt(struct regiao* R[]);
int SelecionaOrdenacao();
int OrdenaTelefone(struct entidade** head,struct entidade** E);
int ComparaTelefone(struct entidade** head,struct entidade** E,struct entidade** aux);
int DeletaAux(struct entidade** temp,struct entidade** aux);
int ChangeNode1(struct entidade** head,struct entidade** E,struct entidade** aux);
int ChangeNode2(struct entidade** head,struct entidade** E,struct entidade** aux);
struct entidade* CN2(struct entidade** head,struct entidade** E,struct entidade** aux);

int OrdenaEndereco(struct entidade** head,struct entidade** E);
int ComparaEndereco(struct entidade** head,struct entidade** E,struct entidade** aux);
int OrdenaNome(struct entidade** head,struct entidade** E);
int ComparaNome(struct entidade** head,struct entidade** E,struct entidade** aux);

int AlteraEnt(struct regiao* R[]);
struct entidade* BuscaEnt(struct regiao* R[]);
struct entidade* search(struct entidade* E,char nome[]);
