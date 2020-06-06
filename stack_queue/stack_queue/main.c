//
//  main.c
//  stack_queue
//
//  Created by 최제현 on 2020/06/05.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int element;

typedef struct queueNode{
    element data;
    struct queueNode* link;
}queueNode;

typedef struct queue{
    struct queueNode* front;
    struct queueNode* rear;
}queue;


typedef struct stackNode{
    element data;
    struct stackNode* link;
} stackNode;

typedef struct stackArray{
    element *data;
    int top;
    int size;
}stackArray;

element linkedPop();
//element linkedPeek();
void linkedPush();
stackNode* createLinkedStack();
int linkedStackEmpty();
int arrayStackFull();
int arrayPop();
void arrayPush();
void createARrayStack();
int arrayStackFull();
int arrayStackEmpty();



int main(int argc, const char * argv[]) {
    element stackData;
    element queueData;
    stackNode* top;
    top = createLinkedStack();
    
    
    
    
    


    return 0;
}

//linked list stack 에서 pop하는 함수

element linkedPop(stackNode** top){
    element outputData;
    stackNode** temp;
    
    if(LinkedstackEmpty(*top)){
        printf("\n\n stack is empty\n");
        exit(1);
    }else{
        temp = *top;
        outputData = (*top) -> data;
        *top = (*top) -> link;
        free(temp);
        
        return outputData;
    }
    
    
    
    return outputData;
}

////linked list stack 에서 Peek하는 함수
//
//element linkedPeek(stackNode* top){
//    element output;
//
//    if(LinkedstackEmpty(top)){
//        printf("\n\n stack is empty\n");
//        exit(1);
//    }else{
//        return(top -> data);
//    }
//
//    return output;
//}

//linked list stack에서 push 하는 함수

void linkedPush(stackNode* top, element inputData){
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    if(!temp){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    temp -> data = inputData;
    temp -> link = top;
    top = temp;
    
    
}


// linked list를 처음에 생성하는 함수

stackNode* createLinkedStack(){
    return NULL;
}

//linked list stack이 비어있는지 확인하는 함수

int linkedStackEmpty(stackNode* top){
    if(top == NULL) return 1;
    else return 0;
}

//linked list의 모든 스택을 출력하는 함수

void printLinkedStack(stackNode* top){
    
    for(stackNode* temp = top; temp != NULL; temp->link){
        printf("%d->", temp -> data);
    }
    
    printf("NULL\n"); // 탐색되는 data가 없을시 출력
    
}


//array stack 을 pop하는 함수

int arrayPop(stackArray* stack){
    
    if(arrayStackEmpty(stack)){
        fprintf(stderr, "stack empty error!\n");
        exit(-1);
    }else{
        return stack->data[(stack->top)--];
    }
    
}

//array stack을 Push하는 함수

void arrayPush(stackArray* stack, element input){
    
    if(arrayStackFull(stack)){
        stack -> size *= 2;
        stack -> data = (element*)realloc(stack -> data, stack -> size * sizeof(element)); // size 만큼 메모리 재할당
    }else{
        stack -> data[++(stack->top)] = input;
    }
    
}


//array stack을 처음에 생성하는 함수

void createArrayStack(stackArray* stack){
    
    stack -> top = -1;
    
}

//array stack이 꽉 차있는지 확인하는 함수

int arrayStackFull(stackArray* stack){
    return(stack -> top == (sizeof(stack->data)-1));
}

//array stack이 비어있는지 확인하는 함수

int arrayStackEmpty(stackArray* stack){
    return(stack -> top == -1);
}
