#ifndef __CDLLIST_C
#define __CDLLIST_C
#include <stdlib.h> 
#include "cDlList.h"

struct DLNode {
    void *data;
    DLNode *next;
    DLNode *prev;
};

struct CDLList {
    DLNode *first;
    DLNode *cur;
};

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma CDLList
---------------------------------------------------------------------------*/
CDLList *cdllCreate(void){
    CDLList *l;
    l = (CDLList *)malloc(sizeof(CDLList));
    if(l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a CDLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int cdllDestroy(CDLList *l){
    if(l != NULL){
        if(l->first == NULL){
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no começo da CDLList
---------------------------------------------------------------------------*/
int cdllInsertAsFirst(CDLList *l, void *data){
    DLNode *newNode, *first, *last;
    if(l != NULL){
        newNode = (DLNode *)malloc(sizeof(DLNode));
        if(newNode != NULL){
            newNode->data = data; 
            if(l->first != NULL){
                first = l->first;
                last  = first->prev;
                
                first->prev = newNode;
                newNode->next = first;

                last->next = newNode;
                newNode->prev = last;
            }else{
                newNode->next = newNode;
                newNode->prev = newNode;
            }
            l->first = newNode;
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no fim da CDLList
---------------------------------------------------------------------------*/
int cdllInsertAsLast(CDLList *l, void *data){
    DLNode *newNode, *last, *first;
    if(l != NULL){
        newNode = (DLNode *)malloc(sizeof(DLNode));
        if(newNode != NULL){
            newNode->data = data; 
            if(l->first != NULL){
                first = l->first;
                last  = first->prev;
                
                first->prev = newNode;
                newNode->next = first;

                last->next = newNode;
                newNode->prev = last;
            }else{
                newNode->next = newNode;
                newNode->prev = newNode;
                l->first = newNode;
            }
            return TRUE;
            
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CDLList e o retorna
---------------------------------------------------------------------------*/
void *cdllRemoveFirst(CDLList *l){
    DLNode *first, *last, *next;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            first = l->first;
            next = first->next;
            last = first->prev;
            if(first == next){
                l->first = NULL;
            }else{
                l->first = next;
                last->next = next;
                next->prev = last;
            }
            data = first->data;
            free(first);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CDLList e o retorna
---------------------------------------------------------------------------*/
void *cdllRemoveLast(CDLList *l){
    DLNode *first, *last, *prev;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            first = l->first;
            last = first->prev;
            prev = last->prev;
            if(last == prev){
                l->first = NULL;
            }else{
                prev->next = first;
                first->prev = prev;
            }
            data = last->data;
            free(last);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da CDLList
---------------------------------------------------------------------------*/
void *cdllGetFirst(CDLList *l){
    if(l != NULL){
        l->cur = l->first;
        if(l->first != NULL){
            return l->cur->data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da CDLList
---------------------------------------------------------------------------*/
void *cdllGetNext(CDLList *l){
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
** Inseri um item na K-ésima posição da CDLList, assumindo k == 0 como a primeira posição da lista
---------------------------------------------------------------------------*/
int cdllInsertAsKesimo (CDLList *l, void *data, int k){
    DLNode *newnode, *spec, *prev;
    if(l != NULL){
        newnode = (DLNode *)malloc(sizeof(DLNode));
        if(newnode != NULL){
            newnode->data = data;
            if(l->first != NULL){
                spec = l->first;
                while(k > 0 && spec->next != l->first){
                    spec = spec->next;
                    k--;
                }
                if(k == 0){
                    prev = spec->prev;
                    newnode->next = spec;
                    spec->prev = newnode;

                    newnode->prev = prev;
                    prev->next = newnode;
                    if(spec == l->first){
                        l->first = newnode;
                    }
                    return TRUE;
                }
            }else{
                if(k == 0){
                    newnode->next = newnode;
                    newnode->prev = newnode;
                    l->first = newnode;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item após um item especifico da CDLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int cdllInsertAfterSpec (CDLList *l, void *data, void *key, int (*cmp)(void *, void *)){
    DLNode *newnode, *spec, *after;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            newnode = (DLNode *)malloc(sizeof(DLNode));
            if(newnode != NULL){
                newnode->data = data;
                spec = l->first;
                stat = cmp(key, spec->data);
                while(stat != TRUE && spec->next != l->first){
                    spec = spec->next;
                    stat = cmp(key, spec->data);
                }
                if(stat == TRUE){
                    after = spec->next;
                    spec->next = newnode;
                    newnode->prev = spec;

                    after->prev = newnode;
                    newnode->next = after;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item antes de um item especifico da CDLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int cdllInsertBeforeSpec (CDLList *l, void*data, void *key, int (*cmp)(void *, void *)){
    DLNode *newnode, *spec, *prev;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            newnode = (DLNode *)malloc(sizeof(DLNode));
            if(newnode != NULL){
                newnode->data = data;
                spec = l->first;
                stat = cmp(key, spec->data);
                while(stat != TRUE && spec->next != l->first){
                    spec = spec->next;
                    stat = cmp(key, spec->data);
                }
                if(stat == TRUE){
                    prev = spec->prev;
                    spec->prev = newnode;
                    newnode->next = spec;

                    prev->next = newnode;
                    newnode->prev = prev;
                    if(spec == l->first){
                        l->first = newnode;
                    }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Remove o item que especifico da CDLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *cdllRemoveSpec(CDLList *l, void *key, int (*cmp)(void *, void *)){
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
** Devolve uma cópia de um item especifico da CDLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *cdllGetSpec(CDLList *l, void *key, int (*cmp)(void *, void *)){
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
** Retorna o número de itens que estão na CDllist
---------------------------------------------------------------------------*/
int cdllNumElms(CDLList *l){
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
** libera todos os nós da uma CDLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
---------------------------------------------------------------------------*/
int cdllClear( CDLList *l, int (*freeDat)(void *)){

    return FALSE;
}

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
CDLList *cdllContatOrdNew( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
CDLList *cdllContatOrd( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
int cdllContido( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *)){

    return FALSE;
}

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
CDLList *cdllUniao( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

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
CDLList *cdllIntersecao( CDLList *l1, CDLList *l2, int (*cmp)(void *, void *)){

    return NULL;
}

#endif
