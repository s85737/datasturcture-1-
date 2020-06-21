//
//  main.c
//  postorder traversal
//
//  Created by 최제현 on 2020/06/17.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct treeNode{
    element data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

typedef struct stackNode{
    treeNode* data;
    struct stackNode* link;
} stackNode;

typedef struct stack{
    struct stackNode* top;
} stack;

stackNode* createStack(){
    return NULL; //data가 없을때 top = NULL
}

//linked list stack이 비어있는지 확인하는 함수

int stackEmpty(stackNode* top){
    if(top == NULL) return 1; //data가 없을때 top은 NULL 이므로
    else return 0;
}

/*
 linked list stack 에서 pop하는 함수
 @params 구조체 선언을 할 때 따로 보조구조체인 top을 선언하지 않고, main 함수에서 선언
 하였기 떄문에 -> top -> Node 를 역참조 하려면 이중포인터를 사용
 */

treeNode* pop(stackNode** top){
    treeNode* data;
    stackNode** temp; //pop 후 남은 Node를 삭제하기 위해 선언
    
    if(stackEmpty(*top)){
        //스택이 비어있을때 오류 출력
        fprintf(stderr ,"\n\n stack empty error!\n");
        exit(-1);
    }
    
    temp = *top;
    data = (*top) -> data;
    //pop 하기전 head에 연결된 node가 top 이었으므로, 그 다음 Node를 top으로 변경
    *top = (*top) -> link;
    free(temp);
    
    return data;
}

treeNode* peek(stackNode** top){
    if(*top == NULL){
        printf("\nStack is empty!\n");
        exit(1);
    }
    else{
        return((*top) -> data);
    }
    
}

//linked list stack에서 push 하는 함수

void push(stackNode** top, treeNode* data){
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    if(!newNode){
        //메모리 할당이 제대로 되지 않았을 때 오류출력
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    newNode -> data = data;
    newNode -> link = *top; //새로 생성된 노드의 다음노드에 top 에 붙여줌
    *top = newNode; // 새로운 노드가 push 되었으므로 top 변경
    
    
}

void deleteStack(stackNode** top){
    stackNode *temp = *top;
    while(*top != NULL){
        pop(&temp);
    }
    
    free(temp);
    
    
}

//linked list의 모든 스택을 출력하는 함수

void printStack(stackNode** top){
    
    stackNode* stack = *top;
    if(stackEmpty(*top)){
        fprintf(stderr ,"stack is empty!\n");
        return;
    }
    printf("\nLinked STACK [top- ");
    while(stack){
        printf("%d ", stack -> data);
        stack = stack->link;
    }
    printf("]\n");
    
}


treeNode* createNode(int data){
    treeNode* newNode = malloc(sizeof(treeNode));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> data = data;
    return newNode;
    
}

void makeTree(treeNode* parent, treeNode* lson, treeNode* rson){
    
    parent -> left = lson;
    parent -> right = rson;
    
}


void postOrder(treeNode* root){
    stackNode* top;
    top = createStack();
    
    push(&top, root); //최종적으로 출력될 root 노드를 스택 제일 아래에 둔다.
    while(1){
                while(root){ //더이상 자식 노드가 없을때 까지 탐색
            
            if(root-> right) push(&top ,root->right); //만약 오른쪽 노드가 있으면, 왼쪽노드가 pop 된 후, 오른쪽 노드가 pop 되어야 하므로 스택에 넣는다.
            push(&top, root);
            root = root->left; //왼쪽 자식노드로 이동
            
            
        }
        
        // 왼쪽에 자식노드가 더이상 없을 때
        
        // 루트에 현재 top 노드 pop
        root = pop(&top);
        
        //아직 현재 탐색중인 root 노드의 오른쪽 자식노드가 있고 top의 값과 같으면 print 하지않고 pop후 현재 root push, root오른쪽으로 이동
        if(root->right && peek(&top) == root->right){
            pop(&top);
            push(&top, root);
            root = root->right;
        }else{ // 그 외일경우 root 출력, root를 null로 만든다.
            printf("%d ",root->data);
            root = NULL;
        }
    }
    
    deleteStack(&top);
    
}


int main(int argc, const char * argv[]) {
 
    
    stackNode* top;
    treeNode* n1 = createNode(1);
    treeNode* n2 = createNode(2);
    treeNode* n3 = createNode(3);
    treeNode* n4 = createNode(4);
    treeNode* n5 = createNode(5);
    treeNode* n6 = createNode(6);
    treeNode* n7 = createNode(7);
    
    makeTree(n1, n2, n3);
    makeTree(n2, n4, n5);
    makeTree(n3, n6, n7);
    
    postOrder(n1);
    
    
    
    return 0;
}
