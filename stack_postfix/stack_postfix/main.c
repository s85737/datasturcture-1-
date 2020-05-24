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
//연산자 우선순위 반환

int prec(char op){
    switch(op){
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

// infix 에서 postfix 전환
void infix_to_postfix(stackNode** s, char* pre, char* postfix){
    int i = 0;
    char ch, top;
    int len = strlen(pre);
    
    for ( i = 0; i < len; i++){
        ch = pre[i];
        switch (ch) {
            case '+': case '-': case '*': case '/': // 연산자
                // stack에 있는 연산자의 우선 순위 검사
                while(!is_empty(&s) && (prec(ch)) <= prec(peek(&s))){
                    *postfix++ = pop(&s);
                    printf("%c" , *(postfix - 1));
                    
                }
                
                push(&s, ch);
                break;
                
            case '(':
                push(&s, ch);
                break;
            case ')':
                top = pop(&s);
                
                while(top != '('){
                    printf("%c", top);
                    *postfix++ = top;
                    top = pop(&s);
                }
                
                break;
                
            default:
                printf("%c", ch);
                *postfix++ = ch;
                break;
        }
    }
    
    while(!is_empty(*s)){ // 스택에 저장된 연산자들 출력
        *postfix++ = pop(&s);
        printf("%c", *(postfix-1));
    }
}

int eval(stackNode** s,char* exp){
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    
    for ( i= 0; i<len; i++){
        ch = exp[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/'){ // 입력된 값이 operand 일 경우
            value = ch - '0'; //ASCII 코드로 저장되므로 '0' 빼준다.
            push(&s, value);
        }
        else { // operator 일 경우: operand 를 스택에서 제거
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch){
                case '+' : push(&s, op1+op2); break;
                case '-' : push(&s, op1-op2); break;
                case '*' : push(&s, op1*op2); break;
                case '/' : push(&s, op1/op2); break;
            }
        }
    }
    return pop(&s);
    
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
//        printf("Stack is empty\n");
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
    
    
    int result;
//    char* s = "(a+b)*c";
    char* s = "(2+3)*4+9";
//    char* s = "2*3+6/2-4";
    
    char postfix[50] = {0};
    
    printf("infix : %s \n", s);
    printf("Postfix : ");
    
    infix_to_postfix(&top, s, postfix);
    
    printf("\nPostfix in the value: ");
    
    result = eval(&top, postfix);
    
    printf("\n\n연산결과 => %d\n", result);
    
    return 0;
}
