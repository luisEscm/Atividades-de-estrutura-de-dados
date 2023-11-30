/*------------------------------------------------------------------------
dlListLuisEduardoSCMartins.h
Arquivo com uma double linked List
Autor: Luis Eduardo S. C. Martins (LEM) 10/2023
---------------------------------------------------------------------------*/
#ifndef __DLLIST_H
#define __DLLIST_H
#define TRUE 1
#define FALSE 0

typedef struct _dlnode_ {
  void *data;
  struct _dlnode_ *next;
  struct _dlnode_ *prev;
} DLNode;

typedef struct _dllist_ {
    DLNode *first;
    DLNode *cur;
}DLList;

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma DLList
---------------------------------------------------------------------------*/
DLList * dllCreate( void );

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a DLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int dllDestroy ( DLList *l);

/*------------------------------------------------------------------------
** Inseri um item no começo da DLList
---------------------------------------------------------------------------*/
int dllInsertAsFirst(DLList *l, void *data);

/*------------------------------------------------------------------------
** Inseri um item no fim da DLList
---------------------------------------------------------------------------*/
int dllInsertAdLast ( DLList *l, void *data);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da DLList e o retorna
---------------------------------------------------------------------------*/
void *dllRemoveFirst (DLList *l);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da DLList e o retorna
---------------------------------------------------------------------------*/
void *dllRemoveLast (DLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da DLList
---------------------------------------------------------------------------*/
void *dllGetFirst (DLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da DLList
---------------------------------------------------------------------------*/
void *dllGetNext (DLList *l);

/*------------------------------------------------------------------------
** Remove o item que especifico da DLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *dllRemoveSpec (DLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da DLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *dllGetSpec (DLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna o número de itens que estão na Dllist
---------------------------------------------------------------------------*/
int dllNumElms( DLList *l);

/*------------------------------------------------------------------------
** libera todos os nós da uma DLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int dllClear( DLList *l, int (*freeDat)(void *));

/*------------------------------------------------------------------------
** Contena duas DLList ordenadas e retorna uma terceira DLList que tem uma cópia de todos os
** elementos das duas DLList e mantendo a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
DLList *dllContatOrdNew( DLList *l1, DLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Contena duas DLList ordenadas e retorna uma uma das DLList com todos os elementos mantendo
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
DLList *dllContatOrd( DLList *l1, DLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Verifica se a DLList l1 está contido na DLList l2, se sim retorna TRUE caso contrario retorna FALSE,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
int dllContido( DLList *l1, DLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma DLList que é a união dos elementos da DLList l1 com DLList l2,
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
DLList *dllUniao( DLList *l1, DLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma DLList que é a interseção dos elementos da DLList l1 com DLList l2,
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
DLList *dllIntersecao( DLList *l1, DLList *l2, int (*cmp)(void *, void *));

#endif
