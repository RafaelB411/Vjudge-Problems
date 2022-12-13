#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char elem;
    struct Node *next; 
} Node;

Node* createNode(char elemval, Node *nextval) {
    Node *ntemp = (Node*) malloc(1 * sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->elem = elemval;
    ntemp->next = nextval;
    return ntemp;
}

typedef struct List {
    Node *head;
    Node *curr;
    Node *tail;
    long long int size;
} List;

List createList() {
    List ltemp;
    ltemp.head = createNode('-', NULL);
    ltemp.curr = ltemp.head;
    ltemp.tail = ltemp.head;
    ltemp.size = 0;
    return ltemp;
}

void clearList(List *lista) {
    while(lista->head != NULL) {
        lista->curr = lista->head;
        lista->head = lista->curr->next;
        free(lista->curr);
    }
    lista->size = 0;
}

void insertElem(List *lista, char elem) {
    lista->curr->next = createNode(elem, lista->curr->next);
    if(lista->curr == lista->tail) lista->tail = lista->curr->next;
    lista->curr = lista->curr->next;
    lista->size++;
}

int main() {
    List lista;
    char key;

    while(scanf("%c", &key)!=EOF) {
        lista = createList();
        while(key != '\n') {
            if(key == '[') { lista.curr = lista.head; }
            else if(key == ']') { lista.curr = lista.tail; }
            else { insertElem(&lista, key); }
            scanf("%c", &key);
        }

        lista.curr = lista.head;
        while(lista.curr != lista.tail) {
            printf("%c", lista.curr->next->elem);
            lista.curr = lista.curr->next;
        }
        if(lista.size != 0) printf("\n");

        clearList(&lista);
    }

    return 0;
}