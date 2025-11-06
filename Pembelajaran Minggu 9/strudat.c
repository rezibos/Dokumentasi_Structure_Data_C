#include<stdio.h>
#include<stdlib.h>

#include"linklistdata.h"
#include"helper.h"

FILE *f;
int (*kerja)(); // pointer ke fungsi
extern int edit();
extern int hapus();

int menu(void); 
void process(char *filename);

int input(){
  penduduk * temp = createNewLink();
  
  printf("Masukan Angka NIK (6 digit):");
  scanf("%d", &temp->nik);
  printf("Masukan nama:");
  scanf("%*c%[^\n]%*c", temp->nama);
  printf("Gender [P]erempuan/[L]aki :");
  scanf("%c%*c", &temp->gender);

  addNewEntry(temp);

  int cont = lanjut();
  if(cont==1) flushNewEntry(f);
  return cont;
}

void process(char *argv){
  f = fopen(argv, "a+");
  if(f == NULL){
    printf("Could not open %s\n", argv);
    exit(2);
  }
  loadData(f);
  while((*kerja)()==0){};
  fclose(f);
}

int menu(){
  char pilih;
  printf("\e[1;1H\e[2J");
  printf("Welcome\n===============\n");
  printf("\033[97;40m\033[1mI\033[0mnput Data\n");
  printf("\033[93;40m\033[1mE\033[0mdit Data\n");
  printf("\033[94;40m\033[1mH\033[0mapus Data\n");
  printf("\033[95;40m\033[1mC\033[0mari Data\n");
  printf("\033[96;40m\033[1mB\033[0merhenti Program\n");
  printf("\nPilihan Anda (Masukan huruf yang cetak tebal):");
  scanf("%c", &pilih);
  fflush(stdin);
  switch(pilih){
    case 'I':
    case 'i':
        kerja = input;
        return 1;
        break;
    case 'E':
    case 'e':
        kerja = edit;
        return 2;
        break;
    case 'H':
    case 'h':
   	kerja = hapus;
        return 3;
        break;
    case 'C':
    case 'c':
        kerja = cari;
        return 4;
        break;
    case 'B':
    case 'b':
        return 9;
        break;
    default:
        return 0;
  }
}

int main(int argc, char *argv[]){

  if(argc <= 1){
     printf("No argumen found.\nSyntax:\nstrudat full_path_data_file\n");
     return 1;
  }

  int choice;
  while((choice=menu())!=9){
     if(choice>=1 && choice <=4){
        process(argv[1]);
     }
     printf("\a");
  }

  printf("\nThank you for using this app\n");
  return 0;
}