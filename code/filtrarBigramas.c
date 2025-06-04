#include <stdio.h>
#include <stdlib.h>

void pasteBigramas(FILE *arq, char bi[529][2]) {
    for (int i = 0; i < 529; i++) {
        if(bi[i][0] != '*')
            fprintf(arq, "%c%c\n", bi[i][0], bi[i][1]);
    }
}

void copyBigramas(FILE* arq, char bi[529][2], int freq[529]) {
    char c, previousChar;
    int curSize = 0, total = 0;
    while(fscanf(arq, "%c", &c) != EOF) {
        curSize++;
        if(c=='\n') {
            curSize = 0;
        } else if(curSize == 2) {
            bi[total][0] = previousChar;
            bi[total][1] = c;
            freq[total] = 0;
            total++;
        }
        previousChar = c;
    }
} 

void deletarBigrama(char bi[2], char allBigramas[529][2], int freq[529]) {
    for(int i = 0; i < 529; i++) {
        if(allBigramas[i][0] != '*') {
            if(bi[0] == allBigramas[i][0] && bi[1] == allBigramas[i][1]) {
                freq[i]++;
                if(freq[i]>=20) {
                    allBigramas[i][0] = '*';
                    allBigramas[i][1] = '*';
                }
            }
        }
    }
}

int main() {
    FILE *palavras = fopen("resources/lista-filtrada.txt", "r");
    FILE *bigramas = fopen("resources/all-bigramas.txt", "r");
    FILE *bigramasFiltrados = fopen("resources/bigramas-inexistentes.txt", "w");
    char allBigramas[529][2];
    int freqBigrama[529];
    copyBigramas(bigramas, allBigramas, freqBigrama);
    char c, previousChar;
    int curSize = 0;
    while(fscanf(palavras, "%c", &c) != EOF) {
        curSize++;
        if(c == '\n') {
            curSize = 0;
        } else if(curSize > 1) {
            char bi[2] = {previousChar, c};
            deletarBigrama(bi, allBigramas, freqBigrama);
        }
        previousChar = c;
    }
    pasteBigramas(bigramasFiltrados, allBigramas);
    fclose(palavras);
    fclose(bigramas);
    fclose(bigramasFiltrados);
    return 0;
}