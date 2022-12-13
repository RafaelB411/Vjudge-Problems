#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int cell;
    char key[16];
} Item;

Item createElem(int cvalue, char* kvalue) {
    Item itemp;
    itemp.cell = cvalue;
    strcpy(itemp.key, kvalue);
    return itemp;
}

typedef struct Dictionary {
    int hlen;
    int hcnt;
    Item* table;
    int (*hash)(char*);
} Dictionary;

Dictionary createDict(int size, int (*fuction)(char*)) {
    Dictionary dtemp;
    dtemp.hlen = size;
    dtemp.hcnt = 0;
    dtemp.table = (Item*) malloc(size*sizeof(Item));
    if(dtemp.table == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    for(int n=0; n<size; n++) dtemp.table[n].cell = -1;
    dtemp.hash = fuction;
    return dtemp;
}

void clearTable(Dictionary* dictionary) {
    for(int n=0; n<dictionary->hlen; n++) dictionary->table[n].cell = -1;
    dictionary->hcnt = 0;
}

void clearDict(Dictionary* dictionary) {
    free(dictionary->table);
    dictionary->hcnt = 0;
}

int searchElem(Dictionary dictionary, char* key) {
    for(int n=0; n<dictionary.hlen; n++) {
        if(strcmp(key, dictionary.table[n].key)==0 && dictionary.table[n].cell!=-1)
            return n;
    }
    return -1;
}

void insertElem(Dictionary* dictionary, char* key) {
    if(searchElem((*dictionary), key)==-1) {
        int hfunc = dictionary->hash(key);
        int pos = hfunc;
        for(int n=0; n<20 && dictionary->table[pos].cell!=-1; n++) {
            pos = (hfunc+n*n+23*n)%101;
        }
        if(dictionary->table[pos].cell==-1) {
            dictionary->table[pos] = createElem(pos, key);
            dictionary->hcnt++;
        }
    }
}

void removeElem(Dictionary* dictionary, char* key) {
    int ward=0;
    for(int n=0; n<dictionary->hlen && !ward; n++) {
        if(strcmp(key, dictionary->table[n].key)==0 && dictionary->table[n].cell!=-1) {
            dictionary->table[n].cell = -1;
            dictionary->hcnt--;
            ward = 1;
        }
    }
}

int sizeDict(Dictionary dictionary) { return dictionary.hcnt; }

int hfunc(char* key) {
    long long int sum = 0;
    for(long long int n=0; n<strlen(key); n++) {
        sum += key[n] * (n+1);
    }
    sum *= 19;
    return sum%101;
}

int main() {
    Dictionary dict;
    int cases, opnum;
    char oper[21], str[16];

    dict = createDict(101, &hfunc);

    scanf("%d", &cases);
    for(int i=0; i<cases; i++) {
        scanf("%d", &opnum);
        for(int j=0; j<opnum; j++) {
            scanf(" %s", oper);
            for(int c=4; oper[c-1]!='\0'; c++) {
                str[c-4] = oper[c];
            }
            if(strncmp(oper, "ADD", 3)==0) {
                insertElem(&dict, str);
            }
            if(strncmp(oper, "DEL", 3)==0) {
                removeElem(&dict, str);
            }
        }
        printf("%d\n", dict.hcnt);
        for(int k=0; k<dict.hlen; k++) {
            if(dict.table[k].cell!=-1)
            printf("%d:%s\n", k, dict.table[k].key);
        }
        clearTable(&dict);
    }

    return 0;
}