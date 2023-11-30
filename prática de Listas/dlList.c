#ifndef __DLLIST_C
#define __DLLIST_C
#include <stdlib.h> 
#include "dlList.h"

struct DLNode {
    void *data;
    DLNode *next;
    DLNode *prev;
};

struct DLList {
    DLNode *first;
    DLNode *cur;
};

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma DLList
---------------------------------------------------------------------------*/
DLList *dllCreate(void){
    DLList *l;
    l = (DLList *)malloc(sizeof(DLList));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a DLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int dllDestroy(DLList *l){
    if(l != NULL){
        if(l->first == NULL){
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no começo da DLList
---------------------------------------------------------------------------*/
int dllInsertAsFirst(DLList *l, void *data){
    DLNode *newNode, *first;
    if(l != NULL){
        newNode = (DLNode *)malloc(sizeof(DLNode));
        if(newNode != NULL){
            newNode->data = data; 
            first = l->first;
            newNode->next = first;
            newNode->prev = NULL;
            if(first != NULL){
                first->prev = newNode;
            }
            l->first = newNode;
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no fim da DLList
---------------------------------------------------------------------------*/
int dllInsertAdLast(DLList *l, void *data){
    DLNode *newNode, *last;
    if(l != NULL){
        newNode = (DLNode *)malloc(sizeof(DLNode));
        if(newNode != NULL){
            last = l->first;
            newNode->data = data;
            newNode->next = NULL;
            if(last != NULL){
                while(last->next != NULL){
                    last = last->next;
                }
                last->next = newNode;
            }else{
                l->first = newNode;
            }
            newNode->prev = last;
            return TRUE;
            
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da DLList e o retorna
---------------------------------------------------------------------------*/
void *dllRemoveFirst(DLList *l){
    DLNode *first, *next;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            first = l->first;
            next = first->next;
            if(next != NULL){
                next->prev = NULL;
            }
            l->first = next;
            data = first->data;
            free(first);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da DLList e o retorna
---------------------------------------------------------------------------*/
void *dllRemoveLast(DLList *l){
    DLNode *last, *prev;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            last = l->first;
            while(last->next != NULL){
                last = last->next;
            }
            prev = last->prev;
            if(prev != NULL){
                prev->next = NULL;
            }else{
                l->first = NULL;
            }
            data = last->data;
            free(last);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da DLList
---------------------------------------------------------------------------*/
void *dllGetFirst(DLList *l){
    if(l != NULL){
        l->cur = l->first;
        if(l->first != NULL){
            return l->cur->data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da DLList
---------------------------------------------------------------------------*/
void *dllGetNext(DLList *l){
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
** Remove o item que especifico da DLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *)){
    DLNode *spec, *prevSpec, *nextSpec;
    void *data;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            stat = cmp(key,spec->data);
            while(stat != TRUE && spec->next != NULL){
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if(stat == TRUE){
                prevSpec = spec->prev;
                nextSpec = spec->next;
                if(prevSpec != NULL){
                    prevSpec->next = nextSpec;
                }else{
                    l->first = nextSpec;
                }
                if(nextSpec != NULL){
                    nextSpec->prev = prevSpec;
                }
                data = spec->data;
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia de um item especifico da DLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *dllGetSpec(DLList *l, void *key, int (*cmp)(void *, void *)){
    DLNode *spec;
    void *data;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            spec = l->first;
            stat = cmp(key,spec->data);
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
** Retorna o número de itens que estão na Dllist
---------------------------------------------------------------------------*/
int dllNumElms(DLList *l){
    DLNode *cur;
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
** libera todos os nós da uma DLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int dllClear( DLList *l, int (*freeDat)(void *)){

    return FALSE;
}

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
DLList *dllContatOrdNew( DLList *l1, DLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
DLList *dllContatOrd( DLList *l1, DLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
int dllContido( DLList *l1, DLList *l2, int (*cmp)(void *, void *)){

    return FALSE;
}

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
DLList *dllUniao( DLList *l1, DLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
DLList *dllIntersecao( DLList *l1, DLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

#endif
