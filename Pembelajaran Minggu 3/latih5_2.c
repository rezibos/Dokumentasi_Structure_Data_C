#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	// deklarasi variable berjenis pointer ke file untuk
	// menampung hasil yang diberikan fungsi fopen
	FILE* fptr;

	// membuka file text yang disebutkan pada command argument
	// dalam mode tulis "w"
	fptr = fopen(argv[1], "w");

	// jika file tidak berhasil dibuka
	if (fptr == NULL) {
        printf("Gagal baca file. Program berhenti dengan " "kode 5.");
        exit(5);	
    }
	//selain itu berarti berhasil
	else {
		printf("File berhasil dibuka.");
    }

	// jangan lupa tutup file kalua sudah tidak diperlukan.
	fclose(fptr);
	// program berhenti dengan kode 0 alias sukses tanpa masalah
	return 0;
}