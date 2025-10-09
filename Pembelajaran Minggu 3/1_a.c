#include <stdio.h>

int a;
int *b;

int main(int argc, char** argv){
    b = &a;
    *b = 2;

    // printf("%d %d\n", b, &a); : Debug Buat Memastikan Alamatnya Sama / Tidak

    printf("a = %d ", a);
    return 0;
}