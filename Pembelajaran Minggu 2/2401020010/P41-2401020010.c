#include <stdio.h>
#include <stdlib.h>

void kotak(int baris, int kolom) {
    printf("Hello, World!\n");
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            printf("o");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Terjadi Kesalahan Saat Input");
        return 1;
    }

    int jumlahBaris = atoi(argv[1]);
    int jumlahKolom = atoi(argv[2]);
    
    kotak(jumlahBaris, jumlahKolom);
    
    return 0;
}