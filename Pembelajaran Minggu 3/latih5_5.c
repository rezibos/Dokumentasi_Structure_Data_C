#include <stdio.h>
#include <string.h>

int main() {
	FILE* filePointer;

	char dataToBeWritten[] = "Belajar Struktur Data itu mudah.";

	filePointer = fopen("TestFile.txt", "w");

	if (filePointer == NULL) {
		printf("TestFile.txt gagal dibuka.\n");
	} else {
		printf("File dibuka dan mulai menulis ke file.\n");

		if (strlen(dataToBeWritten) > 0) {
			fputs(dataToBeWritten, filePointer);
			fputs("\n", filePointer);
		}
		printf("Data sukses ditulis ke file"
			"TestFile.txt \n");
		printf("File ditutup.");
		fclose(filePointer);
	}

	return 0;
}