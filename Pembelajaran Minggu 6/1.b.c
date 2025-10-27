#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char **stackString;
int  pStack;

int push(char *kata){
  if (stackString == NULL){
    stackString = (char **) malloc(sizeof(char **));
    stackString[pStack] = (char *) malloc(sizeof(char *));
    printf("success created stack\n");
  }
  char ** stackStringT = (char **) realloc(stackString, (pStack+1)*sizeof(char *));
  if (stackStringT){
    stackString = stackStringT;
    stackString[pStack] = (char *) malloc(strlen(kata) + 1);
  }
  if (strcpy(stackString[pStack], kata) != NULL){
    pStack++;
    return 1;
  }
  else
    return 0;
}

int pop(){
  if (stackString == NULL){
    printf("No stack found\n");
    return 0;
  }
  if (pStack!=0) {
    printf("\033[1;92mPop =>\033[37;44m %s \033[0m\n", stackString[--pStack]);
    free(stackString[pStack]);
    return 1;
  } else {
    printf("\033[1;31mStack Empty \n");
    return 0;
  }
}

void popAll(){
  while (pop()){
  
  }
  free(stackString);
}

void indirect(void (*func) ()) {
    func();
}

// main fuction. Do not Modify !!!!
int main(int argc, char **params){
  pStack = 0;
  if (argc <= 1){
    printf("\e[5mError.\n\e[1mFormat :\n\t\e[3m./stack.o kata1 kata2 kata3 ...\n\e[0m");
    return 1;
  }

  for (int i=1; i<argc;i++){
    if (!push(params[i])){
      printf("Push Operation %d Out of memory\n", i);
    }

  }
  
  // Here is the advance technique using pointer to call function without explicitly
  // using the function name, rather than only use the pointer variable
  void (*pr) () = popAll;
  indirect( pr );

  return 0;
}