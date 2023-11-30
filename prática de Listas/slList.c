#ifndef __SLLIST_C
#define __SLLIST_C
#include <stdlib.h> 
#include "slList.h"

struct SLNode {
    void *data;
    SLNode *next;
};

struct SLList {
    SLNode *first;
    SLNode *cur;
};

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma SLList
---------------------------------------------------------------------------*/
SLList *sllCreate(void){
    SLList *l;
    l = (SLList * ) malloc(sizeof(SLList ));
    if ( l != NULL ) {
        l->first = NULL;
        return l;
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a SLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int sllDestroy(SLList *l){
    if ( l != NULL ) {
        if ( l->first == NULL ) {
            free (l);
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no começo da SLList
---------------------------------------------------------------------------*/
int sllInsertAsFirst(SLList *l, void *data){
    SLNode * newnode;
    if ( l != NULL) {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if ( newnode != NULL ){
            newnode->data = data;
            newnode->next = l->first;
            l->first = newnode;
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no fim da SLList
---------------------------------------------------------------------------*/
int sllInsertAsLast(SLList *l, void *data){
    SLNode *newnode, *last;
    if ( l != NULL ) {
        newnode = (SLNode *) malloc (sizeof(SLNode *));
        if ( newnode != NULL ) {
            newnode->next = NULL;
            newnode->data = data;

            if ( l->first == NULL ) {
                l->first = newnode;
            }else {
                last = l->first;
                while (last->next != NULL ) {
                    last = last->next;
                }
                last->next = newnode;
            }
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da SLList e o retorna
---------------------------------------------------------------------------*/
void *sllRemoveFirst(SLList *l){
    SLNode *first; void *data;
    if ( l != NULL) {
        if ( l->first != NULL ) {
            first = l->first;
            data = first->data;
            l->first = first->next;
            free(first);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na ultima posição da SLList e o retorna
---------------------------------------------------------------------------*/
void *sllRemoveLast(SLList *l){
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da SLList
---------------------------------------------------------------------------*/
void *sllGetFirst(SLList *l){
    if(l != NULL){
        l->cur = l->first;
        if(l->first != NULL){
            return l->cur->data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da SLList
---------------------------------------------------------------------------*/
void *sllGetNext(SLList *l){
    if(l != NULL){
        if(l->cur != NULL){
            l->cur = l->cur->next;
            if(l->cur != NULL){
                return l->cur->data;
            }
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Remove o item que especifico da SLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *sllRemoveSpec(SLList *l, void *key, int (*cmp)(void *, void *)){
    SLNode *spec, *prev;
    void *data;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            prev = NULL;
            stat = cmp(key, spec->data);
            while(stat != TRUE && spec->next != NULL){
                prev = spec;
                spec= spec->next;
                stat = cmp(key, spec->data);
            }
            if(stat == TRUE){
                data = spec->data;
                if ( prev == NULL) {
                    l->first = spec->next;
                } else {
                    prev->next =spec->next;
                }
                free (spec);
                return data;
            }
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da SLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *sllGetSpec(SLList *l, void *key, int (*cmp)(void *, void *)){
    SLNode *spec;
    void *data;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            stat = cmp(key, spec->data);
            while(stat != TRUE && spec->next != NULL){
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if(stat == TRUE){
                data = spec->data;
                return data;
            }
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da SLList que está na N-éssima posição,
** onde o 0 é a primeira posição, se o n form maior que o tamanho da lista retorna o ultimo item
---------------------------------------------------------------------------*/
void *sllGetNItem(SLList *l, int n){
    SLNode *nItem;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            nItem = l->first;
            while(n > 0 && nItem->next != NULL){
                nItem = nItem->next;
                n--;
            }
            data = nItem->data;
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Retorna o número de itens que estão na Sllist
---------------------------------------------------------------------------*/
int sllNumElms(SLList *l)
{
    SLNode *cur;
    int n;
    if(l != NULL){
        n = 0;
        cur = l->first;
        while(cur != NULL){
            n++;
            cur = cur->next;
        }
        return n;
    }
    return -1;
}

/*------------------------------------------------------------------------
** libera todos os nós da uma SLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int sllClear( SLList *l, int (*freeDat)(void *)){

    return FALSE;
}

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
SLList *sllContatOrdNew( SLList *l1, SLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
SLList *sllContatOrd( SLList *l1, SLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
int sllContido( SLList *l1, SLList *l2, int (*cmp)(void *, void *)){

    return FALSE;
}

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
SLList *sllUniao( SLList *l1, SLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
SLList *sllIntersecao( SLList *l1, SLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

#endif
