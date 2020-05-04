//
//  main.c
//  stack
//
//  Created by 최제현 on 2020/05/01.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define max_stack_size 3

typedef int element;

element stack[max_stack_size];
int top = -1;

//공백 상태 검출 함수

int is_empty()
{
    return (top == -1);
}

//포화 상태 검출 함수
int is_full()
{
    return (top == (max_stack_size -1));
}

// 삽입 함수

void push(element item)
{
    if(is_full()){
        fprintf(stderr, "스택 포화 에러\n");
        
    }
    else stack[++top] = item;
}
//삭ㅈ 함수

element pop()
{
    if (is_empty()){
        fprintf(stderr, "스택 공백 에러\n"); //파일에다가 출력. stderr 에러 출력 (std =화면)
        exit(1);
    }
    else return stack[top--];
}

int main(void)
{
    push(1);
    push(2);
    push(3);
    push(4);

    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    return 0;
    
}


