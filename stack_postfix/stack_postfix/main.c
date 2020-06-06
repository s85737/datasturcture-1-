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


//stack push함수

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

//stack pop함수
element pop(stackNode** top){
    element item;
    stackNode** temp; //노드를 메모리에서 해제 시키기 위해 따로 temp 사용
    
    if(is_empty(*top))
    {
        printf("stack is empty!\n");
        return -1; // 예외처리 : 스택이 비었을경우 -1 리턴
    }
    else{
        temp = *top;
        item = (*top)->data;
        *top = (*top)->link;
        free(temp);
        return item;
    }
}

//요소를 스택에서 삭제하지 않고 데이터 추출하는 함수
element peek(stackNode** top){
    if(*top == NULL){
        printf("\n\n Stack is empty\n");
        exit(1);
    }
    else{
        return((*top)->data);
    }

}

//연산자 우선순위 반환 함수
int prec(char op){
    switch(op){
        case '(': case ')':
            return 0; //괄호는 출력하지않음
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
    }
    return -1; //예외처리 : 그 외의 경우 -1리턴
}

// infix 에서 postfix로의 변환 함수
void infix_to_postfix(stackNode** s, char* input, char* postfix){
    int i = 0;
    char ch, top;
    int len = strlen(input);
    
    for ( i = 0; i < len; i++){
        ch = input[i];
        switch (ch) {
            case '+': case '-': case '*': case '/': // operator 일 경우
                // stack에 있는 연산자의 우선 순위 검사
                // stack안의 operator가 우선순위가 input의 operator 보다 더 크거나 같으면 출력
                while(!is_empty(&s) && (prec(ch)) <= prec(peek(&s))){
                    *postfix++ = pop(&s); //pop실행 후 다음 저장을 위해 포인터 조정
                    printf("%c" , *(postfix - 1)); // 포인터 조정 전의 data 출력
                    
                }
                
                push(&s, ch); //우선순위
                break;
                
            case '(': //왼쪽 괄호일경우 스택에 push
                push(&s, ch);
                break;
            case ')': //오른쪽 괄호일 경우 출력
                top = pop(&s);
                
                while(top != '('){ // 왼쪽 괄호를 만날때 까지 stack 안의 operator 출력
                    printf("%c", top);
                    *postfix++ = top; //stack에 저장된 operator 배열에 저장 후 포인터 조정
                    top = pop(&s);
                }
                
                break;
                
            default: //operand 일 경우 stack에 넣지않고 바로 출력
                printf("%c", ch);
                *postfix++ = ch; // 배열에 저장후 다음 저장을 위해 포인터 조정
                break;
        }
    }
    
    while(!is_empty(*s)){ // 스택에 저장된 연산자들 출력 및 배열에 저장
        *postfix++ = pop(&s);
        printf("%c", *(postfix-1));
    }
}

//postfix 변환식 연산 함수
int eval(stackNode** s,char* exp){
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    
    for ( i= 0; i<len; i++){
        ch = exp[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/'){ // 입력된 값이 operand 일 경우 스택에 저장
            value = ch - '0'; //ASCII 코드로 저장되므로 '0' 빼준다.
            push(&s, value);
        }
        else { // operator 일 경우: operand 2개를 스택에서 pop하고 결과를 스택에 push
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch){
                case '+' :
                    push(&s, op1+op2);
                    break;
                case '-' :
                    push(&s, op1-op2);
                    break;
                case '*' :
                    push(&s, op1*op2);
                    break;
                case '/' :
                    push(&s, op1/op2);
                    break;
            }
        }
    }
    return pop(&s);
    
}

//스택 출력함수
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
//        printf("\nStack is empty\n");
        return 1;
    }
    else return 0;
}


int main(int argc, const char * argv[]) {

    element item;
    stackNode* top;
    top = createStack();
    
    
    int result;
    char* input = "(1+2+3)*(2+3)*2+4";
//    char* s = "8/4+4/2+8*2+4";
    
    char postfix[30] = {0};
    
    printf("\n 연결 스택 연산 \n");
    
    //push,pop 정상동작, 스택이 비었을 경우 정상출력 되는지 test
    
    push(&top, 3);
    push(&top, 6);
    push(&top, 9);
    
    printStack(&top);

    item = peek(&top);
    printf("peek => %d\n", item);

    
    for (int i =0; i <4; i++){
        item = pop(&top);
        if(item != -1) printf("pop => %d\n", item); //스택이 비었을 경우는 item 값 출력하지 않음
        }

    printf("\n------------\n");
    printf(" infix에서 postfix 변환후 postfix 연산 \n\n");
    //1. infix to postfix 변환
    printf("infix : %s \n", input);
    printf("Postfix : ");
    
    infix_to_postfix(&top, input, postfix);
    
    printf("\n변수에 저장된 postfix : %s", postfix);
    
    //postfix 연산
    result = eval(&top, postfix);
    
    printf("\n\n연산결과 ==> %d\n", result);
    
    return 0;
}
