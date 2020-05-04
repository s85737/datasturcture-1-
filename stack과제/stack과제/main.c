//
//  main.c
//  stack과제
//
//  Created by 최제현 on 2020/05/01.
//  Copyright © 2020 5468107최제현. All rights reserved.
//
// stack controller 사용하여 구현

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5

typedef struct {
    
    int top;
    int capacity;
    int* array;
    

} ArrayStack;

//스택 생성
ArrayStack* createStack() {
    
    
    ArrayStack *S = malloc(sizeof(ArrayStack));
    
    if (!S) {
        return NULL;
        
    }
    
    S->capacity = MAX_STACK_SIZE;
    S->top = -1;
    S->array = malloc(S->capacity * sizeof(int));
    if(!S->array)
    {
        return NULL;
    }

    return S; //구조체 포인터 반환
}

int isFullStack(ArrayStack* S){
    return (S->top == (S->capacity -1));
}

void push(ArrayStack* S, int data){
    if(isFullStack(S)){
        printf("Stack is full!\n");
        //S->capacity *= 2;
        //S->array = (int*)realloc(S->array, S->capacity * (sizeof(int)));
    }
    
    S->array[++S->top] = data;
}

int pop(ArrayStack* S){
    
    if(isEmptyStack(S)){
        printf("Stack is empty\n");
        return 0;
    }
    else return S->array[S->top--];
    
}

int isEmptyStack(ArrayStack* S){
    
    return S->top == -1;
}

void deleteStack(ArrayStack* S){
    if(S) {
        if(S->array)
            free(S->array);
        
        free(S);
    }
}

int main(int argc, const char * argv[]) {
    
    ArrayStack* mys;
    mys = createStack();
    
    for(int i = 0; i < 5; i++){
        push(mys, i);
    }

    for (int j =0; j < 6; j++){
        
        int tmp = pop(mys);
        printf("%d\n", tmp);
    }
    
    //printf("%d\n", pop(mys));
    deleteStack(mys);
    return 0;
}
