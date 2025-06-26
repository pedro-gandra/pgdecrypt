#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LEN 26
#define TOTAL_WORDS 237871
#define TOTAL_BI 235

char original[MAX_LEN];
char bigramasInexistentes[TOTAL_BI][2];
char **allPalavras;
int qtdePalavras[26];

double tempoSearch;
int ctotal, ckyw, cvogais, cbigramas, csearched;

char deslocarLetra(char l, int d) {
    if(l < 'a' || l > 'z')
        return l;
    int novaLetra = (l-97+d)%26;
    return novaLetra+97;
}

void copyWords(char** w) {
    FILE *palavras = fopen("resources/lista-filtrada.txt", "r");
    int i = 0, l = 0;
    char letra = 'a';
    while(fscanf(palavras, "%s", w[i]) != EOF) {
        if(w[i][0] != letra) {
            letra = w[i][0];
            l++;
        }
        qtdePalavras[l]++;
        i++;
    }
    fclose(palavras);
}

void copyBigramas(char bi[TOTAL_BI][2]) {
    FILE *bigramasFile = fopen("resources/bigramas-inexistentes.txt", "r");
    char c, previousChar;
    int curSize = 0, total = 0;
    while(fscanf(bigramasFile, "%c", &c) != EOF) {
        curSize++;
        if(c=='\n') {
            curSize = 0;
        } else if(curSize == 2) {
            bi[total][0] = previousChar;
            bi[total][1] = c;
            total++;
        }
        previousChar = c;
    }
    fclose(bigramasFile);
}

bool bigramaInList(char bi[2]) {
    for(int i = 0; i < 235; i++) {
        if((bi[0] == bigramasInexistentes[i][0] && bi[1] < bigramasInexistentes[i][1]) || bi[0] < bigramasInexistentes[i][0])
            return false;
        if(bi[0] == bigramasInexistentes[i][0] && bi[1] == bigramasInexistentes[i][1]) {
            cbigramas++;
            return true;
        }
    }
    return false;
}

bool encontrarPalavra(char str[]) {
    csearched++;
    int size = strlen(str);
    clock_t inicio, fim;
    inicio = clock();
    int firstLetter = str[0]-97;
    int totalSkip = 0;
    for(int i = 0; i < firstLetter; i++) {
        totalSkip+=qtdePalavras[i];
    }
    for(int p = totalSkip; p < TOTAL_WORDS; p++) {
        bool match = true;
        for(int i = 0; i < size; i++) {
            if(str[i] < allPalavras[p][i]) {
                fim = clock();
                tempoSearch += (double) (fim-inicio)/CLOCKS_PER_SEC;
                return false;
            }
            if(str[i] != allPalavras[p][i]) {
                match = false;
                break;
            }
        }
        if(match && allPalavras[p][size] == '\0') {
            fim = clock();
            tempoSearch += (double) (fim-inicio)/CLOCKS_PER_SEC;
            return true;
        }
    }
    fim = clock();
    tempoSearch += (double) (fim-inicio)/CLOCKS_PER_SEC;
    return false;
}

bool validarBigramas(char str[]) {
    for (int i = 1; str[i] != '\0'; i++) {
        char bi[] = {str[i-1], str[i]};
        if(bigramaInList(bi)) {
            return false;
        }
    }
    return true;
}

bool validarVogais(char str[]) {
    int vogais = 0;
    int size = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        size++;
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
            vogais++;
    }
    if((float)vogais/size <= 0.33) {
        cvogais++;
        return false;
    }
    return true;
}

int getKeyLength(int key[]) {
    int sizeKey = 1;
    for (int i = 1; i < 3; i++) {
        if(key[i] != -1)
            sizeKey++;
    }
    return sizeKey;
}

void printKey(int key[]) {
    printf("[%d", 26-key[0]);
    if(key[1] != -1)
       printf(", %d", 26-key[1]);
    if(key[2] != -1)
        printf(", %d", 26-key[2]); 
    printf("]\n");
}

void encodeWord(char str[], char word[], int key[]) {
    int sizeKey = getKeyLength(key);
    int i = 0;
    while(str[i] != '\0') {
        int pos = i%sizeKey;
        word[i] = deslocarLetra(str[i], key[pos]);
        i++;
    }
}

void increaseKey(int key[]) {
    if(key[1] == -1) {
        if(key[0] < 25)
            key[0]++;
        else {
            key[0] = 0;
            key[1] = 0;
        }
    } else if(key[2] == -1) {
        if(key[1] < 25)
            key[1]++;
        else {
            key[1] = 0;
            key[0]++;
        }
        if(key[0]>25) {
            key[0] = 0;
            key[2] = 0;
        }
    } else {
        key[2]++;
        if(key[2]>25) {
            key[2] = 0;
            key[1]++;
        }
        if(key[1]>25) {
            key[1] = 0;
            key[0]++;
        }
    }
}

void decifrarCifra(char str[], char new[]) {
    int c[3] = {0,-1,-1};
    while (c[0]<=25) {
        bool kwy = false;
        int j = 0;
        ctotal++;
        encodeWord(str, new, c);
        while(str[j] != '\0') {
            if(new[j] == 'k' || new[j] == 'w' || new[j] == 'y') {
                kwy = true;
                break;
            }
            j++;
        }
        if(kwy) {
            ckyw++;
            increaseKey(c);
            continue;
        }
        new[j] = '\0';
        if(validarVogais(new) && validarBigramas(new)) {
            if(encontrarPalavra(new)) {
                printf("%s - ", new);
                printKey(c);
            }
        }
        increaseKey(c);
    }
}

int main() {
    copyBigramas(bigramasInexistentes);
    allPalavras = malloc(TOTAL_WORDS*sizeof(char*));
    for (int i = 0; i < TOTAL_WORDS; i++) {
        allPalavras[i] = malloc(MAX_LEN*sizeof(char));
    };
    copyWords(allPalavras);
    char new[MAX_LEN];
    clock_t inicio, fim;
    double tempo_gasto;
    printf("Digite a palavra criptografada: ");
    scanf("%s", original);
    inicio = clock();
    tempoSearch = 0;
    ctotal = ckyw = cvogais = cbigramas = csearched = 0;
    printf("\nPalavras possiveis:\n");
    decifrarCifra(original, new);
    fim = clock();
    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Total de possibilidades: %d\n", ctotal);
    printf("Possuem KYW: %d\n", ckyw);
    printf("Possuem poucas vogais: %d\n", cvogais);
    printf("Possuem bigramas inexistentes: %d\n", cbigramas);
    printf("Foram checadas na lista: %d\n", csearched);
    printf("\n");
    printf("Tempo de execucao: %.4f segundos\n", tempo_gasto);
    printf("Tempo procurando palavras na lista: %.4f segundos\n", tempoSearch);
    printf("\n");
    free(allPalavras);
    return 0;
}