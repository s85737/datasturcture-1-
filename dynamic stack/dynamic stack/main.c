//
//  main.c
//  dynamic stack
//
//  Created by 최제현 on 2020/05/09.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct stackNode{
    element data;
    struct stackNode* link;
    
} stackNode;

stackNode* createStack(){
    return NULL;
    
    
}

//스택이 공백 상태인지 확인하는 연산

int isEmptyStack(stackNode* top){
    if(top ==NULL){
        printf("\n\n Stack is empty\n");
        return 1;
    }
    else return 0;
    
}

//스택의 top에 원소를 삽입하는 연산
// 이중포인터는 top의 위치를 바꿀수도 있기 때문에 하는것
void push(stackNode** top, element item){
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    
    if(!temp){
        exit(1);
    }
    
    temp->data = item;
    temp->link = *top;
    *top = temp;
}

//스택의 top 에서 원소를 삭제하는 연산
element pop(stackNode** top){
    element item;
    stackNode* temp;
    
    if(isEmptyStack(*top))
        exit(1);
    
    else{ //스택이 공백 리스트가 아닌
        temp = *top;
        item = temp->data;
        *top = (*top)->link; //top 위치를 삭제 노드
        free(temp); //삭제된 노드의 메모리 반환
        return item; //삭제된 원소 반환
    }
    
}


// 스택의 원소를 top에서 bottm 순서로 출력하는 연산
void printStack(stackNode** top){
    stackNode* p = *top;
    printf("\nSTACK [");{
        while(p) {
            printf("%d ", p->data);
            p = p->link;
        }
        printf("] \n");
        
    }
    
    
}

void deleteStack(stackNode** top){
    stackNode* temp, * p;
    
    p= *top;
    
    while(p)
    {
        temp = p->link;
        free(p);
        p = temp;
        
    }
    *top = NULL;
    
    
}

int main(int argc, const char * argv[]) {
    element item;
    stackNode* top;
    
    top = createStack();
    
    printf("\n** 연결 스택 연산 \n ");
    
    push(&top, 1);
    item = pop(&top);
    printf("%d", item);
    
    for (int i=2; i<5; i++){
        push(&top, i);
        
        
    }
    
    printStack(&top);
    
    item = pop(&top);
    printf("pop => %d\n", item);
    item = pop(&top);
    printf("pop => %d\n", item);
    item = pop(&top);
    printf("pop => %d\n", item);
    
    
    
    return 0;
}
