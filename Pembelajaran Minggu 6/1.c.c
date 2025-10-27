#include <stdio.h>
#define SIZE 5 // Maximum size of the queue

int queue[SIZE];
int front = -1, rear = -1;

// Fuction to add an element to the queue
void enqueue(int value) {
  if (rear == SIZE - 1) {
    printf("Queue is full! Cannot enqueue %d.\n", value);
  } else {
// Initialize front if it's the first element 
    if (front == -1) front = 0;
    queue[++rear] = value;
    printf("Enqueued: %d\n", value);
  }
}

// Function to remove an element from the queue
void dequeue() {
  if (front == -1) {
    printf("Queue is empty! Cannot dequeue.\n");
  } else {
    printf("Dequeued: %d\n", queue[front++]);
    if (front > rear) front = rear = -1; // Reset queue if empty
  }
}

// Function to display the queue
void display() {
  if (front == -1) {
    printf("Queue is empty!\n");
  } else {
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++) {
       printf("%d ", queue[i]);
    }
    printf("\n");
  }
}

// Main fuction to demonstrate queue operations
int main(){
  enqueue(10);
  enqueue(20);
  enqueue(30);
  display();
  dequeue();
  display();
  enqueue(40);
  enqueue(50);
  enqueue(60);  // This will show "Queue is full"
  display();
  return 0;
}




