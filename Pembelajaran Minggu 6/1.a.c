#include<stdio.h>
#include<stdlib.h>

#define MAX 100 // Maximum size of the stack

// Stack structure
typedef struct Stack {
  int data[MAX];
  int top;
} Stack;

// Initialize the stack
void initialize(Stack *stack) {
  stack->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *stack) {
  return stack->top == -1;
}

// Check if the stack is full
int isFull(Stack *stack) {
  return stack->top == MAX - 1;
}

// Push an element onto the stack
void push(Stack *stack, int value) {
  if (isFull(stack)) {
    printf("Stack Overflow! Cannot push %d\n", value);
    return;
  }
  stack->data[++stack->top] = value;
  printf("Pushed %d onto the stack.\n", value);
}

// Pop an element from the stack
int pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Underflow! Cannot pop.\n");
    return -1; // Return -1 to indicate an error
  }
  return stack->data[stack->top--];
}

// Peek at the top element of the stack
int peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty! Cannot peek.\n");
    return -1; // Return -1 to indicate an error
  }
  return stack->data[stack->top];
}

// Main function to demonstrate stack operations
int main() {
  Stack stack;
  initialize(&stack);
  
  push(&stack, 10);
  push(&stack, 20);
  push(&stack, 30);

  printf("Top element is: %d\n", peek(&stack));
  
  printf("Popped element: %d\n", pop(&stack));
  printf("Popped element: %d\n", pop(&stack));

  printf("Is stack empty? %s\n", isEmpty(&stack) ? "Yes" : "No");

  return 0;
}



