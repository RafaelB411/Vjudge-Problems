#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long long int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(long long int key) {
    Node* ntemp = (Node*) malloc(1*sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->key = key;
    ntemp->left = NULL;
    ntemp->right = NULL;
    return ntemp;
}

typedef struct BSTree {
    Node* root;
    int cnt;
} BSTree;

BSTree createTree() {
    BSTree ttemp;
    ttemp.root = NULL;
    ttemp.cnt = 0;
    return ttemp;
}

void clearHelp(Node* root) {
    if(root==NULL) return;
    clearHelp(root->left);
    clearHelp(root->right);
    free(root);
}

void clearTree(BSTree *tree) {
    clearHelp(tree->root);
}

Node* insertHelp(Node* root, long long int key) {
    if(root == NULL) return createNode(key);
    else if(root->key > key) root->left = insertHelp(root->left, key);
    else if(root->key < key) root->right = insertHelp(root->right, key);
    return root;
}

void insertElem(BSTree* tree, long long int key) {
    tree->root = insertHelp(tree->root, key);
    tree->cnt++;
}

void postorder(Node* root) {
    if(root!=NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%lld\n", root->key);
    }
}

int main() {
    long long int key;
    BSTree tree;

    tree = createTree();

    while(scanf("%lld", &key)!=EOF)
        insertElem(&tree, key);
    
    postorder(tree.root);

    clearTree(&tree);

    return 0;
}