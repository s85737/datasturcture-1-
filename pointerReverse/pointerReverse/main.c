//
//  main.c
//  pointerReverse
//
//  Created by 최제현 on 2020/03/30.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>

char reverse(char *input, char *output);

int main(void) {
    char s1[100], s2[100], *p, *q;
    
    printf("문자열 입력: ");
    scanf("%s", s1);
    
    
    p = s1; // 입력 문자열이 저장된 배열 s1에 포인터 P 연결
    q = s2; // 입력 문자열을 저장할 배열 s2에 포인터 q 연결
    
    reverse(p, q);
    
    printf("역순문자열 : %s \n", s2);
}

char reverse(char *input, char *output){ //입력된 
    
    
    char *init = input; // 시작점 저장

    while (*input != '\0') input++ ; // 문자열 s1 배열의 끝지점 탐색

    for (input--; input >= init; input--, output++) *output = *input;
       // s1의 문자를 역순으로 s2문자열에 저장

    *output = '\0'; // 배열 s2에 문자열 끝을 지정하기 위해 '\0' 저장
    
    return 0;
}
