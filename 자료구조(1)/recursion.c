//
//  recursion.c
//  자료구조(1)
//
//  Created by 최제현 on 2020/03/23.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// iteration 방식 factorial
int iFactorial(int paramNum){
    int result=1;
    
    for (int i = 1; i <= paramNum; i++){
        result = result * i;
    };
    
    return result;
}

// recursion 방식 factorial
int rFactorial(int paramNum){
    if(paramNum <= 1) return 1;  // n이 1 이하로 갈 경우 1을 반환하고 재귀호출 종료
    else return (paramNum * rFactorial(paramNum-1));
}

int compare(void) {
    clock_t startIter, stopIter, startRecu, stopRecu;
    double durationIter, durationRecu;
    double result = 0;
    int argNum=0;
    while(1){
        printf("몇 factorial 을 계산할까요? 0을 입력하면 종료합니다.\n");
        scanf("%d", &argNum);
        if(argNum>0){
            //interation 방식 시간측정
            startIter = clock();  // 시간 측정 시작
            result = iFactorial(argNum);
            stopIter = clock(); // 시간 측정 중지
            // 측정한 시간을 초 단위 변환
            durationIter = (double)(stopIter - startIter) / CLOCKS_PER_SEC;
            printf("%d!의 interation 방식의 수행시간은 %lf초 입니다.\n",argNum, durationIter);
            printf("답 : %.0lf\n", result);
            
            //recursion 방식 시간측정
            startRecu = clock();  // 시간 측정 시작
            result = rFactorial(argNum);
            stopRecu = clock(); // 시간 측정 중지
            durationRecu = (double)(stopRecu - startRecu) / CLOCKS_PER_SEC;
            printf("%d!의 recursion 방식의 수행시간은 %lf초 입니다.\n",argNum ,durationRecu);
            printf("답 : %.0lf\n", result);
            continue;
            }
        else printf("프로그램을 종료합니다.\n");
        return 0;
    }
}
