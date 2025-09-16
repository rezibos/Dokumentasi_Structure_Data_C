#include <stdio.h>
#include <stdlib.h>

void segitiga(int baris) {
    printf("Hello, World!\n");
    for (int i = 1; i <= baris; i++) {
        int jumlah_o = 2 * i - 1;
        int spasi_depan = baris - i;
        
        for (int j = 0; j < spasi_depan; j++) {
            printf(" ");
        }
        
        for (int j = 0; j < jumlah_o; j++) {
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
    
    segitiga(jumlahBaris);
    
    return 0;
}