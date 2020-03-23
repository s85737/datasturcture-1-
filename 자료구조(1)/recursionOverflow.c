//
//  recursionOverflow.c
//  자료구조(1)
//
//  Created by 최제현 on 2020/03/23.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 호출 count
int count = 0;

// iteration 방식 factorial
int iteration(int paramNum){
    int result=1;
    
    for (int i = 1; i <= paramNum; i++){
        result = result * i;
    };
    
    return result;
}

// recursion 방식 factorial

int recursion(int paramNum){
    count++; // 함수가 한번 호출 될 때마다 1번 count
    if(paramNum <= 1) return 1; // n이 1 이하로 갈 경우 1을 반환하고 재귀호출 종료
    else{
        printf("%d회 호출\n", count);
        return (paramNum * recursion(paramNum-1));
    }
}

int main(void) {
    clock_t start, stop;
    double duration;
    int argNum;
    double iteResult=0;
    double recResult=0;
    
    printf("몇 factorial 을 계산할까요?\n");
    scanf("%d", &argNum);
    // interation 방식의 수행시간 측정
    start = clock();  // 시간 측정 시작
    iteResult = iteration(argNum);
    stop = clock(); // 시간 측정 중지
               // 측정한 시간을 초 단위 변환
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("%d!의 interation 방식의 수행시간은 %lf초 입니다.\n",argNum, duration);
    printf("답 : %.0lf\n", iteResult);
    recResult = recursion(argNum); // recursion 방식이 stack overflow가 되지않고 수행완료시 결과출력
    printf("답 : %.0lf\n", recResult);
    
    return 0;
}

