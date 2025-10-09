#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int larik[], int jumlah) {
    for (int i = 1; i < jumlah; i++) {
        int kunci = larik[i];
        int j = i - 1;

        while (j >= 0) {
            if (larik[j] > kunci) {
                larik[j + 1] = larik[j];
                j--;
            } else {
                break;
            }
        }
        larik[j + 1] = kunci;
    }
}

int memuat_data(const char *nama_file, int **larik) {
    FILE *berkas = fopen(nama_file, "r");
    if (!berkas) {
        perror("Gagal membuka file");
        exit(1);
    }

    int jumlah = 0;
    int sementara;
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
    insertion_sort(data, jumlah);
    clock_t selesai = clock();

    double waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    double mikro = waktu * 1000000;

    printf("Jumlah data: %d\n", jumlah);
    printf("Waktu eksekusi: %.6f detik (%.6f mikrodetik)\n", waktu, mikro);

    free(data);
    return 0;
}