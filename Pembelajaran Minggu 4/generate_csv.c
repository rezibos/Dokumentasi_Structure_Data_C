#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_csv(const char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Gagal membuka file");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int num = rand() % 1000000 + 10;
        fprintf(fp, "%d\n", num);
    }

    fclose(fp);
    printf("File %s berhasil dibuat dengan %d data.\n", filename, count);
}

int main() {
    generate_csv("data100.csv", 100);
    generate_csv("data1000.csv", 1000);
    generate_csv("data10000.csv", 10000);
    return 0;
}
