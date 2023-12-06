#include "cDlList.h"
#include "cSlList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>

#define FALSE 0
#define TRUE 1

typedef struct aluno {
char nome[30]; float nota; int matricula;
} Aluno;

int QueryAlunoNota(void *b, void *a){
    Aluno *pa; float *pn;
    pa = (Aluno *) a;
    pn = (float *) b;
    if( pa->nota == *pn){
        return TRUE;
    } else{
        return FALSE;
    }
}

int QueryAlunoNome(void *b, void *a){
    Aluno *pa; char *pnome;
    pa = (Aluno *) a;
    pnome = (char *) b;
    if( strcmp(pa->nome, pnome) == 0){
        return TRUE;
    } else {
        return FALSE;
    }
}

int QueryAlunoMatricula(void *b, void *a){
    Aluno *pa; int *pn;
    pa = (Aluno *) a;
    pn = (int *) b;
    if( pa->matricula == *pn){
        return TRUE;
    } else{
        return FALSE;
    }
}


int lerInteiro(){
    int num;
    while (scanf("%d", &num) != 1){
        static char temp[256];
        fgets(temp, sizeof(temp), stdin);
        printf("\nNumero invalido\n");
        printf("Digite um numero: ");
    }
    return num;
}

float lerFloat(){
    float num;
    while (scanf("%f", &num) != 1){
        static char temp[256];
        fgets(temp, sizeof(temp), stdin);
        printf("\nNumero invalido\n");
        printf("Digite um numero: ");
    }
    return num;
}
/*
int inserirAluno(SLList * l){
    Aluno *aluno;
    if(l != NULL){
        aluno = (Aluno *)malloc(sizeof(Aluno));
        printf("Insira o nome do aluno: ");
        scanf("%s", &(aluno->nome));

        printf("Insira a nota do aluno: ");
        aluno->nota = lerFloat();

        printf("Insira a matricula do aluno: ");
        aluno->matricula = lerInteiro();

        sllInsertAsFirst(l,(void *) aluno);
        return TRUE;
    }
    return FALSE;

}

SLList * criarList(){
    SLList *l;
    l = sllCreate();
    return l;
}

int printAluno(Aluno * a){
    if(a != NULL){
        printf("-------------------\n");
        printf("Aluno\n");
        printf("Nome: %s\n", a->nome);
        printf("Nota: %f\n", a->nota);
        printf("Matricula: %d\n", a->matricula);
        printf("-------------------\n");
        return TRUE;
    }
    return FALSE;
}

int consultarAlunoNome(SLList * l){
    char pnome[30] = "";
    Aluno * aluno;
    if(l != NULL){
        printf("Insira o nome de procura: ");
        scanf("%s",&(pnome));
        aluno = (Aluno  *)sllGetSpec(l,(void *) pnome,QueryAlunoNome);
        if(aluno != NULL){
            printAluno(aluno);
            return TRUE;
        }
        printf("nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int consultarAlunoNota(SLList * l){
    float pnota;
    Aluno * aluno;
    if(l != NULL){
        printf("Insira o nota de procura: ");
        pnota = lerFloat();
        aluno = (Aluno *)sllGetSpec(l,(void *) &pnota,QueryAlunoNota);
        if(aluno != NULL){
            printAluno(aluno);
            return TRUE;
        }
        printf("nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int consultarAlunoMatricula(SLList * l){
    int pmatricula;
    Aluno * aluno;
    if(l != NULL){
        printf("Insira o matricula de procura: ");
        pmatricula = lerInteiro();
        aluno = (Aluno *)sllGetSpec(l,(void *) &pmatricula,QueryAlunoMatricula);
        if(aluno != NULL){
            printAluno(aluno);
            return TRUE;
        }
        printf("nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int removerAlunoNome(SLList * l){
    char pnome[30] = "";
    Aluno *aluno;
    if(l != NULL){
        printf("Insira o nome de procura: ");
        scanf("%s",&(pnome));
        aluno = (Aluno *)sllRemoveSpec(l,(void *) pnome,QueryAlunoNome);
        if(aluno != NULL){
            printf("-------------------------\n");
            printf("Aluno %s removido da lista\n", aluno->nome);
            printf("-------------------------\n");
            free(aluno);
            return TRUE;
        }
        printf("Nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int removerAlunoNota(SLList * l){
    float pnota;
    Aluno * aluno;
    if(l != NULL){
        printf("Insira o nota de procura: ");
        pnota = lerFloat();
        aluno = (Aluno *)sllRemoveSpec(l,(void *) &pnota,QueryAlunoNota);
        if(aluno != NULL){
            printf("-------------------------\n");
            printf("Aluno %s removido da lista\n", aluno->nome);
            printf("-------------------------\n");
            free(aluno);
            return TRUE;
        }
        printf("Nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int removerAlunoMatricula(SLList * l){
    int pmatricula;
    Aluno * aluno;
    if(l != NULL){
        printf("Insira o matricula de procura: ");
        pmatricula = lerInteiro();
        aluno = (Aluno *)sllRemoveSpec(l,(void *) &pmatricula,QueryAlunoMatricula);
        if(aluno != NULL){
            printf("-------------------------\n");
            printf("Aluno %s removido da lista\n", aluno->nome);
            printf("-------------------------\n");
            free(aluno);
            return TRUE;
        }
        printf("Nao foi encontrado o aluno\n");
    }
    return FALSE;
}

int listarItensLista(SLList * l){
    Aluno * aluno;
    if(l != NULL){
        printf("Itens da Lista\n");
        aluno = (Aluno *)sllGetFirst(l);
        while(aluno != NULL){
            printAluno(aluno);
            aluno = (Aluno *)sllGetNext(l);
        }
        return TRUE;
    }
    printf("Nao foi possível listar da Lista\n");
    return FALSE;
}

int esvaziarList(SLList * l){
    Aluno * aluno;
    if(l != NULL){
        aluno = (Aluno *)sllRemoveFirst(l);
        while(aluno != NULL){
            free(aluno);
            aluno = (Aluno *)sllRemoveFirst(l);
        }
        printf("Lista esvaziado com sucesso\n");
        return TRUE;
    }
    printf("Nao foi possível esvaziar o lista\n");
    return FALSE;
}
*/

int compara(void *key, void *data){
    int *n = (int *) key;
    int *dat = (int *) data;
    if(n == dat){
        return TRUE;
    }
    return FALSE;
}

int compara2(void *a, void *b){
    int *n1 = (int *) a;
    int *n2 = (int *) b;
    if(n1 == n2){
        return 0;
    }else if(n1 < n2){
        return (-1);
    }
    return 1;
}

int printarList(CSLList *lista){
    int i, *n;
    if(lista != NULL){
        n = (int *)csllGetFirst(lista);
        if(n != NULL){
            for(i = 0; i < 10; i++){
                printf("Número da posição [%d]: %d\n", i, n);
                n = (int *)csllGetNext(lista);
            }
            return TRUE;
        }
        printf("Lista vazia\n");
    }
    return FALSE;
}

int liberaMemoria(void *dat){
    return TRUE;
}

int listaContida(CSLList *lista1, CSLList *lista2){
    int stat;
    if(lista1 != NULL && lista2 != NULL){
        stat = csllContido(lista1, lista2, compara);
        if(stat == TRUE){
            printf("A Primeira Lista está contida na Segunda Lista.\n");
        }else{
            printf("A Primiera Lista não está contida na Segunda Lista.\n");
        }
        return TRUE;
    }
    printf("Uma das duas listas é igual a NULL\n");
    return FALSE;
}

int main(){
    /*                                                                        
    CDLList *dlist;

    CSLList *slist;
    int i, *n;
    
    dlist = cdllCreate();
    cdllInsertAsLast(dlist, (void *) 2);
    cdllInsertAsFirst(dlist, (void *) 3);
    cdllInsertAsLast(dlist, (void *) 1);
    cdllInsertAfterSpec(dlist, (void *) 4, (void *) 2, compara);
    cdllInsertBeforeSpec(dlist, (void *) 6, (void *) 5, compara);
    cdllInsertBeforeSpec(dlist, (void *) 5, (void *) 4, compara);
    n = (int *) cdllGetFirst(dlist);
    for(i = 0; i < 7; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) cdllGetNext(dlist);
    }
    printf("-------------------------------\n");
    cdllRemoveLast(dlist);
    n = (int *) cdllGetFirst(dlist);
    for(i = 0; i < 7; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) cdllGetNext(dlist);
    }
    printf("-------------------------------\n");
    cdllRemoveFirst(dlist);
    n = (int *) cdllGetFirst(dlist);
    for(i = 0; i < 7; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) cdllGetNext(dlist);
    }
    cdllRemoveFirst(dlist);
    cdllRemoveFirst(dlist);
    cdllRemoveFirst(dlist);
    cdllDestroy(dlist);*/
    //setlocale(LC_ALL, "Portuguese_Brazil");
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    slist3 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsLast(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 6);
    csllInsertAsLast(slist, (void *) 14);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsLast(slist2, (void *) 3);
    csllInsertAsLast(slist2, (void *) 6);
    csllInsertAsLast(slist2, (void *) 10);
    csllInsertAsLast(slist2, (void *) 14);
    csllInsertAsLast(slist2, (void *) 15);

    printf("Inseriu os elementos na segunda lista\n");

    //slist3 = csllUniao(slist, slist2, compara);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    slist3 = csllConcatOrdNew(slist, slist2, compara2);

    printf("Remoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3);

    return 0;
}

    /*  *********************************************                Teste da função de Uniao e de liberar todos os nós                *********************************************
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsFirst(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 1);
    csllInsertAfterSpec(slist, (void *) 4, (void *) 2, compara);
    csllInsertBeforeSpec(slist, (void *) 6, (void *) 4, compara);
    csllInsertBeforeSpec(slist, (void *) 5, (void *) 4, compara);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsFirst(slist2, (void *) 55);
    csllInsertAsLast(slist2, (void *) 21);
    csllInsertAfterSpec(slist2, (void *) 4, (void *) 2, compara);
    printf("Inseriu os elementos na segunda lista\n");

    slist3 = csllUniao(slist, slist2, compara);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllRemoveFirst(slist);
    csllRemoveFirst(slist2);
    csllRemoveFirst(slist3);
    csllRemoveLast(slist);
    csllRemoveLast(slist2);
    csllRemoveLast(slist3);
    printf("Remoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3);*/
    
    /*  *********************************************             Teste da função de Interseção e de liberar todos os nós              *********************************************
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsFirst(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 1);
    csllInsertAfterSpec(slist, (void *) 4, (void *) 2, compara);
    csllInsertBeforeSpec(slist, (void *) 6, (void *) 4, compara);
    csllInsertBeforeSpec(slist, (void *) 5, (void *) 4, compara);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsFirst(slist2, (void *) 6);
    csllInsertAsLast(slist2, (void *) 21);
    csllInsertAfterSpec(slist2, (void *) 4, (void *) 2, compara);
    printf("Inseriu os elementos na segunda lista\n");

    slist3 = csllIntersecao(slist, slist2, compara);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllRemoveFirst(slist);
    csllRemoveFirst(slist2);
    csllRemoveFirst(slist3);
    csllRemoveLast(slist);
    csllRemoveLast(slist2);
    csllRemoveLast(slist3);
    printf("Remoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3);*/

    /*  *********************************************                       Teste da função de l1 contido em l2                        *********************************************
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    slist3 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsFirst(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 1);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsFirst(slist2, (void *) 3);
    csllInsertAsLast(slist2, (void *) 11);
    csllInsertAsLast(slist2, (void *) 21);
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsFirst(slist2, (void *) 6);
    printf("Inseriu os elementos na segunda lista\n");

    csllInsertAsLast(slist3, (void *) 2);
    csllInsertAsFirst(slist3, (void *) 3);
    csllInsertAsFirst(slist3, (void *) 2);
    csllInsertAsFirst(slist3, (void *) 3);
    csllInsertAsLast(slist3, (void *) 1);
    csllInsertAfterSpec(slist3, (void *) 4, (void *) 1, compara);
    csllInsertAsFirst(slist3, (void *)7);
    csllInsertAsFirst(slist3, (void *)10);
    csllInsertAsLast(slist3, (void *)1);
    printf("Inseriu os elementos na terceira lista\n");

    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);
    
    printf("\nPrimeira lista = List1; Segunda Lista = Lista 2\n");
    listaContida(slist, slist2);

    printf("\nPrimeira lista = List1; Segunda Lista = Lista 3\n");
    listaContida(slist, slist3);

    csllRemoveFirst(slist);
    csllRemoveFirst(slist2);
    csllRemoveFirst(slist3);
    csllRemoveLast(slist);
    csllRemoveLast(slist2);
    csllRemoveLast(slist3);
    printf("\nRemoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("\n|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3);*/

    /*  ********************************************* Teste da função de contatenar duas lista ordenadas, mas sem criar uma nova lista *********************************************
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    slist3 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsLast(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 6);
    csllInsertAsLast(slist, (void *) 14);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsLast(slist2, (void *) 3);
    csllInsertAsLast(slist2, (void *) 6);
    csllInsertAsLast(slist2, (void *) 10);
    csllInsertAsLast(slist2, (void *) 11);
    csllInsertAsLast(slist2, (void *) 13);

    printf("Inseriu os elementos na segunda lista\n");

    //slist3 = csllUniao(slist, slist2, compara);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    slist3 = csllConcatOrd(slist, slist2, compara2);

    printf("Remoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3); */

    /*  *********************************************  Teste da função de contatenar duas lista ordenadas, mas criando uma nova lista  *********************************************
    printf("------------------------------------CSLLIST------------------------------------\n");
    CSLList *slist, *slist2, *slist3;
    int i, *n;
    
    slist = csllCreate();
    slist2 = csllCreate();
    slist3 = csllCreate();
    printf("Criou as listas\n");
    csllInsertAsLast(slist, (void *) 2);
    csllInsertAsLast(slist, (void *) 3);
    csllInsertAsLast(slist, (void *) 6);
    csllInsertAsLast(slist, (void *) 14);
    
    printf("Inseriu os elementos na primeira lista\n");
    csllInsertAsLast(slist2, (void *) 2);
    csllInsertAsLast(slist2, (void *) 3);
    csllInsertAsLast(slist2, (void *) 6);
    csllInsertAsLast(slist2, (void *) 10);
    csllInsertAsLast(slist2, (void *) 14);
    csllInsertAsLast(slist2, (void *) 15);

    printf("Inseriu os elementos na segunda lista\n");

    //slist3 = csllUniao(slist, slist2, compara);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    slist3 = csllConcatOrdNew(slist, slist2, compara2);

    printf("Remoção dos primeiros e ultimos elementos\n");
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllClear(slist, liberaMemoria);
    csllClear(slist2, liberaMemoria);
    csllClear(slist3, liberaMemoria);
    printf("|----------Lista 1----------|\n");
    printarList(slist);
    
    printf("|----------Lista 2----------|\n");
    printarList(slist2);
    
    printf("|----------Lista 3----------|\n");
    printarList(slist3);

    csllDestroy(slist);
    csllDestroy(slist2);
    csllDestroy(slist3);
    */
