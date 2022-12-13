#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Graph {
    bool *mark;
    bool **matrix;
    int edge;
    int tam;
} Graph;

Graph createGraph(int tam) {
    Graph gtemp;

    gtemp.mark = (bool*) calloc(tam, sizeof(bool));
    if(gtemp.mark==NULL) { printf("Problema na alocaçao\n"); exit(-1); }

    gtemp.matrix = (bool**) calloc(tam, sizeof(bool*));
    if(gtemp.matrix==NULL) { free(gtemp.mark); printf("Problema na alocaçao\n"); exit(-1); }
    for(int i=0; i<tam; i++) {
        gtemp.matrix[i] = (bool*) calloc(tam, sizeof(bool));
        if(gtemp.matrix[i]==NULL) { free(gtemp.mark); free(gtemp.matrix); printf("Problema na alocaçao\n"); exit(-1); }
    }

    gtemp.edge = 0;
    gtemp.tam = tam;

    return gtemp;
}

void clearGraph(Graph *g) {
    free(g->mark);
    for(int i=0; i<g->tam; i++) free(g->matrix[i]);
    free(g->matrix);
    g->edge = 0;
    g->tam = 0;
}

void setEdge(Graph* g, int i, int j, int weight) {
    if(weight==0) printf("error404\n");
    if(!g->matrix[i][j]) g->edge++;
    g->matrix[i][j] = true;
}

void setMark(Graph* g, int vertx, bool value) {
    g->mark[vertx] = value;
}

bool getMark(Graph g, int vertx) {
    return g.mark[vertx];
}

int nextVertx(Graph g, int start, int vertx) {
    for(int i=vertx+1; i<g.tam; i++) {
        if(g.matrix[start][i]) return i;
    }
    return g.tam;
}

int first(Graph g, int vertex) {
    for(int i=0; i<g.tam; i++) {
        if(g.matrix[vertex][i]) return i;
    }
    return g.tam;
}

typedef struct Stack {
    int maxsize;
    int top;
    int *listArray;
} Stack;

Stack createStack(int size) {
    Stack stemp;
    stemp.maxsize = size;
    stemp.top = 0;
    stemp.listArray = (int*) calloc(size, sizeof(int));
    return stemp;
}

void clearStack(Stack *stack) {
    free(stack->listArray);
    stack->maxsize = 0;
}

void pushElem(int elem, Stack *stack) {
    if(stack->top == stack->maxsize) printf("A pilha esta cheia\n");
    else {
        stack->listArray[stack->top] = elem;
        (stack->top)++;
    }
}

int popElem(Stack *stack) {
    int elem;
    if(stack->top == 0) {
        printf("A pilha esta vazia\n");
        return 0;
    }
    else {
        elem = stack->listArray[(stack->top)-1];
        (stack->top)--;
        return elem;
    }
}

void toposort(Graph g, int vertx, Stack* s) {
    setMark(&g, vertx, true);
    int start = first(g, vertx);
    while(start<g.tam) {
        if(!getMark(g, start)) toposort(g, start, s);
        start = nextVertx(g, vertx, start);
    }
    pushElem(vertx, s);
}

void graphTraverse(Graph g, Stack *s) {
    for(int vertx=0; vertx<g.tam; vertx++) {
        setMark(&g, vertx, false);
    }
    for(int vertx=0; vertx<g.tam; vertx++) {
        if(!getMark(g, vertx)) toposort(g, vertx, s);
    }
}

int main() {
    int nvert, nedge, head, end, top;
    Graph g;
    Stack s;

    scanf("%d %d", &nvert, &nedge);
    g = createGraph(nvert);
    s = createStack(nvert);

    for(int i=0; i<nedge; i++) {
        scanf("%d %d", &head, &end);
        setEdge(&g, head, end, 1);
    }

    graphTraverse(g, &s);
    
    while(s.top!=0) {
        top = popElem(&s);
        printf("%d\n", top);
    }

    clearGraph(&g);

    return 0;
}