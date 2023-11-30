/*------------------------------------------------------------------------
slListLuisEduardoSCMartins.h
Arquivo com uma simple linked List
Autor: Luis Eduardo S. C. Martins (LEM) 10/2023
---------------------------------------------------------------------------*/
#ifndef __SLLISTLUISEDUARDOSCMARTINS_H
#define __SLLISTLUISEDUARDOSCMARTINS_H
#define TRUE 1
#define FALSE 0

typedef struct _slnode_ {
  void *data;
  struct _slnode_ *next;
} SLNode;

typedef struct _sllist_ {
    SLNode *first;
    SLNode *cur;
}SLList;

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma SLList
---------------------------------------------------------------------------*/
SLList * sllCreate( void );

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a SLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int sllDestroy ( SLList *l);

/*------------------------------------------------------------------------
** Inseri um item no começo da SLList
---------------------------------------------------------------------------*/
int sllInsertAsFirst(SLList *l, void *data);

/*------------------------------------------------------------------------
** Inseri um item no fim da SLList
---------------------------------------------------------------------------*/
int sllInsertAsLast ( SLList *l, void *data);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da SLList e o retorna
---------------------------------------------------------------------------*/
void *sllRemoveFirst (SLList *l);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da SLList e o retorna
---------------------------------------------------------------------------*/
void *sllRemoveLast (SLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia que está na primeira posição da SLList
---------------------------------------------------------------------------*/
void *sllGetFirst (SLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da SLList
---------------------------------------------------------------------------*/
void *sllGetNext (SLList *l);

/*------------------------------------------------------------------------
** Remove o item que especifico da SLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *sllRemoveSpec (SLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da SLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *sllGetSpec (SLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da SLList que está na N-éssima posição,
** onde o 0 é a primeira posição, se o n form maior que o tamanho da lista retorna o ultimo item
---------------------------------------------------------------------------*/
void *sllGetNItem (SLList *l, int n);

/*------------------------------------------------------------------------
** Retorna o número de itens que estão na Sllist
---------------------------------------------------------------------------*/
int sllNumElms( SLList *l);

/*------------------------------------------------------------------------
** libera todos os nós da uma SLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int sllClear( SLList *l, int (*freeDat)(void *));

/*------------------------------------------------------------------------
** Contena duas SLList ordenadas e retorna uma terceira SLList que tem uma cópia de todos os
** elementos das duas SLList e mantendo a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
SLList *sllContatOrdNew( SLList *l1, SLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Contena duas SLList ordenadas e retorna uma uma das SLList com todos os elementos mantendo
** a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
SLList *sllContatOrd( SLList *l1, SLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Verifica se a SLList l1 está contido na SLList l2, se sim retorna TRUE caso contrario retorna FALSE,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
int sllContido( SLList *l1, SLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma SLList que é a união dos elementos da SLList l1 com SLList l2,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
**
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
SLList *sllUniao( SLList *l1, SLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma SLList que é a interseção dos elementos da SLList l1 com SLList l2,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
**
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
SLList *sllIntersecao( SLList *l1, SLList *l2, int (*cmp)(void *, void *));

#endif
