//
//  recursionOverflow.c
//  자료구조(1)
//
//  Created by 최제현 on 2020/03/23.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// 함수 호출 count
int count = 0;

// recursion 방식 factorial

int recursion(int paramNum){
    count++; // 함수가 한번 호출 될 때마다 1번 count
    if(paramNum <= 1) return 1; // n이 1 이하로 갈 경우 1을 반환하고 재귀호출 종료
    else{
        printf("%d회 호출\n", count);
        return (paramNum * recursion(paramNum-1));
    }
}

int compare(void) {
    
    int argNum;
    double result=0;
    
    printf("몇 factorial 을 계산할까요?\n");
    scanf("%d", &argNum);
    
    result = recursion(argNum);
    
    printf("결과%.0lf\n", result); //함수가 게산 완료했을 때 결과출력
    return 0;
}


