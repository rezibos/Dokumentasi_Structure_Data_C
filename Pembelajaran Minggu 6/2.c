#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int priorityQueue[MAX];
int size = 0;

// Fuction to insert an element into the prority queue
void insert(int value) {
  if (size >= MAX) {
    printf("Priority Queue is full!\n");
    return;
  }
  size++;
  int i = size;
  while (i > 1 && value > priorityQueue[i / 2]) {
    priorityQueue[i] = priorityQueue[i / 2];
    i /= 2;
  }
  priorityQueue[i] = value;
}

// Fuction to delete the highest priority element
void deleteMax() {
  if (size == 0) {
    printf("Priority Queue is empty!\n");
    return;
  }
  int max = priorityQueue[1];
  int last = priorityQueue[size];
  size--;
  int i = 1, child;
  while (i * 2 <= size) {
    child = i * 2;
    if (child + 1 <= size && priorityQueue[child + 1] > priorityQueue[child]) {
       child++;
    }
    if (last >= priorityQueue[child]) break;
    priorityQueue[i] = priorityQueue[child];
    i = child;
  }
  priorityQueue[i] = last;

  printf("Deleted element: %d\n", max);
}

// Function to display the priority queue
void display() {
  if (size == 0) {
    printf("Priority Queue is empty!\n");
    return;
  }
  printf("Priority Queue: ");
  for (int i = 1; i <= size; i++) {
     printf("%d ", priorityQueue[i]);
  }
  printf("\n");
}

// Main fuction to demonstrate the operations
int main() {
   int choice, value;

   while (1) {
     printf("\nPriority Queue Operations:\n");
     printf("1. Insert\n");
     printf("2. Delete Max\n");
     printf("3. Display\n");
     printf("4. Exit\n");
     printf("Enter your choice: ");
     scanf("%d", &choice);

     switch (choice) {
       case 1:
         printf("Enter value to insert: ");
         scanf("%d", &value);
         insert(value);
         break;
       case 2:
         deleteMax();
         break;
       case 3:
         display();
         break;
       case 4:
         exit(0);
       default:
         printf("Invalid choice! Please try again.\n");
      }
   }
   return 0;
}





