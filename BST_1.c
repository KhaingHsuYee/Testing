//
// Created by Khaing Hsu Yee
//







#include "stdio.h"
#include "stdlib.h"

int a[1000];

struct Node{

    int data;

    struct Node* left;
    struct Node* right;


};
struct Node* creatNode( struct Node* newNode,int begin,int end){

    newNode =(struct Node*)malloc(sizeof (struct Node));
    int middle = (begin+end)/2;
    newNode->data = a[middle];

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root,int begin,int end){


    if(root == NULL){
        root = creatNode(root,begin,end);
    }
    int middle = (begin+end)/2;



    if(a[(begin+(middle-1))/2] != root->data && begin<=middle-1){
        root->left =  insertNode(root->left,begin,middle-1);
    }
    if(a[(end+(middle+1))/2] != root->data && middle+1<=end){
        root->right = insertNode(root->right,middle+1,end);
    }

    return root;
}
void inorderTraversal(struct Node* node){

    if(node !=NULL) {

        inorderTraversal(node->left);
        printf("data: %d\n", node->data);

        inorderTraversal(node->right);
    }
}

int main(){

    for (int i = 0; i < 1000; i++) {
        a[i] = i + 1;
    }
    int begin = 0;
    int end = 999;
    struct Node *root = NULL;
    root = insertNode(root,begin, end);

    inorderTraversal(root);
    return 0;







}
