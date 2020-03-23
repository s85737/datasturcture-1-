//
//  main.c
//  자료구조(1)
//
//  Created by 최제현 on 2020/03/20.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// iteration factorial
int iFactorial(int paramNum){
    int i =1;
    int result=1;
    for (i = 1; i <= paramNum; i++){
        result = result * i;
    };
    
    return result;
}

// recursion factorial

int rFactorial(int paramNum){
    if(paramNum <= 1) return 1;
    else return (paramNum * rFactorial(paramNum-1));
}

int main() {
    clock_t startIter, stopIter, startRecu, stopRecu;
    double durationIter, durationRecu;
    double finalResult = 0;
    int argNum;
    
    printf("몇 펙토리얼?\n");
    scanf("%d", &argNum);
    
    //interation 방식
    startIter = clock();  // 시간 측정 시작
    finalResult = iFactorial(argNum);
    stopIter = clock(); // 시간 측정 중지
    durationIter = (double)(stopIter - startIter) / CLOCKS_PER_SEC;
    printf("interation 방식의 수행시간은 %f초 입니다.\n", durationIter);
    printf("답 : %f\n", finalResult);
    
    //recursion 방식
    startRecu = clock();  // 시간 측정 시작
    finalResult = iFactorial(argNum);
    stopRecu = clock(); // 시간 측정 중지
    durationRecu = (double)(stopRecu - startRecu) / CLOCKS_PER_SEC;
    printf("recursion 방식의 수행시간은 %f초 입니다.\n", durationRecu);
    printf("답 : %f\n", finalResult);
    
    return 0;
}
