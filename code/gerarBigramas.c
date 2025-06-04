#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool validChar(char c) {
    return (c!= 'k' && c!= 'y' && c!= 'w');
}

int main() {
    FILE *bigramas = fopen("resources/all-bigramas.txt", "w");
    for (int i = 'a'; i <= 'z'; i++) {
        for (int j = 'a'; j <= 'z'; j++) {
            if(validChar(i) && validChar(j))
                fprintf(bigramas, "%c%c\n", i, j);
        }
    }
    fclose(bigramas);
    return 0;
}