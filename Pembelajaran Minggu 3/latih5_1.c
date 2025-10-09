#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	//Deklarasikan variable berjenis pointer ke file untuk
	//menampung hasil yang diberikan fungsi fopen
	FILE* fptr;

	//Membuka file text yang disebutkan pada command argument
	//dalam mode baca "r"
	fptr = fopen( argv[1], "w");

	//jika file tidak berhasil dibuka
	if (fptr == NULL) {
		printf("Gagal baca file. Program berhenti dengan " "kode 5.");
		exit(5);
}

	//jangan lupa tutup file kalua sudah tidak diperlukan.
	fclose(fptr);
	//program berhenti dengan kode 0 alias suskses tanpa masalah
	return 0;
}