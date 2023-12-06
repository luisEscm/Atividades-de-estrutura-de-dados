#ifndef __CSLLIST_C
#define __CSLLIST_C
#include <stdlib.h> 
#include "cSlList.h"

struct SLNode {
    void *data;
    SLNode *next;
};

struct CSLList {
    SLNode *first;
    SLNode *cur;
};

/*------------------------------------------------------------------------
** Aloca um espaço de memoria para uma CSLList
---------------------------------------------------------------------------*/
CSLList *csllCreate(void){
    CSLList *l;
    l = (CSLList * ) malloc(sizeof(CSLList ));
    if ( l != NULL ) {
        l->first = NULL;
        return l;
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Desaloca o espaço da memoria onde a CSLList foi alocado se estiver vazio
---------------------------------------------------------------------------*/
int csllDestroy(CSLList *l){
    if ( l != NULL ) {
        if ( l->first == NULL ) {
            free (l);
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no começo da CSLList
---------------------------------------------------------------------------*/
int csllInsertAsFirst(CSLList *l, void *data){
    SLNode * newnode, *last;
    if ( l != NULL) {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if ( newnode != NULL ){
            newnode->data = data;
            if(l->first != NULL){
                newnode->next = l->first;
                last = l->first;
                while(last->next != l->first){
                    last = last->next;
                }
                last->next = newnode;
                l->first = newnode;
            }else{
                l->first = newnode;
                newnode->next = l->first;
            }
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item no fim da CSLList
---------------------------------------------------------------------------*/
int csllInsertAsLast(CSLList *l, void *data){
    SLNode *newnode, *last;
    if ( l != NULL ) {
        newnode = (SLNode *) malloc (sizeof(SLNode *));
        if ( newnode != NULL ) {
            newnode->data = data;

            if ( l->first == NULL ) {
                l->first = newnode;
            }else {
                last = l->first;
                while (last->next != l->first ) {
                    last = last->next;
                }
                last->next = newnode;
            }
            newnode->next = l->first;
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na primeira posição da CSLList e o retorna
---------------------------------------------------------------------------*/
void *csllRemoveFirst(CSLList *l){
    SLNode *first, *last; void *data;
    if ( l != NULL) {
        if ( l->first != NULL ) {
            first = l->first;
            data = first->data;
            last = l->first;
            while(last->next != l->first){
                last = last->next;
            }
            if(last == first){
                l->first = NULL;
            }else{
                l->first = first->next;
                last->next = l->first;
            }
            free(first);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Remove o item que estiver na ultima posição da CSLList e o retorna
---------------------------------------------------------------------------*/
void *csllRemoveLast(CSLList *l){
    SLNode *last,*prev;
    void *data;
    if(l != NULL){
        if(l->first != NULL){
            prev = l->first;
            last = prev->next;
            while(last->next != l->first){
                prev = last;
                last = last->next;
            }
            data = last->data;
            if(prev == last){
                l->first = NULL;
            }else{
                prev->next = last->next;
            }
            free(last);
            return data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na primeira posição da CSLList
---------------------------------------------------------------------------*/
void *csllGetFirst(CSLList *l){
    if(l != NULL){
        l->cur = l->first;
        if(l->first != NULL){
            return l->cur->data;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Devolve uma cópia do item que está na posição após o item cópiado anterior da CSLList
---------------------------------------------------------------------------*/
void *csllGetNext(CSLList *l){
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
** Inseri um item na K-ésima posição da CSLList, assumindo k == 0 como a primeira posição da lista
---------------------------------------------------------------------------*/
int csllInsertAsKesimo (CSLList *l, void *data, int k){
    SLNode *newnode, *spec, *prev;
    if(l != NULL && k >= 0){
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if(newnode != NULL){
            newnode->data = data;
            if(l->first != NULL){
                prev = l->first;
                spec = prev->next;
                if(k == 0){
                    while(spec != l->first){
                        prev = spec;
                        spec = spec->next;
                    }
                }else{
                    k--;
                    while(k > 0 && spec->next != l->first){
                        prev = spec;
                        spec = spec->next;
                        k--;
                    }
                }
                if(k == 0){
                    prev->next = newnode;
                    newnode->next = spec;
                    if(spec == l->first){
                        l->first = newnode;
                    }
                    return TRUE;
                }
            }else{
                if(k == 0){
                    newnode->next = newnode;
                    l->first = newnode;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item após um item especifico da CSLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int csllInsertAfterSpec (CSLList *l, void *data, void *key, int (*cmp)(void *, void *)){
    SLNode *newnode, *spec, *after;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            newnode = (SLNode *)malloc(sizeof(SLNode));
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
                    newnode->next = after;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Inseri um item antes de um item especifico da CSLList, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
int csllInsertBeforeSpec (CSLList *l, void *data, void *key, int (*cmp)(void *, void *)){
    SLNode *newnode, *spec, *prev;
    int stat;
    if(l != NULL){
        if(l->first != NULL){
            newnode = (SLNode *)malloc(sizeof(SLNode));
            if(newnode != NULL){
                newnode->data = data;
                prev = l->first;
                spec = prev->next;
                stat = cmp(key, spec->data);
                while(stat != TRUE && spec != l->first){
                    prev = spec;
                    spec = spec->next;
                    stat = cmp(key, spec->data);
                }
                if(stat == TRUE){
                    prev->next = newnode;
                    newnode->next = spec;
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
** Remove o item que especifico da CSLList e o retorna, utilizando uma função de comparação
** que é da seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *csllRemoveSpec(CSLList *l, void *key, int (*cmp)(void *, void *)){
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
** Devolve uma cópia de um item especifico da CSLList, utilizando uma função de comparação
** que fica de seguinte forma "cmp(void *key, void *data)"
---------------------------------------------------------------------------*/
void *csllGetSpec(CSLList *l, void *key, int (*cmp)(void *, void *)){
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
** Devolve uma cópia de um item especifico da CSLList que está na N-éssima posição,
** onde o 0 é a primeira posição, se o n form maior que o tamanho da lista retorna o ultimo item
---------------------------------------------------------------------------*/
void *csllGetNItem(CSLList *l, int n){
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
** Retorna o número de itens que estão na CSllist
---------------------------------------------------------------------------*/
int csllNumElms(CSLList *l)
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
** libera todos os nós da uma CSLList usando uma função para liberar os dados antes, que é do seguinte formato:
** "int freeDat(void * data)"
** onde ela retorna as seguintes informações:
**
** freeDat(data) == TRUE, se a data foi desalocada da memoria;
** freeDat(data) == FALSE, se a data não foi desalocada da memoria.
**
** Assumindo TRUE == 1, e FALSE == 0.
---------------------------------------------------------------------------*/
int csllClear( CSLList *l, int (*freeDat)(void *)){
    SLNode *cur, *next;
    if(l != NULL){
        if(l->first != NULL){
            cur = l->first;
            next = cur->next;
            freeDat(cur->data);
            free(cur);
            while(next != l->first){
                cur = next;
                next = next->next;
                freeDat(cur->data);
                free(cur);
            }
            l->first = NULL;
        }
        return TRUE;
    }
    return FALSE;
}

/*------------------------------------------------------------------------
** Contena duas CSLList ordenadas e retorna uma terceira CSLList que tem uma cópia de todos os
** elementos das duas CSLList mantendo a ordem.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
CSLList *csllConcatOrdNew( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    SLNode *cur1, *cur2, *last, *newnode;
    CSLList *l3;
    int stat;
    if(l1 != NULL && l2 != NULL){
        l3 = (CSLList *)malloc(sizeof(CSLList));
        if(l3 != NULL){
            l3->first = NULL;
            l3->cur = NULL;
            if(l1->first != NULL && l2->first != NULL){
                last = NULL;
                cur1 = l1->first;
                cur2 = l2->first;
                stat = cmp(cur1->data, cur2->data);
                newnode = (SLNode *)malloc(sizeof(SLNode));
                if(newnode != NULL){
                    if(stat <= 0){
                        newnode->data = cur1->data;
                        cur1 = cur1->next;
                    }else{
                        newnode->data = cur2->data;
                        cur2 = cur2->next;
                    }
                    newnode->next = newnode;
                    last = newnode;
                    l3->first = newnode;
                    while(cur1->next != l1->first && cur2->next != l2->first){
                        stat = cmp(cur1->data, cur2->data);
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            cur1 = l3->first;
                            while(cur1->next != l3->first){
                                cur2 = cur1;
                                cur1 = cur1->next;
                                free(cur2);
                            }
                            free(cur1);
                            free(l3);
                            return NULL;
                        }
                        if(stat <= 0){
                            newnode->data = cur1->data;
                            cur1 = cur1->next;
                        }else{
                            newnode->data = cur2->data;
                            cur2 = cur2->next;
                        }
                        newnode->next = l3->first;
                        last->next = newnode;
                        last = newnode;
                    }
                    stat = cmp(cur1->data, cur2->data);
                    if(cur1->next == l1->first){
                        while(stat > 0 && cur2->next != l2->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            cur2 = cur2->next;
                            stat = cmp(cur1->data, cur2->data);
                        }

                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            cur1 = l3->first;
                            while(cur1->next != l3->first){
                                cur2 = cur1;
                                cur1 = cur1->next;
                                free(cur2);
                            }
                            free(cur1);
                            free(l3);
                            return NULL;
                        }
                        if(stat <= 0){
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            while(cur2->next != l2->first){
                                newnode = (SLNode *)malloc(sizeof(SLNode));
                                if(newnode == NULL){
                                    cur1 = l3->first;
                                    while(cur1->next != l3->first){
                                        cur2 = cur1;
                                        cur1 = cur1->next;
                                        free(cur2);
                                    }
                                    free(cur1);
                                    free(l3);
                                    return NULL;
                                }
                                newnode->data = cur2->data;
                                newnode->next = l3->first;
                                last->next = newnode;
                                last = newnode;
                                cur2 = cur2->next;
                            }
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                //csllFree(l3);
                                return NULL;
                            }
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                        }else{
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                //csllFree(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                        }
                    }else{
                        while(stat < 0 && cur1->next != l1->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            cur1 = cur1->next;
                            stat = cmp(cur1->data, cur2->data);
                        }
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            cur1 = l3->first;
                            while(cur1->next != l3->first){
                                cur2 = cur1;
                                cur1 = cur1->next;
                                free(cur2);
                            }
                            free(cur1);
                            free(l3);
                            return NULL;
                        }
                        if(stat >= 0){
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            while(cur1->next != l1->first){
                                newnode = (SLNode *)malloc(sizeof(SLNode));
                                if(newnode == NULL){
                                    cur1 = l3->first;
                                    while(cur1->next != l3->first){
                                        cur2 = cur1;
                                        cur1 = cur1->next;
                                        free(cur2);
                                    }
                                    free(cur1);
                                    free(l3);
                                    return NULL;
                                }
                                newnode->data = cur1->data;
                                newnode->next = l3->first;
                                last->next = newnode;
                                last = newnode;
                                cur1 = cur1->next;
                            }
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                //csllFree(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                        }else{
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                //csllFree(l3);
                                return NULL;
                            }
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                        }
                    }
                }else{
                    free(l3);
                    return NULL;
                }
            }else{
                if(l1->first != NULL){
                    cur1 = l1->first;
                    newnode = (SLNode *)malloc(sizeof(SLNode));
                    if(newnode != NULL){
                        newnode->data = cur1->data;
                        newnode->next = newnode;
                        l3->first = newnode;
                        last = newnode;
                        cur1 = cur1->next;
                        while(cur1 != l1->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            cur1 = cur1->next;
                        }
                    }else{
                        free(l3);
                        return NULL;
                    }
                }else if(l2->first != NULL){
                    cur2 = l2->first;
                    newnode = (SLNode *)malloc(sizeof(SLNode));
                    if(newnode != NULL){
                        newnode->data = cur2->data;
                        newnode->next = newnode;
                        l3->first = newnode;
                        last = newnode;
                        cur2 = cur2->next;
                        while(cur2 != l2->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                cur1 = l3->first;
                                while(cur1->next != l3->first){
                                    cur2 = cur1;
                                    cur1 = cur1->next;
                                    free(cur2);
                                }
                                free(cur1);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            last->next = newnode;
                            last = newnode;
                            cur2 = cur2->next;
                        }
                    }else{
                        free(l3);
                        return NULL;
                    }
                }
            }
            return l3;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Contena duas CSLList ordenadas e retorna a primeira das CSLList com todos os elementos
** mantando a ordem  e removendo todos os elementos de segunda CSLList.
** Para verificar a ordem é utilizada uma função cmp que tem o seguinte formato:
** "int cmp(void *a, void *b)"
**
** O resultado esperado da função é o seguinte:
**
** cmp(a, b) > 0, se a > b;
** cmp(a, b) == 0, se a == b;
** cmp(a, b) < 0, se a < b.
---------------------------------------------------------------------------*/
CSLList *csllConcatOrd( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    SLNode *cur1, *cur2, *prev, *first;
    int stat;
    if(l1 != NULL && l2 != NULL){
        if(l1->first != NULL && l2->first != NULL){
            prev = NULL;
            cur1 = l1->first;
            cur2 = l2->first;
            stat = cmp(cur1->data, cur2->data);
            if(stat <= 0){
                first = l1->first;
                prev = cur1;
                cur1 = cur1->next;
            }else{
                first = l2->first;
                prev = cur2;
                cur2 = cur2->next;
            }
            while(cur1->next != l1->first && cur2->next != l2->first){
                stat = cmp(cur1->data, cur2->data);
                if(stat <= 0){
                    prev->next = cur1;
                    prev = cur1;
                    cur1 = cur1->next;
                }else{
                    prev->next = cur2;
                    prev = cur2;
                    cur2 = cur2->next;
                }
            }
            stat = cmp(cur1->data, cur2->data);

            if(cur1->next == l1->first){
                while(stat > 0 && cur2->next != l2->first){
                    prev->next = cur2;
                    prev = cur2;
                    cur2 = cur2->next;
                    stat = cmp(cur1->data, cur2->data);
                }
                if(stat <= 0){
                    prev->next = cur2;
                    cur1->next = cur2;
                    while(cur2->next != l2->first){
                        cur2 = cur2->next;
                    }
                    cur2->next = first;
                }else{
                    cur2->next = cur1;
                    cur1->next = first;
                }
            }else{
                while(stat < 0 && cur1->next != l1->first){
                    prev->next = cur1;
                    prev = cur1;
                    cur1 = cur1->next;
                    stat = cmp(cur1->data, cur2->data);
                }
                if(stat >= 0){
                    prev->next = cur2;
                    cur2->next = cur1;
                    while(cur1->next != l1->first){
                        cur1 = cur1->next;
                    }
                    cur1->next = first;
                }else{
                    cur1->next = cur2;
                    cur2->next = first;
                }
            }

            l1->first = first;
            l2->first = NULL;
            l2->cur = NULL;

            return l1;
        }else{
            if(l2->first != NULL){
                l1->first = l2->first;
            }
            return l1;
        }
    }
    return NULL;
}

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
int csllContido( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    SLNode *cur1, *cur2;
    int stat;
    if(l1 != NULL && l2 != NULL){
        if(l1->first != NULL && l2->first != NULL){
            cur1 = l1->first;
            cur2 = l2->first;
            stat = cmp(cur1->data, cur2->data);
            cur2 = cur2->next;
            while(cur2 != l2->first){
                if(stat == TRUE){
                    cur1 = cur1->next;
                    if(cur1 != l1->first){
                        stat = cmp(cur1->data, cur2->data);
                    }
                    while(stat != FALSE && cur1->next != l1->first && cur2->next != l2->first){
                        cur1 = cur1->next;
                        cur2 = cur2->next;
                        stat = cmp(cur1->data, cur2->data);
                    }
                    if(cur1->next == l1->first && stat == TRUE){
                        return TRUE;
                    }
                }
                cur1 = l1->first;
                stat = cmp(cur1->data, cur2->data);
                cur2 = cur2->next;
            }
            if(cur1->next == l1->first){
                return stat;
            }
        }
    }
    return FALSE;
}

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
int csllElemContido( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    SLNode *cur1, *cur2;
    int stat;
    if(l1 != NULL && l2 != NULL){
        if(l1->first != NULL && l2->first != NULL){
            cur1 = l1->first;
            cur2 = l2->first;
            stat = cmp(cur1->data, cur2->data);
            while(stat != FALSE && cur1->next != l1->first){
                stat = cmp(cur1->data, cur2->data);
                cur2 = cur2->next;
                while(stat == TRUE && cur2 != l2->first){
                    stat = cmp(cur1->data, cur2->data);
                    cur2 = cur2->next;
                }
                cur2 = l2->first;
            }
            return stat;
        }else if(l1->first == NULL){
            return TRUE;
        }
    }
    return FALSE;
}

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
/*CSLList *csllUniao( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    CSLList *l3;
    SLNode *cur1, *cur2, *newnode;
    int stat;
    if(l1 != NULL && l2 != NULL){
        l3 = (CSLList *)malloc(sizeof(CSLList));
        if(l3 != NULL){
            l3->first = NULL;
            l3->cur = NULL;
            if(l1->first != NULL && l2->first != NULL){
                cur1 = l1->first;
                newnode = (SLNode *)malloc(sizeof(SLNode));
                if(newnode != NULL){
                    newnode->data = cur1->data;
                    newnode->next = newnode;
                    l3->first = newnode;
                    cur2 = newnode;
                    cur1 = cur1->next;
                    while(cur1 != l1->first){
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            newnode = l3->first;
                            while(newnode->next != l3->first){
                                cur2= newnode;
                                newnode = newnode->next;
                                free(cur2);
                            }
                            free(newnode);
                            free(l3);
                            return NULL;
                        }
                        newnode->data = cur1->data;
                        newnode->next = l3->first;
                        cur2->next = newnode;
                        cur2 = newnode;
                        cur1 = cur1->next;
                    }
                    cur2 = l3->first;
                    cur1 = l2->first;
                    while(cur1->next != l2->first){
                        stat = cmp(cur2->data, cur1->data);
                        cur2 = cur2->next;
                        while(stat != TRUE && cur2 != l3->first){
                            stat = cmp(cur2->data, cur1->data);
                            cur2 = cur2->next;
                        }
                        if(stat == FALSE){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                newnode = l3->first;
                                while(newnode->next != l3->first){
                                    cur2 = newnode;
                                    newnode = newnode->next;
                                    free(cur2);
                                }
                                free(newnode);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            cur2->next = newnode;
                        }
                        cur1 = cur1->next;
                        cur2 = l3->first;
                    }
                    stat = cmp(cur2->data, cur1->data);
                    cur2 = cur2->next;
                    while(stat != TRUE && cur2 != l3->first){
                        stat = cmp(cur2->data, cur1->data);
                        cur2 = cur2->next;
                    }
                    if(stat == FALSE){
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            newnode = l3->first;
                            while(newnode->next != l3->first){
                                cur2 = newnode;
                                newnode = newnode->next;
                                free(cur2);
                            }
                            free(newnode);
                            free(l3);
                            return NULL;
                        }
                        newnode->data = cur1->data;
                        newnode->next = l3->first;
                        cur2->next = newnode;
                    }
                }else{
                    free(l3);
                    return NULL;
                }
            }else{
                if(l1->first != NULL){
                    cur1 = l1->first;
                    newnode = (SLNode *)malloc(sizeof(SLNode));
                    if(newnode != NULL){
                        newnode->data = cur1->data;
                        newnode->next = newnode;
                        l3->first = newnode;
                        cur2 = newnode;
                        cur1 = cur1->next;
                        while(cur1 != l1->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                newnode = l3->first;
                                while(newnode->next != l3->first){
                                    cur2= newnode;
                                    newnode = newnode->next;
                                    free(cur2);
                                }
                                free(newnode);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            cur2->next = newnode;
                            cur2 = newnode;
                            cur1 = cur1->next;
                        }
                    }else{
                        free(l3);
                        return NULL;
                    }
                }else{
                    if(l2->first != NULL){
                        cur1 = l2->first;
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode != NULL){
                            newnode->data = cur1->data;
                            newnode->next = newnode;
                            l3->first = newnode;
                            cur2 = newnode;
                            cur1 = cur1->next;
                            while(cur1 != l1->first){
                                newnode = (SLNode *)malloc(sizeof(SLNode));
                                if(newnode == NULL){
                                    newnode = l3->first;
                                    while(newnode->next != l3->first){
                                        cur2= newnode;
                                        newnode = newnode->next;
                                        free(cur2);
                                    }
                                    free(newnode);
                                    free(l3);
                                    return NULL;
                                }
                                newnode->data = cur1->data;
                                newnode->next = l3->first;
                                cur2->next = newnode;
                                cur2 = newnode;
                                cur1 = cur1->next;
                            }
                        }else{
                            free(l3);
                            return NULL;
                        }
                    }
                }
            }
            return l3;
        }
    }
    return NULL;
}*/

CSLList *csllUniao( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    CSLList *l3;
    SLNode *cur1, *cur2, *newnode;
    int stat;
    if(l1 != NULL && l2 != NULL){
        l3 = (CSLList *)malloc(sizeof(CSLList));
        if(l3 != NULL){
            l3->first = NULL;
            l3->cur = NULL;
            if(l1->first != NULL){
                cur1 = l1->first;
                newnode = (SLNode *)malloc(sizeof(SLNode));
                if(newnode != NULL){
                    newnode->data = cur1->data;
                    newnode->next = newnode;
                    l3->first = newnode;
                    cur2 = newnode;
                    cur1 = cur1->next;
                    while(cur1 != l1->first){
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            newnode = l3->first;
                            while(newnode->next != l3->first){
                                cur2= newnode;
                                newnode = newnode->next;
                                free(cur2);
                            }
                            free(newnode);
                            free(l3);
                            return NULL;
                        }
                        newnode->data = cur1->data;
                        newnode->next = l3->first;
                        cur2->next = newnode;
                        cur2 = newnode;
                        cur1 = cur1->next;
                    }
                }else{
                    free(l3);
                    return NULL;
                }
            }
            if(l2->first != NULL){
                newnode = cur2;
                cur1 = l1->first;
                cur2 = l2->first;
                if(cur1 != NULL){
                    while(cur2->next != l2->first){
                        stat = cmp(cur1->data, cur2->data);
                        cur1 = cur1->next;
                        while(stat != TRUE && cur1 != l1->first){
                            stat = cmp(cur1->data, cur2->data);
                            cur1 = cur1->next;
                        }
                        if(stat == FALSE){
                            cur1 = newnode;
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                newnode = l3->first;
                                while(newnode->next != l3->first){
                                    cur1 = newnode;
                                    newnode = newnode->next;
                                    free(cur1);
                                }
                                free(newnode);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur2->data;
                            newnode->next = l3->first;
                            cur1->next = newnode;
                        }
                        cur2 = cur2->next;
                        cur1 = l1->first;
                    }
                    stat = cmp(cur1->data, cur2->data);
                    cur1 = cur1->next;
                    while(stat != TRUE && cur1 != l1->first){
                        stat = cmp(cur1->data, cur2->data);
                        cur1 = cur1->next;
                    }
                    if(stat == FALSE){
                        cur1 = newnode;
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            newnode = l3->first;
                            while(newnode->next != l3->first){
                                cur2 = newnode;
                                newnode = newnode->next;
                                free(cur2);
                            }
                            free(newnode);
                            free(l3);
                            return NULL;
                        }
                        newnode->data = cur2->data;
                        newnode->next = l3->first;
                        cur1->next = newnode;
                    }
                }else{
                    cur1 = l2->first;
                    newnode = (SLNode *)malloc(sizeof(SLNode));
                    if(newnode != NULL){
                        newnode->data = cur1->data;
                        newnode->next = newnode;
                        l3->first = newnode;
                        cur2 = newnode;
                        cur1 = cur1->next;
                        while(cur1 != l2->first){
                            newnode = (SLNode *)malloc(sizeof(SLNode));
                            if(newnode == NULL){
                                newnode = l3->first;
                                while(newnode->next != l3->first){
                                    cur2= newnode;
                                    newnode = newnode->next;
                                    free(cur2);
                                }
                                free(newnode);
                                free(l3);
                                return NULL;
                            }
                            newnode->data = cur1->data;
                            newnode->next = l3->first;
                            cur2->next = newnode;
                            cur2 = newnode;
                            cur1 = cur1->next;
                        }
                    }else{
                        free(l3);
                        return NULL;
                    }
                }
            }
            return l3;
        }
    }
    return NULL;
}

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
CSLList *csllIntersecao( CSLList *l1, CSLList *l2, int (*cmp)(void *, void *)){
    CSLList *l3;
    SLNode *cur1, *cur2, *cur3, *newnode;
    int stat;
    if(l1 != NULL && l2 != NULL){
        l3 = (CSLList *)malloc(sizeof(CSLList));
        if(l3 != NULL){
            l3->first = NULL;
            l3->cur = NULL;
            if(l1->first != NULL && l2->first != NULL){
                cur3 = NULL;
                cur1 = l1->first;
                cur2 = l2->first;
                while(cur1->next != l1->first){
                    stat = cmp(cur1->data, cur2->data);
                    cur2 = cur2->next;
                    while(stat != TRUE && cur2 != l2->first){
                        stat = cmp(cur1->data, cur2->data);
                        cur2 = cur2->next;
                    }
                    if(stat == TRUE){
                        newnode = (SLNode *)malloc(sizeof(SLNode));
                        if(newnode == NULL){
                            if(l3->first != NULL){
                                newnode = l3->first;
                                while(newnode->next != l3->first){
                                    cur3 = newnode;
                                    newnode = newnode->next;
                                    free(cur3);
                                }
                                free(newnode);
                            }
                            free(l3);
                            return NULL;
                        }
                        newnode->data = cur1->data;
                        if(l3->first == NULL){
                            l3->first = newnode;
                            cur3 = l3->first;
                        }
                        newnode->next = l3->first;
                        cur3->next = newnode;
                        cur3 = newnode;
                    }
                    cur2 = l2->first;
                    cur1 = cur1->next;
                }
                stat = cmp(cur1->data, cur2->data);
                cur2 = cur2->next;
                while(stat != TRUE && cur2 != l2->first){
                    stat = cmp(cur1->data, cur2->data);
                    cur2 = cur2->next;
                }
                if(stat == TRUE){
                    newnode = (SLNode *)malloc(sizeof(SLNode));
                    if(newnode == NULL){
                        if(l3->first != NULL){
                            newnode = l3->first;
                            while(newnode->next != l3->first){
                                cur3 = newnode;
                                newnode = newnode->next;
                                free(cur3);
                            }
                            free(newnode);
                        }
                        free(l3);
                        return NULL;
                    }
                    newnode->data = cur1->data;
                    if(l3->first == NULL){
                        l3->first = newnode;
                        cur3 = l3->first;
                    }
                    newnode->next = l3->first;
                    cur3->next = newnode;
                }
            }
            return l3;
        }
    }
    return NULL;
}

/*------------------------------------------------------------------------
** Função que da free em uma lista sem se importar em dar free nos seus elementos
---------------------------------------------------------------------------*/
void csllFree(CSLList *l){
    SLNode *cur1, *cur2;
    if(l != NULL){
        if(l->first != NULL){
            cur1 = l->first;
            while(cur1->next != l->first){
                cur2 = cur1;
                cur1 = cur1->next;
                free(cur2);
            }
            free(cur1);
        }
        free(l);
    }
}

#endif
