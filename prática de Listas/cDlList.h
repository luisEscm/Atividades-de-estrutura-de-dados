/*------------------------------------------------------------------------
dlListLuisEduardoSCMartins.h
Arquivo com uma double linked List
Autor: Luis Eduardo S. C. Martins (LEM) 10/2023
---------------------------------------------------------------------------*/
#ifndef __CDLLIST_H
#define __CDLLIST_H
#define TRUE 1
#define FALSE 0

typedef struct _dlnode_ {
  void *data;
  struct _dlnode_ *next;
  struct _dlnode_ *prev;
} DLNode;

typedef struct _cdllist_ {
    DLNode *first;
    DLNode *cur;
}CDLList;

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma CDLList
---------------------------------------------------------------------------*/
CDLList * cdllCreate( void );

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a CDLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int cdllDestroy ( CDLList *l);

/*------------------------------------------------------------------------
** Inseri um item no começo da CDLList
---------------------------------------------------------------------------*/
int cdllInsertAsFirst(CDLList *l, void *data);

/*------------------------------------------------------------------------
** Inseri um item no fim da CDLList
---------------------------------------------------------------------------*/
int cdllInsertAsLast ( CDLList *l, void *data);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CDLList e o retorna
---------------------------------------------------------------------------*/
void *cdllRemoveFirst (CDLList *l);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CDLList e o retorna
---------------------------------------------------------------------------*/
void *cdllRemoveLast (CDLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da CDLList
---------------------------------------------------------------------------*/
void *cdllGetFirst (CDLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da CDLList
---------------------------------------------------------------------------*/
void *cdllGetNext (CDLList *l);

/*------------------------------------------------------------------------
** Inseri um item na K-ésima posição da CDLList, assumindo k == 0 como a primeira posição da lista
---------------------------------------------------------------------------*/
int cdllInsertAsKesimo (CDLList *l, void *data, int k);

/*------------------------------------------------------------------------
** Inseri um item após um item especifico da CDLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int cdllInsertAfterSpec (CDLList *l, void *data, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Inseri um item antes de um item especifico da CDLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int cdllInsertBeforeSpec (CDLList *l, void*data, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Remove o item que especifico da CDLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *cdllRemoveSpec (CDLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da CDLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *cdllGetSpec (CDLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna o número de itens que estão na CDllist
---------------------------------------------------------------------------*/
int cdllNumElms( CDLList *l);

/*------------------------------------------------------------------------
** libera todos os nós da uma CDLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int cdllClear( CDLList *l, int (*freeDat)(void *));

/*------------------------------------------------------------------------
** Contena duas CDLList ordenadas e retorna uma terceira CDLList que tem uma cópia de todos os
** elementos das duas CDLList e mantendo a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
CDLList *cdllContatOrdNew( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Contena duas CDLList ordenadas e retorna uma uma das CDLList com todos os elementos mantendo
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
CDLList *cdllContatOrd( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Verifica se a CDLList l1 está contido na CDLList l2, se sim retorna TRUE caso contrario retorna FALSE,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
int cdllContido( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma CDLList que é a união dos elementos da CDLList l1 com CDLList l2,
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
CDLList *cdllUniao( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma CDLList que é a interseção dos elementos da CDLList l1 com CDLList l2,
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
CDLList *cdllIntersecao( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *));

#endif
