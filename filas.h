struct pedido{
	int n;
	int prioridade;
	
	struct pedido *next;
};

struct impressora{
	int qtd;
	struct impressora* prev;
	struct impressora *next;
	struct pedido *prox;

};	


int addPedido(struct impressora* IP[],int prio);
int AlocaImpressora(struct impressora* IP[]);
int DefineMenor(struct impressora* IP[]);
struct pedido* NovoPedido(int p,int prio);
int addFF(struct pedido** F,struct pedido** NP);
int addPrio(struct pedido** F,struct pedido** NP);
int PrintImpressora(struct impressora* IP[]);
int PrintPedido(struct pedido* p);
int EsvaziaFila(struct impressora* IP[]);
