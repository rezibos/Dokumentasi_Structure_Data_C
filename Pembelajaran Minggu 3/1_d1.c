#include <stdio.h>
#include <string.h>

int main() {
    char nim[100][20];
    char nama[100][50];
    int count = 0;
    char lagi;

    do {
        printf("Masukan NIM: ");
        scanf("%[^\n]", nim[count]);
        getchar();

        printf("Masukan Nama: ");
        scanf("%[^\n]", nama[count]);

        count++;

        if (count >= 100) {
            printf("Data sudah penuh (maksimal %d)\n", 100);
            break;
        }

        printf("Masih ada Data ? Y/T : ");
        scanf("%c", &lagi);
        getchar();

    } while (lagi == 'Y' || lagi == 'y');

    printf("\nNIM\t\tNAMA\n");
    printf("============================\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%s\n", nim[i], nama[i]);
    }

    return 0;
}
