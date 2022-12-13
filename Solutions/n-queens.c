#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tabuleiro {
    char board[8][8];
    int size;
    int solucoes;
} Tabuleiro;

bool valid(char tabuleiro[8][8], int q, int k, int size) {
    int i = q-1;
    int j = k-1;
    // diagonal esquerda
    while(i>-1 && j>-1) {
        if(tabuleiro[i][j]=='Q') return false;
        i--;
        j--;
    }

    i = q-1;
    j = k;
    // vertical
    while(i>-1) {
        if(tabuleiro[i][j]=='Q') return false;
        i--;
    }

    i = q-1;
    j = k+1;
    // diagonal direita
    while(i>-1 && j<size) {
        if(tabuleiro[i][j]=='Q') return false;
        i--;
        j++;
    }

    return true;
}

void qns(int q, Tabuleiro *tabuleiro) {
    if(q==tabuleiro->size) {
        if(tabuleiro->solucoes > 0) printf("\n");
        for(int i=0; i<tabuleiro->size; i++) {
            for(int j=0; j<tabuleiro->size; j++) {
                printf("%c ", tabuleiro->board[i][j]);
            }
            printf("\n");
        }
        tabuleiro->solucoes++;
    }
    else {
        for(int k=0; k<tabuleiro->size; k++) {
            if(valid(tabuleiro->board, q, k, tabuleiro->size)) {
                tabuleiro->board[q][k] = 'Q';
                qns(q+1, tabuleiro);
            }
            tabuleiro->board[q][k] = '-';
        }
    }
}

int main() {
    Tabuleiro tabuleiro;
    tabuleiro.solucoes = 0;

    scanf("%d", &tabuleiro.size);

    if(tabuleiro.size > 8) return 1;

    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            tabuleiro.board[i][j] = '-';
        }
    }

    qns(0, &tabuleiro);
    if(tabuleiro.solucoes==0) printf("Not Possible\n");

    return 0;
}