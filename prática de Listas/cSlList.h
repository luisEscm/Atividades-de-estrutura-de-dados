/*------------------------------------------------------------------------
slListLuisEduardoSCMartins.h
Arquivo com uma simple linked List
Autor: Luis Eduardo S. C. Martins (LEM) 10/2023
---------------------------------------------------------------------------*/
#ifndef __CSLLIST_H
#define __CSLLIST_H
#define TRUE 1
#define FALSE 0

typedef struct _slnode_ {
  void *data;
  struct _slnode_ *next;
} SLNode;

typedef struct _csllist_ {
    SLNode *first;
    SLNode *cur;
}CSLList;

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma CSLList
---------------------------------------------------------------------------*/
CSLList * csllCreate( void );

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a CSLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int csllDestroy ( CSLList *l);

/*------------------------------------------------------------------------
** Inseri um item no começo da CSLList
---------------------------------------------------------------------------*/
int csllInsertAsFirst(CSLList *l, void *data);

/*------------------------------------------------------------------------
** Inseri um item no fim da CSLList
---------------------------------------------------------------------------*/
int csllInsertAsLast ( CSLList *l, void *data);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CSLList e o retorna
---------------------------------------------------------------------------*/
void *csllRemoveFirst (CSLList *l);

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CSLList e o retorna
---------------------------------------------------------------------------*/
void *csllRemoveLast (CSLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia que está na primeira posição da CSLList
---------------------------------------------------------------------------*/
void *csllGetFirst (CSLList *l);

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da CSLList
---------------------------------------------------------------------------*/
void *csllGetNext (CSLList *l);

/*------------------------------------------------------------------------
** Inseri um item na K-ésima posição da CSLList, assumindo k == 0 como a primeira posição da lista
---------------------------------------------------------------------------*/
int csllInsertAsKesimo (CSLList *l, void *data, int k);

/*------------------------------------------------------------------------
** Inseri um item após um item especifico da CSLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int csllInsertAfterSpec (CSLList *l, void *data, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Inseri um item antes de um item especifico da CSLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int csllInsertBeforeSpec (CSLList *l, void*data, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Remove o item que especifico da CSLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *csllRemoveSpec (CSLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da CSLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *csllGetSpec (CSLList *l, void *key, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da CSLList que está na N-éssima posição,
** onde o 0 é a primeira posição, se o n form maior que o tamanho da lista retorna o ultimo item
---------------------------------------------------------------------------*/
void *csllGetNItem (CSLList *l, int n);

/*------------------------------------------------------------------------
** Retorna o número de itens que estão na CSllist
---------------------------------------------------------------------------*/
int csllNumElms( CSLList *l);

/*------------------------------------------------------------------------
** libera todos os nós da uma CSLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int csllClear( CSLList *l, int (*freeDat)(void *));

/*------------------------------------------------------------------------
** Contena duas CSLList ordenadas e retorna uma terceira CSLList que tem uma cópia de todos os
** elementos das duas CSLList e mantendo a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
CSLList *csllContatOrdNew( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Contena duas CSLList ordenadas e retorna uma uma das CSLList com todos os elementos mantendo
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
CSLList *csllContatOrd( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Verifica se a CSLList l1 está contido na CSLList l2, se sim retorna TRUE caso contrario retorna FALSE,
** utilizando uma função de comparação que é da seguinte forma:
** "int cmp(void * a, void *b)"
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
int csllContido( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Verifica se todos os elementos da CSLList l1 estão contidos na CSLList l2, se sim
** retorna TRUE caso contrario retorna FALSE, utilizando uma função de comparação que
** é da seguinte forma:
** "int cmp(void * a, void *b)"
** onde o resultado esperado da função é o seguinte:
** 
** cmp(a, b) == TRUE, se a == b;
** cmp(a, b) == FALSE, se a != b.
**
** assumindo TRUE == 1 e FALSE == 0.
---------------------------------------------------------------------------*/
int csllElemContido( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma CSLList que é a união dos elementos da CSLList l1 com CSLList l2,
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
CSLList *csllUniao( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

/*------------------------------------------------------------------------
** Retorna uma CSLList que é a interseção dos elementos da CSLList l1 com CSLList l2,
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
CSLList *csllIntersecao( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *));

#endif
