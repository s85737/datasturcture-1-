//
//  main.c
//  stack_postfix
//
//  Created by 최제현 on 2020/05/19.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//스택 element 의 자료형을 int로 정의

typedef int element;
typedef struct {
    element data;
    struct stackNode* link;
} stackNode;


//삽입함수

void push(stackNode** top, element item){
    stackNode* temp = (stackNode**)malloc(sizeof(stackNode));
    if(!temp){
    printf("메모리 할당 에러\n");
    exit(1);
    }
    
    temp -> data = item;
    temp -> link = *top;
    *top = temp;
    
    }

//삭제함수
element *pop(stackNode** top){
    element item;
    stackNode** temp;
    
    if(is_empty(*top)) exit(1);
    
    else{
        temp = *top;
        item = (*top)->data;
        *top = (*top)->link;
        free(temp);
        return item;
    }
}

//요소를 스택에서 삭제하지 않고 데이터 추출
element peek(stackNode** top){
    if(*top == NULL){
        printf("\n\n Stack is empty! \n");
        exit(1);
    }
    else{
        return((*top)->data);
    }

}


void printStack(stackNode** top){
    stackNode* p = *top;
    printf("\nSTACK [");
    while(p){
        printf("%d ", p->data);
        p = p->link;
    }
    printf("]\n");
}

stackNode* createStack(){
    return NULL;
}
//공백 상태 검출 함수
int is_empty(stackNode* top){
    if(top == NULL){
        printf("Stack is empty\n");
        return 1;
    }
    else return 0;
}
             
//int is_full(){
//    if(count == MAX_STACK_SIZE-1){
//        printf("Stack is full\n");
//        return 1;
//    }
//    else return 0;
//}


int main(int argc, const char * argv[]) {

    element item;
    stackNode* top;
    top = createStack();
    printf("\n 연결 스택 연산 \n");
    
    push(&top, 1);
    push(&top, 2);
    push(&top, 3);
    
    printStack(&top);
    
    item = peek(&top);
    printf("peek => %d\n", item);
    
    item = pop(&top);
    printf("pop => %d\n", item);
    item = pop(&top);
    printf("pop => %d\n", item);
    item = pop(&top);
    printf("pop => %d\n", item);
    item = pop(&top);
    printf("pop => %d\n", item);
    return 0;
}
