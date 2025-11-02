#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_NIM 20
#define MAX_NAMA 100

typedef struct Mahasiswa {
    char nim[MAX_NIM];
    char nama[MAX_NAMA];
    struct Mahasiswa *next;
} Mahasiswa;

Mahasiswa *head = NULL;
int jumlahData = 0;

void toLower(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int bacaFile(char *namaFile){
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Error: File tidak dapat dibuka\n");
        return 0; 
    }
    
    Mahasiswa * current = head;
    while (current != NULL){
        Mahasiswa *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    jumlahData = 0;

    char line[200];
    Mahasiswa *tail = NULL;

    while (fgets(line, sizeof(line), file)){
        Mahasiswa *newNode = (Mahasiswa*)malloc(sizeof(Mahasiswa));

        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;

        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(newNode->nim, token);

            token = strtok(NULL, ",");
            if(token != NULL){
                strcpy(newNode->nama, token);
                newNode->next = NULL;

                if(head == NULL){
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                jumlahData++;
            } else {
                free(newNode);
            }
        } else {
            free(newNode);
        }
    }

    fclose(file);
    return jumlahData;
}

void cariData(char *jenis, char *keyword) {
    clock_t start = clock();
    int found = 0;

    char keywordLower[100];
    strcpy(keywordLower, keyword);
    toLower(keywordLower);

    printf("\nResult:\n");

    Mahasiswa *current = head;
    while(current != NULL){
        if(strcmp(jenis, "NIM") == 0){
            char nimLower[MAX_NIM];
            strcpy(nimLower, current->nim);
            toLower(nimLower);

            if(strstr(nimLower, keywordLower) != NULL){
                printf("%s %s\n", current->nim, current->nama);
                found++;
            }
        } else if(strcmp(jenis, "NAMA") == 0){
            char namaLower[MAX_NAMA];
            strcpy(namaLower, current->nama);
            toLower(namaLower);
            
            if (strstr(namaLower, keywordLower) != NULL) {
                printf("%s %s\n", current->nim, current->nama);
                found++;
            }
        }
        
        current = current->next;
    }
    
    if (found == 0) {
        printf("Data tidak ditemukan\n");
    }

    clock_t end = clock();
    double timeElapsed = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("Total time %.3f seconds\n", timeElapsed);
}

void prosesCommand(char *command){
    command[strcspn(command, "\n")] = 0;
    command[strcspn(command, "\r")] = 0;

    if(strcmp(command, "berhenti") == 0){
        Mahasiswa *current = head;
        while (current != NULL){
            Mahasiswa *temp = current;
            current = current->next; 
            free(temp);
        }
        exit(0);
    }

    char cmd[10], jenis[10], keyword[100];
    int result = sscanf(command, "%s %s %[^\n]", cmd, jenis, keyword);

    if(result != 3 || strcmp(cmd, "cari") != 0){
        printf("\nSyntax error. Should only\n");
        printf("cari xxx yyy\n");
        printf("Where xxx is NIM or NAMA, and yyy is the search value\n\n");
        return;
    }

    if(strcmp(jenis, "NIM") != 0 && strcmp(jenis, "NAMA") != 0){
        printf("\nSyntax error. Should only\n");
        printf("cari xxx yyy\n");
        printf("Where xxx is NIM or NAMA, and yyy is the search value\n\n");
        return;
    }

    cariData(jenis, keyword);
}

int main(int argc, char *argv[]){
    int berhasil = bacaFile(argv[1]);
    if (berhasil == 0 && head == NULL) {
        if (fopen(argv[1], "r") == NULL) {
            return 1;
        }
    }

    char command[200];

    while (1) {
        printf("\nYour command: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        prosesCommand(command);
    }
    
    Mahasiswa *current = head;
    while(current != NULL) {
        Mahasiswa *temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}