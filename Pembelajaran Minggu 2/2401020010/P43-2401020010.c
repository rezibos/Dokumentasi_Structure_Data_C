#include <stdio.h>
#include <stdlib.h>

void segitigatebalek(int baris) {
    printf("Hello, World!\n");
    for (int i = 0; i < baris; i++) {
        int spasi = i;
        
        for (int j = 0; j < spasi; j++) {
            printf(" ");
        }
        
        printf("o");
        
        int garisputus = (baris - i - 1) * 2 - 1;
        
        if (garisputus > 0) {
            for (int k = 0; k < garisputus; k++) {
                printf("-");
            }
            printf("o");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Terjadi Kesalahan Saat Input");
        return 1;
    }
    
    int jumlahBaris = atoi(argv[1]);

    segitigatebalek(jumlahBaris);
    
    return 0;
}