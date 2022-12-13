#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long long int key;
    struct Node* left;
    struct Node* right;
    long long int height;
    long long int subcnt;
} Node;

Node* createNode(long long int key) {
    Node* ntemp = (Node*) malloc(1*sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->key = key;
    ntemp->left = NULL;
    ntemp->right = NULL;
    ntemp->height = 0;
    ntemp->subcnt = 1;
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

int max(int x, int y) { if(x>y) return x; else return y; }

int height(Node* root) {
    if(root==NULL) return -1;
    else return root->height;
}

int subtree(Node* root) {
    if(root==NULL) return 0;
    else return root->subcnt;
}

int getBalance(Node* root) {
    if(root==NULL) return 0;
    else return height(root->left)-height(root->right);
}

Node* rightRotate(Node* root) {
    Node* left = root->left;
    Node* lright = left->right;
    left->right = root;
    root->left = lright;
    root->height = max(height(root->left), height(root->right)) + 1;
    left->height = max(height(left->left), height(left->right)) + 1;
    root->subcnt = subtree(root->left) + subtree(root->right) + 1;
    left->subcnt = subtree(left->left) + subtree(left->right) + 1;
    return left;
}

Node* leftRotate(Node* root) {
    Node* right = root->right;
    Node* rleft = right->left;
    right->left = root;
    root->right = rleft;
    root->height = max(height(root->left), height(root->right)) + 1;
    right->height = max(height(right->left), height(right->right)) + 1;
    root->subcnt = subtree(root->left) + subtree(root->right) + 1;
    right->subcnt = subtree(right->left) + subtree(right->right) + 1;
    return right;
}

Node* insertHelp(Node* root, long long int key) {
    if(root == NULL) return createNode(key);
    else if(root->key > key) root->left = insertHelp(root->left, key);
    else root->right = insertHelp(root->right, key);

    root->height = 1 + max(height(root->right), height(root->left));
    root->subcnt = 1 + subtree(root->right) + subtree(root->left);
    int balance = getBalance(root);
    if(balance<-1 && key>=root->right->key) { return leftRotate(root); }
    if(balance>1 && key<root->left->key) { return rightRotate(root); }
    if(balance>1 && key>=root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && key<root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void insertElem(BSTree* tree, long long int key) {
    tree->root = insertHelp(tree->root, key);
    tree->cnt++;
}

int findHelp(Node* root, long long int key, long long int index) {
    if(root == NULL) return -1;
    else if(root->key > key) { index -= subtree(root->right)+1; return findHelp(root->left, key, index); }

    if(root->key == key) { index -= subtree(root->right); return index; }

    if(root->key < key) { return findHelp(root->right, key, index); }
}

int findElem(BSTree tree, long long int key, long long int cnt) {
    return findHelp(tree.root, key, tree.cnt);
}

int main() {
    long long int opnum, key, index, cnt;
    int oper;
    BSTree tree;

    tree = createTree();

    scanf("%lld", &opnum);
    for(int i=0; i<opnum; i++) {
        scanf("%d %lld", &oper, &key);
        index=0;
        switch (oper)
        {
        case 1:
            insertElem(&tree, key);
            break;
        case 2:
            index = findElem(tree, key, cnt);
            if(index == -1) printf("Data tidak ada\n");
            else printf("%lld\n", index);
            break;
        }
    }

    clearTree(&tree);

    return 0;
}