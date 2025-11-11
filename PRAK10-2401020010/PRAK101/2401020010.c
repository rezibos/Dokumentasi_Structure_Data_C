#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if(root == NULL){
        return createNode(data);
    }
    if(data < root->data){
        root->left = insert(root->left, data);
    } else if(data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

int maxDepth(struct Node* node){
    if(node == NULL) return 0;
    int leftDepth = maxDepth(node->left);
    int rightDepth = maxDepth(node->right);
    return(leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void displayTree(struct Node* root, int space){
    if(root == NULL) return;
    
    space += 5;

    displayTree(root->right, space);

    printf("\n");
    for(int i = 5; i < space; i++){
        printf(" ");
    }

    if(root->left && root->right){
        printf("%c%d\n", 218, root->data);
    } else if(root->left) {
        printf("%c%d\n", 218, root->data);
    } else if(root->right) {
        printf("%c%d\n", 191, root->data);
    } else {
        printf("%d\n", root->data);
    }

    displayTree(root->left, space);
}

int main(){
    struct Node* root = NULL;
    char choice;
    int value;

    printf("=== PRPGRAM BINARY TREE SEDERHANA ===\n");
    
    do {
        printf("Masukan angka bulat: ");
        scanf("%d", &value);
        root = insert(root, value);

        int depth = maxDepth(root) - 1;
        printf("Susunan Binary Tree (Depth : %d)\n", depth);
        displayTree(root, 0);
        printf("\n");

        printf("Masih ada masukan? Y/T _ ");
        scanf(" %c", &choice);
     } while(choice == 'Y' || choice == 'y');

     printf("Program selesai.\n");
     return 0;
}
      
    





