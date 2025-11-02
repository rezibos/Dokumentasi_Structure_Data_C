#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 100

// Stack structure
typedef struct {
  int top;
  char arr[MAX];
} Stack;

void push(Stack *stack, char c){
  stack->arr[++stack->top] = c;
}

char pop(Stack *stack){
  return stack->arr[stack->top--];
}

char peek(Stack *stack){
  return stack->arr[stack->top];
}

char isEmpty(Stack *stack){
  return stack->top == -1;
}

// Utility functions
int precedence(char op){
  if(op == '+' || op == '-') return 1;
  if(op == '*' || op == '/') return 2;
  if(op == '^') return 3;
  return 0; 
}

int isOperator(char c){
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Reverse a string
void reverse(char *exp){
  int len = strlen(exp);
  for(int i = 0; i < len / 2; i++){
    char temp = exp[i];
    exp[i] = exp[len - i - 1];
    exp[len - i - 1] = temp;
  }
}

// Convert infix to prefix
void infixToPrefix(char *infix, char *prefix){
  Stack stack;
  stack.top = -1;
  
  reverse(infix); // Reverse the infix expression

  int j = 0;
  for(int i = 0; infix[i] != '\0'; i++){
    char c = infix[i];

    if(isalnum(c)){ // Operand
       prefix[j++] = c;
    } else if(c == ')') {  // Closing parenthesis
       push(&stack, c);
    } else if(c == '(') { // Opening parenthesis
      while(!isEmpty(&stack) && peek(&stack) != ')'){
        prefix[j++] = pop(&stack);
      }
      if(!isEmpty(&stack) && peek(&stack) == ')') {
        pop(&stack);
      }
    } else if(isOperator(c)) { // Operator
       while(!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(c)){
         prefix[j++] = pop(&stack);
       }
      push(&stack, c);
    }
  }

  // Pop remaining operators
  while(!isEmpty(&stack)){
    prefix[j++] = pop(&stack);
  }

  
  prefix[j] = '\0';
  reverse(prefix); // Reverse the result to get the final prefix expression
}

// Main fuction
int main(){
  char infix[MAX], prefix[MAX];
  
  printf("Enter an infix expression: ");
  scanf("%s", infix);

  infixToPrefix(infix, prefix);

  printf("Prefix expression: %s\n", prefix);

  return 0;
}