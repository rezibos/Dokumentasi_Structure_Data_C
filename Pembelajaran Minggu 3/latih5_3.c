#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int num;
	FILE *fptr;

	fptr = fopen(argv[1], "w");

	if(fptr == NULL) {
        printf("Gagal buka file %s !\n", argv[1]);
        exit(1);
    }

	printf("Masukin 1 angka: ");
	scanf("%d", &num);

	fprintf(fptr, "%d", num);
	fclose(fptr);

	return 0;
}