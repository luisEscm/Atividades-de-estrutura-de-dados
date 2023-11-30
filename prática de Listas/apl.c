#include "cDlList.h"
#include "cSlList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){/*                                                                        
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
    cdllDestroy(dlist);
    printf("------------------------------------CSLLIST------------------------------------\n");
    slist = csllCreate();
    csllInsertAsLast(slist, (void *) 7);
    csllInsertAsFirst(slist, (void *) 8);
    csllInsertAsLast(slist, (void *) 6);
    csllInsertAfterSpec(slist, (void *) 9, (void *) 8, compara);
    csllInsertBeforeSpec(slist, (void *) 11, (void *) 10, compara);
    csllInsertBeforeSpec(slist, (void *) 10, (void *) 8, compara);

    n = (int *) csllGetFirst(slist);
    for(i = 0; i < 8; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) csllGetNext(slist);
    }
    printf("-------------------------------\n");
    csllRemoveLast(slist);
    n = (int *) csllGetFirst(slist);
    for(i = 0; i < 8; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) csllGetNext(slist);
    }
    printf("-------------------------------\n");
    csllRemoveFirst(slist);
    n = (int *) csllGetFirst(slist);
    for(i = 0; i < 8; i++){
        printf("Número da posicao [%d]: %d\n", i, n);
        n = (int *) csllGetNext(slist);
    }
    csllRemoveFirst(slist);
    csllRemoveFirst(slist);
    csllRemoveFirst(slist);
    csllDestroy(slist);*/

    CDLList *dlist, *dlist2;
    int i, *n;
    
    dlist = cdllCreate();
    dlist2 = dlist;
    cdllDestroy(dlist);
    //cdllInsertAsLast(dlist, (void *) 2);
    //cdllInsertAsFirst(dlist, (void *) 3);
    //cdllInsertAsLast(dlist, (void *) 1);
    //cdllInsertAfterSpec(dlist, (void *) 4, (void *) 2, compara);
    //cdllInsertBeforeSpec(dlist, (void *) 6, (void *) 5, compara);
    //cdllInsertBeforeSpec(dlist, (void *) 5, (void *) 4, compara);
    //n = (int *) cdllGetFirst(dlist);
    n = 0;
    for(i = 0; i < 7; i++){
        if(dlist == dlist2){
            printf("não deu\n");
            break;
        }
        printf("Número da posicao [%d]: %d\n", i, n);
        //n = (int *) cdllGetNext(dlist);
    }
    return 0;
}