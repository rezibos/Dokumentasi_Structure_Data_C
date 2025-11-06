#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "linklistdata.h"

penduduk *start, *current, *startEntry, *currentEntry;
extern FILE *f;

penduduk *createNewLink(){
    penduduk *newLink = (penduduk *)malloc(sizeof(penduduk));
    newLink->nama = (char *)malloc(sizeof(char) * 101);
    newLink->prev = NULL;
    newLink->next = NULL;
    newLink->nik = 0;
    newLink->gender = ' ';
    return newLink;
}

void addNewLink(penduduk *newLink){
    if(start == NULL){
        start = newLink;
        current = newLink;
    } else {
        current->next = newLink;
        newLink->prev = current;
        current = newLink;
    }
}

void addNewEntry(penduduk *newLink){
    if(startEntry == NULL){
        startEntry = newLink;
        currentEntry = newLink;
    } else {
        currentEntry->next = newLink;
        newLink->prev = currentEntry;
        currentEntry = newLink;
    }
}

void removeLink(penduduk *link){
    if(link == NULL) return;
    
    if(link->prev != NULL){
        link->prev->next = link->next;
    } else {
        start = link->next;
    }
    
    if(link->next != NULL){
        link->next->prev = link->prev;
    } else {
        current = link->prev;
    }
    
    free(link->nama);
    free(link);
}

void flushNewEntry(FILE *file){
    if(startEntry == NULL){
        printf("Tidak ada data untuk disimpan.\n");
        return;
    }
    
    penduduk *tmp = startEntry;
    while(tmp != NULL){
        fprintf(file, "%d;%s;%c\n", tmp->nik, tmp->nama, tmp->gender);
        addNewLink(tmp);
        tmp = tmp->next;
    }
    
    fflush(file);
    startEntry = NULL;
    currentEntry = NULL;
    printf("Data berhasil disimpan ke file.\n");
}

void loadData(FILE *file){
    rewind(file);
    penduduk *tmp;
    
    while(!feof(file)){
        tmp = createNewLink();
        int result = fscanf(file, "%d;%100[^;];%c\n", &tmp->nik, tmp->nama, &tmp->gender);
        
        if(result == 3){
            addNewLink(tmp);
        } else {
            free(tmp->nama);
            free(tmp);
            break;
        }
    }
    
    if(start != NULL){
        printf("Data berhasil dimuat dari file.\n");
    }
}

int edit(){
    char keywd[10], nilai[100];
    printf("Edit Data\n");
    printf("Masukan keyword (NIK/NAMA) spasi nilai_yang_dicari untuk diedit:\n");
    scanf("%s %s", keywd, nilai);
    fflush(stdin);
    
    penduduk *tmp = start;
    int found = 0;
    
    if(tmp == NULL){
        printf("Data kosong\n");
        return 1;
    }
    
    while(tmp != NULL){
        if(strcmp(keywd, "NIK")==0){
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik);
            if(strstr(nik_str, nilai) != NULL){
                found = 1;
                printf("Data ditemukan:\n");
                printf("NIK\t:%d\n", tmp->nik);
                printf("Nama\t:%s\n", tmp->nama);
                printf("Gender\t:%c\n", tmp->gender);
                printf("\nMasukan data baru:\n");
                printf("NIK baru:");
                scanf("%d", &tmp->nik);
                printf("Nama baru:");
                scanf("%*c%[^\n]%*c", tmp->nama);
                printf("Gender baru:");
                scanf("%c%*c", &tmp->gender);
                printf("Data berhasil diupdate\n");
                break;
            }
        } else if(strcmp(keywd, "NAMA")==0){
            if(strstr(tmp->nama, nilai) != NULL){
                found = 1;
                printf("Data ditemukan:\n");
                printf("NIK\t:%d\n", tmp->nik);
                printf("Nama\t:%s\n", tmp->nama);
                printf("Gender\t:%c\n", tmp->gender);
                printf("\nMasukan data baru:\n");
                printf("NIK baru:");
                scanf("%d", &tmp->nik);
                printf("Nama baru:");
                scanf("%*c%[^\n]%*c", tmp->nama);
                printf("Gender baru:");
                scanf("%c%*c", &tmp->gender);
                printf("Data berhasil diupdate\n");
                break;
            }
        }
        tmp = tmp->next;
    }
    
    if(!found){
        printf("Data tidak ditemukan\n");
    }
    
    return 1;
}

int hapus(){
    char keywd[10], nilai[100];
    printf("Hapus Data\n");
    printf("Masukan keyword (NIK/NAMA) spasi nilai_yang_dicari untuk dihapus:\n");
    scanf("%s %s", keywd, nilai);
    fflush(stdin);
    
    penduduk *tmp = start;
    int found = 0;
    
    if(tmp == NULL){
        printf("Data kosong\n");
        return 1;
    }
    
    while(tmp != NULL){
        penduduk *next = tmp->next;
        
        if(strcmp(keywd, "NIK")==0){
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik);
            if(strstr(nik_str, nilai) != NULL){
                found = 1;
                printf("Menghapus:\n");
                printf("NIK\t:%d\n", tmp->nik);
                printf("Nama\t:%s\n", tmp->nama);
                printf("Gender\t:%c\n", tmp->gender);
                removeLink(tmp);
            }
        } else if(strcmp(keywd, "NAMA")==0){
            if(strstr(tmp->nama, nilai) != NULL){
                found = 1;
                printf("Menghapus:\n");
                printf("NIK\t:%d\n", tmp->nik);
                printf("Nama\t:%s\n", tmp->nama);
                printf("Gender\t:%c\n", tmp->gender);
                removeLink(tmp);
            }
        }
        tmp = next;
    }
    
    if(found){
        printf("Data berhasil dihapus\n");
    } else {
        printf("Data tidak ditemukan\n");
    }
    
    return 1;
}

int cari(){
    char keywd[10], nilai[100], *found = NULL;
    printf("Masukan keyword (NIK/NAMA/GENDER) spasi nilai_yang_dicari. Contoh NIK 2010\n");
    scanf("%s %s", keywd, nilai);
    fflush(stdin);
    int countFound = 0;
    penduduk *tmp;
    
    if (start == NULL) {
        printf("Error data missing\n");
        return 1;
    }
    
    tmp = start;
    
    do {
        found = NULL;
        if (strcmp(keywd, "NIK")==0) {
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik);
            found = strstr(nik_str, nilai);
        } else if (strcmp(keywd, "NAMA")==0) {
            found = strstr(tmp->nama, nilai);
        } else if (strcmp(keywd, "GENDER")==0) {
            char gender_str[2] = {tmp->gender, '\0'};
            found = strstr(gender_str, nilai);
        } else {
            printf("\nKEYWORD ga dikenal.\nKeyword hanya NIK atau NAMA atau GENDER saja\n\a");
            break;
        }

        if (found){
            countFound++;
            printf("=================\n");
            printf("NIK\t:%d\n", tmp->nik);
            printf("Nama\t:%s\n", tmp->nama);
            printf("Gender\t:%c\n", tmp->gender);
            printf("\n");
        }
    } while ((tmp = tmp->next) != NULL);
    
    printf("%d data ditemukan.\n", countFound);

    return lanjut();
}