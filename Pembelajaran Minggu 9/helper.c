#include<stdio.h>

int lanjut(){
   char lanjut;
   while(1==1){
      printf("Sekali Lagi ? [Y]a / [T]idak :");
      scanf_s(" %c", &lanjut);
      fflush(stdin);
      if(lanjut=='T')
         return 1;
      else if(lanjut=='Y')
	      break;
   }
   return 0;
}