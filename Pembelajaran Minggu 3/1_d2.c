#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa{
    char nim[20];
    char nama[50];
};

int main() {
    struct Mahasiswa *data = NULL;
    int count = 0;
    char lagi;

    do {
        data = realloc(data, (count + 1) * sizeof(struct Mahasiswa));

        printf("Masukan NIM: ");
        scanf("%[^\n]", data[count].nim);
        getchar();

        printf("Masukan Nama: ");
        scanf("%[^\n]", data[count].nama);

        count++;

        printf("Masih ada Data ? Y/T : ");
        scanf(" %c", &lagi);
        getchar();

    } while (lagi == 'Y' || lagi == 'y');

    printf("\nNIM\t\tNAMA\n");
    printf("============================\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%s\n", data[i].nim, data[i].nama);
    }

    free(data);
    return 0;
}
