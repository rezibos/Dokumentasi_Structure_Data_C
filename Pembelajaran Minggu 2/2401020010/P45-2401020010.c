#include <stdio.h>
#include <stdlib.h>

void rec2401020010(int baris, int barisSekarang) {
    if (barisSekarang >= baris) {
        return;
    }

    for (int j = 0; j < barisSekarang + 1; j++) {
        printf("%c", 'A' + barisSekarang);
    }
    
    for (int j = 0; j < baris - (barisSekarang + 1); j++) {
        printf("%c", 'a' + barisSekarang);
    }
    
    printf("\n");
    
    rec2401020010(baris, barisSekarang + 1);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Terjadi Kesalahan Saat Input");
        return 1;
    }
    
    int jumlahBaris = atoi(argv[1]);

    rec2401020010(jumlahBaris, 0);
    
    return 0;
}