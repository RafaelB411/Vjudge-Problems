#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int elem;
    struct Node *next;
} Node;

Node* createNode(int elemval, Node* nextval) {
    Node *ntemp = (Node*) malloc(1 * sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->elem = elemval;
    ntemp->next = nextval;
    return ntemp;
}

typedef struct Stack {
    Node *top;
    int size;
} Stack;

Stack createStack() {
    Stack stemp;
    stemp.size = 0;
    stemp.top = createNode(1002, NULL);
    return stemp;
}

void clearStack(Stack* pilha) {
    Node *ntemp;
    while(pilha->top != NULL) {
        ntemp = pilha->top;
        pilha->top = pilha->top->next;
        free(ntemp);
    }
    pilha->size = 0;
}

void pushElem(int elemval, Stack* pilha) {
    pilha->top = createNode(elemval, pilha->top);
    (pilha->size)++;
}

void popElem(Stack* pilha) {
    if(pilha->size == 0) printf("Pilha vazia\n");
    else {
        Node *ntemp;
        ntemp = pilha->top;
        pilha->top = pilha->top->next;
        free(ntemp);
        pilha->size--;
    }
}

int main() {
    int numcars, *parade, starter = 0;
    Stack pilha;

    scanf("%d", &numcars);
    while(numcars!=0) {
        pilha = createStack();
        parade = (int*) calloc(numcars, sizeof(int));

        for(int i=0; i<numcars; i++)
            scanf("%d", &parade[i]);

        for(int i=0; i<numcars-1; i++) {
            if(parade[i] == 1) starter = 1;
            if(parade[i]>parade[i+1] || parade[i]>i+1 || !starter)
                pushElem(parade[i], &pilha);
            if(parade[i+1] == pilha.top->elem-1) popElem(&pilha);
        }

        if(pilha.size == 0) printf("yes\n");
        else printf("no\n");

        clearStack(&pilha);
        free(parade);
        scanf("%d", &numcars);
    }

    return 0;
}