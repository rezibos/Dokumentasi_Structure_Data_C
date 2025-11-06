#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PENGUNJUNG 1000
#define MAX_NAMA 100
#define MAX_NIK 20
#define MAX_TUJUAN 200
#define MAX_TANGGAL 11
#define FILENAME "bukutamu.csv"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

typedef struct {
    char tanggal[MAX_TANGGAL];
    char jam[9];
    char nik[MAX_NIK];
    char nama[MAX_NAMA];
    char tujuan[MAX_TUJUAN];
} Pengunjung;

Pengunjung data_pengunjung[MAX_PENGUNJUNG];
int jumlah_pengunjung = 0;

void dapatkan_waktu_saat_ini(char *tanggal, char *jam) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    strftime(tanggal, MAX_TANGGAL, "%Y-%m-%d", tm_info);
    strftime(jam, 9, "%H:%M:%S", tm_info);
}

void muat_data_dari_file() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File bukutamu.csv tidak ditemukan. Akan dibuat baru.\n");
        return;
    }
    
    char header[500];
    fgets(header, sizeof(header), file);
    
    char line[500];
    jumlah_pengunjung = 0;
    
    while (fgets(line, sizeof(line), file) != NULL && jumlah_pengunjung < MAX_PENGUNJUNG) {
        line[strcspn(line, "\n")] = 0;
        
        char *token;
        int field = 0;
        
        token = strtok(line, ",");
        while (token != NULL && field < 5) {
            switch (field) {
                case 0: strcpy(data_pengunjung[jumlah_pengunjung].tanggal, token); break;
                case 1: strcpy(data_pengunjung[jumlah_pengunjung].jam, token); break;
                case 2: strcpy(data_pengunjung[jumlah_pengunjung].nik, token); break;
                case 3: strcpy(data_pengunjung[jumlah_pengunjung].nama, token); break;
                case 4: strcpy(data_pengunjung[jumlah_pengunjung].tujuan, token); break;
            }
            token = strtok(NULL, ",");
            field++;
        }
        jumlah_pengunjung++;
    }
    
    fclose(file);
}

void simpan_data_ke_file() {
    FILE *file = fopen(FILENAME, "w");
    
    fprintf(file, "Tanggal,Jam,NIK,Nama,Tujuan\n");
    
    for (int i = 0; i < jumlah_pengunjung; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                data_pengunjung[i].tanggal,
                data_pengunjung[i].jam,
                data_pengunjung[i].nik,
                data_pengunjung[i].nama,
                data_pengunjung[i].tujuan);
    }
    
    fclose(file);
}

void tambah_pengunjung() {
    if (jumlah_pengunjung >= MAX_PENGUNJUNG) {
        printf(COLOR_RED "\n==============================================\n");
        printf(COLOR_RED "                  PERINGATAN!                 \n");
        printf(COLOR_RED "==============================================\n");
        printf(COLOR_RED " Data pengunjung sudah penuh! (%d/%d)         \n", jumlah_pengunjung, MAX_PENGUNJUNG);
        printf(COLOR_RED "==============================================\n" COLOR_RESET);
        printf("\nTekan enter untuk lanjut : ");
        system("pause>null"); 
        return;
    }

    Pengunjung p;
    dapatkan_waktu_saat_ini(p.tanggal, p.jam);

    system("cls");

    int input_valid = 0;
    while (!input_valid) {
        system("cls");
        
        printf(COLOR_CYAN "\n================================================\n");
        printf(COLOR_YELLOW "              TAMBAH PENGUNJUNG BARU            \n");
        printf(COLOR_CYAN "================================================\n");
        printf(COLOR_RESET " Tanggal: %s (otomatis)                         \n", p.tanggal);
        printf(COLOR_RESET " Jam: %s (otomatis)                             \n", p.jam);
        printf(COLOR_CYAN "================================================\n" COLOR_RESET);

        printf(" NIK : ");
        printf(COLOR_BLUE);
        fflush(stdout);
        fgets(p.nik, MAX_NIK, stdin);
        p.nik[strcspn(p.nik, "\n")] = 0;
        printf(COLOR_RESET);

        printf(" Nama : ");
        printf(COLOR_BLUE);
        fflush(stdout);
        fgets(p.nama, MAX_NAMA, stdin);
        p.nama[strcspn(p.nama, "\n")] = 0;
        printf(COLOR_RESET);

        printf(" Tujuan Kunjungan : ");
        printf(COLOR_BLUE);
        fflush(stdout);
        fgets(p.tujuan, MAX_TUJUAN, stdin);
        p.tujuan[strcspn(p.tujuan, "\n")] = 0;
        printf(COLOR_RESET);

        printf(COLOR_CYAN "================================================\n" COLOR_RESET);

        int error_count = 0;
        
        if (strlen(p.nik) == 0) {
            printf(COLOR_RED " NIK tidak boleh kosong!\n" COLOR_RESET);
            error_count++;
        }
        
        if (strlen(p.nama) == 0) {
            printf(COLOR_RED " Nama tidak boleh kosong!\n" COLOR_RESET);
            error_count++;
        }
        
        if (strlen(p.tujuan) == 0) {
            printf(COLOR_RED " Tujuan kunjungan tidak boleh kosong!\n" COLOR_RESET);
            error_count++;
        } else if (strlen(p.tujuan) < 5) {
            printf(COLOR_RED " Tujuan kunjungan minimal 5 karakter! (Saat ini: %d karakter)\n" COLOR_RESET, strlen(p.tujuan));
            error_count++;
        }

        if (error_count == 0) {
            input_valid = 1;
        } else {
            printf(COLOR_RED "\nSilakan perbaiki input di atas.\n" COLOR_RESET);
            printf("\nTekan enter untuk lanjut : ");
            system("pause>null");
        }
    }

    data_pengunjung[jumlah_pengunjung] = p;
    jumlah_pengunjung++;
    simpan_data_ke_file();

    printf(COLOR_GREEN "\n Data pengunjung berhasil ditambahkan!     \n", COLOR_RESET);
    printf(COLOR_RESET "\nTekan enter untuk lanjut : ");
    system("pause>null"); 
}

void tampilkan_berdasarkan_tanggal() {
    char tanggal_cari[MAX_TANGGAL];
    int jumlah_ditemukan = 0;
    
    system("cls");
    printf("\nMasukkan tanggal (YYYY-MM-DD): ");
    printf(COLOR_BLUE);
    fflush(stdout);
    fgets(tanggal_cari, MAX_TANGGAL, stdin);
    tanggal_cari[strcspn(tanggal_cari, "\n")] = 0;
    printf(COLOR_RESET);
    
    system("cls");
    printf(COLOR_CYAN   "===========================================\n");
    printf(COLOR_YELLOW "     DATA PENGUNJUNG TANGGAL %s     \n", tanggal_cari);
    printf(COLOR_CYAN   "===========================================\n");
    printf(COLOR_CYAN   "| %-39s |\n", "Nama");
    printf(COLOR_CYAN   "===========================================\n" COLOR_RESET);
    
    for (int i = 0; i < jumlah_pengunjung; i++) {
        if (strcmp(data_pengunjung[i].tanggal, tanggal_cari) == 0) {
            printf(COLOR_CYAN "| " COLOR_RESET "%-39s " COLOR_CYAN "|\n", data_pengunjung[i].nama);
            jumlah_ditemukan++;
        }
    }
    
    if (jumlah_ditemukan > 0) {
        printf(COLOR_CYAN "===========================================\n" COLOR_RESET);
        printf(COLOR_GREEN "Total data ditemukan: %d\n" COLOR_RESET, jumlah_ditemukan);
    } else {
        printf(COLOR_CYAN "|" COLOR_RED "             TIDAK ADA DATA              " COLOR_CYAN "|\n");
        printf(COLOR_CYAN "===========================================\n" COLOR_RESET);
    }
    
    printf("\nTekan enter untuk lanjut : ");
    system("pause>null");

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void tampilkan_berdasarkan_bulan() {
    int tahun_cari, bulan_cari;
    int jumlah_ditemukan = 0;
    
    system("cls");
    printf("\nMasukkan tahun (YYYY): ");
    printf(COLOR_BLUE);
    fflush(stdout);
    scanf("%d", &tahun_cari);
    printf(COLOR_RESET);
    
    printf("Masukkan bulan (MM): ");
    printf(COLOR_BLUE);
    fflush(stdout);
    scanf("%d", &bulan_cari);
    printf(COLOR_RESET);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    system("cls");
    printf(COLOR_CYAN   "===========================================\n");
    printf(COLOR_YELLOW "      DATA PENGUNJUNG BULAN %04d-%02d      \n", tahun_cari, bulan_cari);
    printf(COLOR_CYAN   "===========================================\n");
    printf(COLOR_CYAN   "| %-39s |\n", "Nama");
    printf(COLOR_CYAN   "===========================================\n" COLOR_RESET);
    
    for (int i = 0; i < jumlah_pengunjung; i++) {
        int tahun, bulan;
        sscanf(data_pengunjung[i].tanggal, "%4d-%2d", &tahun, &bulan);
        
        if (tahun == tahun_cari && bulan == bulan_cari) {
            printf(COLOR_CYAN "| " COLOR_RESET "%-39s " COLOR_CYAN "|\n", data_pengunjung[i].nama);
            jumlah_ditemukan++;
        }
    }
    
    if (jumlah_ditemukan > 0) {
        printf(COLOR_CYAN "===========================================\n" COLOR_RESET);
        printf(COLOR_GREEN "Total data ditemukan: %d\n" COLOR_RESET, jumlah_ditemukan);
    } else {
        printf(COLOR_CYAN "|" COLOR_RED "             TIDAK ADA DATA              " COLOR_CYAN "|\n");
        printf(COLOR_CYAN "===========================================\n" COLOR_RESET);
    }
    
    printf("\nTekan enter untuk lanjut : ");
    system("pause>null");
}

void cari_berdasarkan_nama() {
    char nama_cari[MAX_NAMA];
    int jumlah_ditemukan = 0;
    
    system("cls");
    printf("\nMasukkan nama (atau bagian nama): ");
    printf(COLOR_BLUE);
    fflush(stdout);
    fgets(nama_cari, MAX_NAMA, stdin);
    nama_cari[strcspn(nama_cari, "\n")] = 0;
    printf(COLOR_RESET);
    
    system("cls");
    printf(COLOR_CYAN "===============================================================================================================\n");
    printf(COLOR_YELLOW "                                HASIL PENCARIAN UNTUK '%s'                                                \n", nama_cari);
    printf(COLOR_CYAN "===============================================================================================================\n");
    printf(COLOR_CYAN "| %-12s | %-10s | %-18s | %-25s | %-30s |\n", "Tanggal", "Jam", "NIK", "Nama", "Tujuan Kunjungan");
    printf(COLOR_CYAN "===============================================================================================================\n" COLOR_RESET);
    
    for (int i = 0; i < jumlah_pengunjung; i++) {
        if (strstr(data_pengunjung[i].nama, nama_cari) != NULL) {
            printf(COLOR_CYAN "| " COLOR_RESET "%-12s " COLOR_CYAN "| " COLOR_RESET "%-10s " COLOR_CYAN "| " COLOR_RESET "%-18s " COLOR_CYAN "| " COLOR_RESET "%-25s " COLOR_CYAN "| " COLOR_RESET "%-30s " COLOR_CYAN "|\n", 
                    data_pengunjung[i].tanggal,
                    data_pengunjung[i].jam,
                    data_pengunjung[i].nik,
                    data_pengunjung[i].nama,
                    data_pengunjung[i].tujuan);
            jumlah_ditemukan++;
        }
    }
    
    if (jumlah_ditemukan > 0) {
        printf(COLOR_CYAN "===============================================================================================================\n" COLOR_RESET);
        printf(COLOR_GREEN "Total data ditemukan: %d\n" COLOR_RESET, jumlah_ditemukan);
    } else {
        printf(COLOR_CYAN "|" COLOR_RED "               TIDAK ADA DATA PENGUNJUNG DENGAN NAMA MENGANDUNG '%s'                " COLOR_CYAN "|\n", nama_cari);
        printf(COLOR_CYAN "===============================================================================================================\n" COLOR_RESET);
    }
    
    printf("\nTekan enter untuk lanjut : ");
    system("pause>null");
}

void tampilkan_menu() {
    printf(COLOR_CYAN "================================================\n" COLOR_RESET);
    printf(COLOR_YELLOW "     SISTEM BUKU TAMU DIGITAL KELURAHAN X     \n" COLOR_RESET);
    printf(COLOR_CYAN "================================================\n" COLOR_RESET);
    printf(COLOR_RESET " 1. Tambah Pengunjung                          \n");
    printf(COLOR_RESET " 2. Tampilkan Berdasarkan Tanggal              \n");
    printf(COLOR_RESET " 3. Tampilkan Berdasarkan Bulan                \n");
    printf(COLOR_RESET " 4. Cari Berdasarkan Nama                      \n");
    printf(COLOR_RESET " 5. Keluar                                     \n");
    printf(COLOR_CYAN "================================================\n" COLOR_RESET);
    printf(COLOR_GREEN "Pilih menu (1-5): " COLOR_RESET);
}

int main() {
    int pilihan;
    char input[10];
    muat_data_dari_file();
    
    while (1) {
        system("cls");
        tampilkan_menu();
        printf(COLOR_BLUE);
        fgets(input, 10, stdin);
        pilihan = atoi(input);
        printf(COLOR_RESET);
        
        switch (pilihan) {
            case 1:
                tambah_pengunjung();
                break;
            case 2:
                tampilkan_berdasarkan_tanggal();
                break;
            case 3:
                tampilkan_berdasarkan_bulan();
                break;
            case 4:
                cari_berdasarkan_nama();
                break;
            case 5:
                system("cls");
                printf("Terima kasih! Program selesai.\n");
                return 0;
            default:
                printf(COLOR_RED "\nPilihan tidak valid! Silakan pilih 1-5.\n" COLOR_RESET);
                printf("\nTekan enter untuk lanjut : ");
                system("pause>null"); 
        }
    }
    
    return 0;
}