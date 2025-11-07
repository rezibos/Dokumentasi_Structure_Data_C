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
    while(start != NULL){
        penduduk *temp = start;
        start = start->next;
        free(temp->nama);
        free(temp);
    }
    start = NULL;
    current = NULL;
    
    rewind(file);
    penduduk *tmp;
    while(1){
        tmp = createNewLink();
        // int result = fscanf(file, "%d;%100[^;];%c\n", &tmp->nik, tmp->nama, &tmp->gender); // BEFORE
        int result = fscanf(file, "%d;%s;%c \n", &tmp->nik, tmp->nama, &tmp->gender); // AFTER
        
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

void writeAllDataToFile(FILE *file){
    char filename[100];
    strcpy(filename, "data1.csv");
    
    FILE *temp = fopen("temp_data.csv", "w");
    if(temp == NULL){
        printf("Error: Tidak bisa membuat file temporary\n");
        return;
    }
    
    penduduk *write_tmp = start;
    while(write_tmp != NULL){
        fprintf(temp, "%d;%s;%c\n", write_tmp->nik, write_tmp->nama, write_tmp->gender);
        write_tmp = write_tmp->next;
    }
    
    fclose(temp);
    
    fclose(file);
    
    remove(filename);
    rename("temp_data.csv", filename);
    
    file = fopen(filename, "a+");
    if(file == NULL){
        printf("Error: Tidak bisa membuka file setelah update\n");
        exit(1);
    }
    
    f = file;
    
    printf("Data berhasil disimpan ke file CSV.\n");
}

int edit(){
    char keywd[10], nilai[100];
    printf("Edit Data\n");
    printf("Masukan keyword (NIK/NAMA) spasi nilai_yang_dicari untuk diedit:\n");
    scanf("%s %s", keywd, nilai);
    fflush(stdin);
    
    penduduk *tmp = start;
    int found = 0;
    int count = 0;
    
    if(tmp == NULL){
        printf("Data kosong\n");
        return 1;
    }
    
    penduduk *foundData[100];
    while(tmp != NULL){
        if(strcmp(keywd, "NIK")==0){
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik);
            if(strstr(nik_str, nilai) != NULL){
                foundData[count++] = tmp;
                found = 1;
            }
        } else if(strcmp(keywd, "NAMA")==0){
            if(strstr(tmp->nama, nilai) != NULL){
                foundData[count++] = tmp;
                found = 1;
            }
        }
        tmp = tmp->next;
    }
    
    if(!found){
        printf("Data tidak ditemukan\n");
        return 1;
    }
    
    printf("\n%d data ditemukan:\n", count);
    for(int i = 0; i < count; i++){
        printf("[%d] NIK: %d, Nama: %s, Gender: %c\n", 
                i+1, foundData[i]->nik, foundData[i]->nama, foundData[i]->gender);
    }
    
    int pilihan;
    if(count > 1){
        printf("\nPilih data yang akan diedit (1-%d): ", count);
        scanf("%d", &pilihan);
        fflush(stdin);
        if(pilihan < 1 || pilihan > count){
            printf("Pilihan tidak valid!\n");
            return 1;
        }
    } else {
        pilihan = 1;
    }
    
    penduduk *dataToEdit = foundData[pilihan-1];
    
    printf("\nData yang akan diedit:\n");
    printf("NIK\t: %d\n", dataToEdit->nik);
    printf("Nama\t: %s\n", dataToEdit->nama);
    printf("Gender\t: %c\n", dataToEdit->gender);
    
    printf("\nMasukan data baru:\n");
    
    unsigned int new_nik;
    char new_nama[101];
    char new_gender;
    
    printf("NIK baru: ");
    scanf("%d", &new_nik);
    printf("Nama baru: ");
    scanf(" %[^\n]", new_nama);
    printf("Gender baru [L/P]: ");
    scanf(" %c", &new_gender);
    
    if(new_gender != 'L' && new_gender != 'P' && 
        new_gender != 'l' && new_gender != 'p') {
        printf("Gender tidak valid! Edit dibatalkan.\n");
        return 1;
    }
    
    if(new_gender == 'l') new_gender = 'L';
    if(new_gender == 'p') new_gender = 'P';
    dataToEdit->nik = new_nik;
    strcpy(dataToEdit->nama, new_nama);
    dataToEdit->gender = new_gender;
    
    printf("Data berhasil diupdate di memory!\n");
    writeAllDataToFile(f);
    
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
    int count = 0;
    
    if(tmp == NULL){
        printf("Data kosong\n");
        return 1;
    }
    
    penduduk *foundData[100];
    penduduk *toDelete[100];
    
    while(tmp != NULL){
        penduduk *next = tmp->next;
        
        if(strcmp(keywd, "NIK")==0){
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik);
            if(strstr(nik_str, nilai) != NULL){
                foundData[count] = tmp;
                toDelete[count] = tmp;
                count++;
                found = 1;
            }
        } else if(strcmp(keywd, "NAMA")==0){
            if(strstr(tmp->nama, nilai) != NULL){
                foundData[count] = tmp;
                toDelete[count] = tmp;
                count++;
                found = 1;
            }
        }
        tmp = next;
    }
    
    if(!found){
        printf("Data tidak ditemukan\n");
        return 1;
    }
    
    printf("\n%d data ditemukan:\n", count);
    for(int i = 0; i < count; i++){
        printf("[%d] NIK: %d, Nama: %s, Gender: %c\n", 
                i+1, foundData[i]->nik, foundData[i]->nama, foundData[i]->gender);
    }
    
    char konfirmasi;
    printf("\nYakin ingin menghapus %d data ini? (Y/N): ", count);
    scanf(" %c", &konfirmasi);
    
    if(konfirmasi == 'Y' || konfirmasi == 'y'){
        for(int i = 0; i < count; i++){
            removeLink(toDelete[i]);
        }
        
        printf("%d data berhasil dihapus dari memory!\n", count);
        writeAllDataToFile(f);
    } else {
        printf("Penghapusan dibatalkan.\n");
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
        if (strcmp(keywd, "NIK")==0) {
            char *a = itoa(tmp->nik, a, 10);
            found = strstr(a, nilai);
        } else if (strcmp(keywd, "NAMA")==0) {
            found = strstr(tmp->nama, nilai);
        } else if (strcmp(keywd, "GENDER")==0) {
            found = strstr(&tmp->gender, nilai);
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