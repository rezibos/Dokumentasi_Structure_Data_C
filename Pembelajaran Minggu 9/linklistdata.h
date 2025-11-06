typedef struct A {
   struct A *prev;
   unsigned int nik;
   char *nama;
   char gender;
   struct A *next;
} penduduk;

penduduk *createNewLink();
void addNewLink(penduduk *);
void addNewEntry(penduduk *);
void removeLink(penduduk *);
void flushNewEntry(FILE *);
void loadData(FILE *);
int cari();