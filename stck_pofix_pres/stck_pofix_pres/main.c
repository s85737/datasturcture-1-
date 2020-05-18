//
//  main.c
//  stck_pofix_pres
//
//  Created by 최제현 on 2020/05/17.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct stackNode{
    element data;
    struct stackNode* link;
    
}stackNode;

stackNode* createStack(){
    return NULL;
}

//스택이 공백 상태인지 확인하는 연산

int isEmptyStack(stackNode* top){
    if (top == NULL) return 1;
    else return 0;
}


// 스택의 top에 원소를 삽입하는 연산
void push(stackNode*){
    
}

//중위 표기 수식 -> 후위 표기 수식

void infix_to_postfix(stackNode **s, char* exp){
    int i 
}
int main(int argc, const char * argv[]) {
    element item;
    stackNode* top;
    top = createStack();
    
    int result;
    char* s = "2+3*4+9";
    //char* s = "(2+3)*4+9;
    
    printf("중위표시수식 %s\n", s);
    
    infix_to_postfix(&top, s);
    deleteStack(&top);
    return 0;
}
