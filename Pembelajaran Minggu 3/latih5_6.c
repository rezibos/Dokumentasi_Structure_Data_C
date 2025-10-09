#include <stdio.h>
#include <string.h>

int main() {
	FILE* filePointer;

	char dataToBeRead[50];

	filePointer = fopen("TestFile.txt", "r");

	if (filePointer == NULL) {
		printf("TestFile.txt gagal dibuka.");
	} else {
		printf("File dibuka dan mulai membaca isi file.\n");

		while (fgets(dataToBeRead, 50, filePointer) != NULL) {
			printf("%s", dataToBeRead);
		}
		fclose(filePointer);

		printf("Berhasil membaca TestFile.txt \n");
		printf("File ditutup.\n");
	}
	return 0;
}