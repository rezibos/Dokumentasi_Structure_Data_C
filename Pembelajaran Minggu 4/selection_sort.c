#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int larik[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        int indeks_min = i;
        for (int j = i + 1; j < jumlah; j++) {
            if (larik[j] < larik[indeks_min])
                indeks_min = j;
        }
        int sementara = larik[indeks_min];
        larik[indeks_min] = larik[i];
        larik[i] = sementara;
    }
}

int memuat_data(const char *nama_file, int **larik) {
    FILE *berkas = fopen(nama_file, "r");
    if (!berkas) {
        perror("Gagal membuka file");
        exit(1);
    }

    int jumlah = 0, sementara;
    while (fscanf(berkas, "%d", &sementara) == 1) jumlah++;
    rewind(berkas);

    *larik = malloc(jumlah * sizeof(int));
    for (int i = 0; i < jumlah; i++) fscanf(berkas, "%d", &(*larik)[i]);

    fclose(berkas);
    return jumlah;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("File tidak ditemukan");
        return 1;
    }

    int *data = NULL;
    int jumlah = memuat_data(argv[1], &data);

    clock_t mulai = clock();
    selection_sort(data, jumlah);
    clock_t selesai = clock();

    double waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    double mikro = waktu * 1000000;

    printf("Jumlah data: %d\n", jumlah);
    printf("Waktu eksekusi: %.6f detik (%.6f mikrodetik)\n", waktu, mikro);

    free(data);
    return 0;
}