#include <stdio.h>
#include <stdlib.h>

void ite2401020010(int n) {
    for (int i = 0; i < n; i++) {
        int jHurufBesar = i + 1;
        
        for (int j = 0; j < jHurufBesar; j++) {
            printf("%c", 'A' + i);
        }
        
        int jHuruhKecil = n - jHurufBesar;
        for (int j = 0; j < jHuruhKecil; j++) {
            printf("%c", 'a' + i);
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

    ite2401020010(jumlahBaris);
    
    return 0;
}