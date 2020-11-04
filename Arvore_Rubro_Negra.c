#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100

struct Vertice{
    int chave;
    int cor;
    struct Vertice *p;
    struct Vertice *esq;
    struct Vertice *dir;
};

typedef struct Vertice NO;

NO *tree_minimum(NO *x){
	while (x->esq != NULL){
		x = x->esq;
	}
	return x;
}

NO *RB_transplant(NO *Traiz, NO *u, NO *v){
	Traiz->p = NULL;
	if(u->p == NULL){
		Traiz = v;
	}else if(u == u->p->esq){
		if(v==NULL){
			u->p->esq = NULL;
		}else{
			u->p->esq = v;	
		}
	}else{
		if(v==NULL){
			u->p->dir = NULL;
		}else{
			u->p->dir = v;
		}
	}
	if (v!=NULL){
		v->p = u->p;
	}
	return Traiz;
}

NO *left_rotate(NO *Traiz, NO *x){
	//printf("ROTACAO A ESQUERDA:\n");
	NO *y = x->dir;
	x->dir = y->esq;
	if (y->esq != NULL){
		y->esq->p = x;
	}
	y->p = x->p;
	if(x->p == NULL){
		y->p = NULL;
		Traiz = y;
	}else if(x == x->p->esq){
		x->p->esq = y;	
	}else{
		x->p->dir = y;
	}
	if (Traiz == x){
		printf("raiz");
		Traiz = y;
	}
	y->esq = x;
	x->p = y;
	
	return Traiz;
}

NO *right_rotate(NO *Traiz, NO *x){
	
	//printf("ROTACAO A DIREITA:\n");
	NO *y = x->esq;
	x->esq = y->dir;
	if (y->dir != NULL){
		y->dir->p = x;
	}
	y->p = x->p;
	if(x->p == NULL){
		Traiz = y;
	}else if(x == x->p->dir){
		x->p->dir = y;	
	}else{
		x->p->esq = y;
	}
	y->dir = x;
	x->p = y;
	if (Traiz == x){
		Traiz = y;
		printf("raiz");
	}
	return Traiz;
}

NO *RB_delete_fixup(NO *Traiz, NO *x){
	
    
	NO *w;
	while ((x!=Traiz) && (x->cor == 2)){
		if (x == x->p->esq){
			w = x->p->dir;
			if(w->cor == 1){
				
				printf("SIMPLES A DIREITA\n");
				w->cor = 2;
				w->p->cor = 1;
				Traiz = left_rotate(Traiz,w->p);
				//w = x->p->dir;
				Traiz = left_rotate(Traiz,x->p);
				x = Traiz;
				imprimir(Traiz);
			}else{
				if((w->esq==NULL) && (w->dir==NULL)){//ajeitar
				
					printf("CASO 2\n");
					w->cor = 1;
					if (x->p->cor == 1){
						x->p->cor = 2;
						x = Traiz;
					}else{
						x = x->p;
					}	
					imprimir(Traiz);
				}else{
					int g=1;
					if(w->dir == NULL){
						g=2;
						printf("DUPLA A DIREITA\n");
						printf("CASO 3:\n");
						w->cor = 1;
						w->esq->cor = 2;
						Traiz = right_rotate(Traiz,w);
						w = x->p->dir;
						imprimir(Traiz);
					}
					if(g!=2){
						printf("SIMPLES A DIREIRA\n");	
					}
					w->cor = w->p->cor;
					w->dir->cor = 2;
					w->p->cor = 2;
					Traiz = left_rotate(Traiz,w->p);
					x = Traiz;
					imprimir(Traiz);
				}
			}
			
		}else{
			w = x->p->esq;
			if(w->cor == 1){
				printf("SIMPLES A ESQUERDA\n");	
				//w->cor = 2;
				w->dir->cor = 1;
				Traiz = right_rotate(Traiz,w->p);
				//w = x->p->dir;
				x = Traiz;
				imprimir(Traiz);
			}else{
				if((w->dir==NULL) && (w->esq==NULL)){
					printf("CASO 2\n");	
					w->cor = 1;
					if (x->p->cor == 1){
						x->p->cor = 2;
					}else{
						x = x->p;
					}
					imprimir(Traiz);	
				}else{
					int g=1;
					if(w->esq == NULL){
						g=2;
						printf("DUPLA A ESQUERDA\n");	
						w->cor = 1;
						w->dir->cor = 2;
						Traiz = left_rotate(Traiz,w);
						w = x->p->esq;
						imprimir(Traiz);
					}
					if(g!=2){
						printf("SIMPLES A ESQUERDA\n");	
					}
					w->cor = w->p->cor;
					w->esq->cor = 2;
					w->p->cor = 2;
					Traiz = right_rotate(Traiz,w->p);
					x = Traiz;
					imprimir(Traiz);
					
				}
			
		}
			
		}
	}
	return Traiz;
}

NO *RB_delete(NO *Traiz, NO *z){
	NO *y = z; 
	NO *info = NULL;
	int cor = y->cor;
	if((z->esq != NULL) &&(z->dir != NULL)){
		y = tree_minimum(z->dir);
		info = y;
	}
	if(y->cor == 1){
		if(( y->p->dir != NULL)&&(y = y->p->dir)){
			 y->p->dir = NULL;
		}else{
			 y->p->esq = NULL;
		}
	}else{
		if((y->esq == NULL) &&(y->dir == NULL)){
			Traiz = RB_delete_fixup(Traiz,y);
			Traiz = RB_transplant(Traiz,y,NULL);
			y->esq = NULL;
			y->dir = NULL;
		}else{
			Traiz = RB_delete_fixup(Traiz,y);
			Traiz = RB_transplant(Traiz,y,y->dir);
			
		}
	}
	if(info != NULL){
		z->chave= info->chave;
		/*if(z->esq!=NULL){
			info->esq = z->esq;
			z->esq->p = info;
		}else{
			info->esq = NULL;
		}
		if(z->dir!=NULL){
			info->dir = z->dir;
			z->dir->p = info;
		}else{
			info->dir = NULL;
		}
		info->cor = cor;
		imprimir(Traiz);
		
		if(z->p == NULL){
			Traiz = info;
		}else if(z == z->p->esq){
			if(info==NULL){
				z->p->esq = NULL;
			}else{
				z->p->esq = info;	
			}
		}else{
			if(info==NULL){
				z->p->dir = NULL;
			}else{
				z->p->dir = info;
			}
		}
		if (info!=NULL){
			info->p = z->p;
		}*/
		
	}
	printf("FINAL:\n");
	imprimir(Traiz);
	return Traiz;
}

NO *RB_Insert_Fixup(NO *Traiz, NO *z){

	while((z->p != NULL) && (z->p->cor == 1)){
		if (z->p == z->p->p->esq){
			NO *y = z->p->p->dir;
			if((y != NULL)&&(y->cor == 1)){
				printf("CASO 1:\n");
				z->p->cor = 2;
				if (y != NULL){
					y->cor = 2;	
				}
				z->p->p->cor = 1;
				z = z->p->p;
				//imprimir(Traiz);
				
			}else{
				int g=1;
				if(z == z->p->dir){
					g=2;
					printf("DUPLA A DIREITA\n");
					z = z->p;
					Traiz = left_rotate(Traiz,z);
					
				//imprimir(Traiz);
				}
				if(g!=2){
					printf("SIMPLES A DIREIRA\n");	
				}
				z->p->cor = 2;
				z->p->p->cor = 1;
				Traiz = right_rotate(Traiz,z->p->p);
				//imprimir(Traiz);
			}
		}else{
			NO *y = z->p->p->esq;
			if((y != NULL) && (y->cor == 1)){
				printf("CASO 1:\n");
				z->p->cor = 2;
				if (y != NULL){
					y->cor = 2;	
				}
				z->p->p->cor = 1;
				z = z->p->p;
				//imprimir(Traiz);
			}else{
				
				int g=1;
				if(z == z->p->esq){	
					printf("DUPLA A ESQUERDA\n");
					g=2;
					z = z->p;
					Traiz = right_rotate(Traiz,z);
					//imprimir(Traiz);
				}
				if(g!=2){
					printf("SIMPLES A ESQUERDA\n");	
				}
				z->p->cor = 2;
				z->p->p->cor = 1;
				Traiz = left_rotate(Traiz,z->p->p);
				//imprimir(Traiz);
			}
		}
	}
	//imprimir(Traiz);
	Traiz->cor = 2;
	return Traiz;
	
}



NO *insereArvore(NO *Traiz, int num) {
	printf("ANTES:\n");
	
	imprimir(Traiz);
	NO *z;
	z = (NO*)malloc(sizeof(NO));
	if(z == NULL){
		return NULL;	
	}
	z->chave=num;
	z->cor=1;
	z->esq=NULL;
	z->dir=NULL;
	z->p=NULL;
	
	NO *y = NULL;
	NO *x = Traiz;
	while (x != NULL){
	
		y = x;
		if(num<x->chave){
			x = x->esq;
		}else{
			x = x->dir;
		}
	}
	z->p = y;

	if (y == NULL) {
		Traiz = z;
		z->p = NULL;
		printf("Raiz da Arvore\n\n");
 	}else if(num < y->chave){
 		y->esq = z;
	}else{
		y->dir = z;
	}
	Traiz = RB_Insert_Fixup(Traiz,z);
	printf("\nDEPOIS:\n");
	imprimir(Traiz);
	return Traiz;
}

NO *buscaArvore(NO *Traiz, int num) {
	if(Traiz != NULL){
		NO *aux = Traiz;
		if (aux != NULL){
			while (aux != NULL){
				if (aux->chave == num){
				 	return aux;
				}else if(aux->chave > num){
					aux = aux->esq;
				}else{
					aux = aux->dir;	
				}
			}
		}
	}
	
	return NULL;
}



NO *insert(NO *Traiz, int num){
	NO *z = buscaArvore(Traiz, num);
	if (z != NULL) {
		printf("Elemento já existe\n");
		return Traiz;
	}else{
    	return insereArvore(Traiz, num);
	}
}

NO *remover(NO *Traiz, int num){
	NO *z = buscaArvore(Traiz, num);
	if (z == NULL) {
		return Traiz;
	}else{
    	return RB_delete(Traiz, z);
	}
}


void imprimir(NO* h){
	
	if (h==NULL){
		return;
	}	
	
	printf("Chave=%d, cor=%d",h->chave, h->cor);
	if( h->esq != NULL){
		printf(" esq=%d",h->esq->chave);
	}else{
		printf(" esq=NULL");
	}
	if(h->dir != NULL){
		printf(" dir=%d",h->dir->chave);
	}else{
		printf(" dir=NULL");
	}
	if(h->p != NULL){
		printf(" p=%d\n",h->p->chave);
	}else{
		printf(" p=NULL\n");
	}
	imprimir(h->esq);
	imprimir(h->dir);
}

int main(){
    int n=MAX;
    int met = 1;
    int opc = 1;
    int chave;
    NO* Traiz = NULL;

    while( opc!=6){
            printf("\n\n");
            printf("\n _____|RUBRO_NEGRA|_____");
            printf("\n|                       |");
            printf("\n|  1 - Buscar           |");
            printf("\n|  2 - Inserir Manual   |");
            printf("\n|  3 - Inserir Definido |");
            printf("\n|  4 - Remover          |");
            printf("\n|  5 - Imprimir         |");
            printf("\n|  6 - Sair             |");
            printf("\n|_______________________|\n");

            scanf("%d",&opc);

            switch(opc){

                case 1:{
                    int i;
                    printf("\n Digite a chave");
                    scanf("%d",&chave);
                    NO *a=buscaArvore(Traiz,chave);
                    if(a==NULL){
                        printf("\n Chave nao encontrada!");
                    }else{
                        printf("\n Chave encontrada");
                    }
                    imprimir(Traiz);
                    break;
                }
                case 2:{
                    printf("\n Digite a chave");
                    scanf("%d",&chave);
                    printf("INSERINDO NUMERO %d\n\n",chave);
                    Traiz = insert(Traiz,chave);
                    break;
                }
                case 3:{
                    int tam=7;
                    int vetor[tam];
                        /*vetor[0]=17;
                        vetor[1]=22;
                        vetor[2]=16;
                        vetor[3]=29;
                        vetor[4]=7;
                        vetor[5]=4;
                        vetor[6]=32;
                        vetor[7]=2;
                        vetor[8]=3;
                        vetor[9]=34;
                        vetor[10]=33;*/
                        //vetor[11]=1;
                        vetor[0]=100;
                        vetor[1]=50;
                        vetor[2]=200;
                        vetor[3]=25;
                        vetor[4]=150;
                        vetor[5]=250;
                        vetor[6]=240;
                        
                        //vetor[12]=17;

                    int i;
                    for (i=0; i<tam;i++){
                    	printf("INSERINDO NUMERO %d\n\n",vetor[i]);
                       Traiz = insert(Traiz,vetor[i]);
                       //imprimir(Traiz);
                       printf("\n***********************************************************\n");
                    }
                    imprimir(Traiz);
                    break;
                }
                case 4:{
                    int i;
                    printf("\n Digite a chave");
                    scanf("%d",&chave);
                    
                    printf("EXCLUINDO NUMERO %d\n\n",chave);
                    remover(Traiz,chave);
                    printf("\n***********************************************************\n");
                    break;
                }
                case 5:{
                    imprimir(Traiz);
                    break;
                }
                default:{
                   if(opc == 6){
                    continue;
                   }
                   printf("\n Digite uma das opções");
                   break;
                }

        }

        }

}


