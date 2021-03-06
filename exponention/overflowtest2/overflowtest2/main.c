//
//  main.c
//  overflowtest2
//
//  Created by 최제현 on 2020/03/27.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <time.h>

//recursion 방식
int countIter = 0;
int countRec = 0;
int recursion(int params);
int iteration(int params);


int recursion(int params){
    
    countRec++;
    
    if ( params == 0 ) return 0;
    if ( params == 1 ) return 1;
    return (recursion(params-1) + recursion(params-2));
}

//interation 방식

int interation(int params){
    if ( params == 0 ) return 0;
    if ( params == 1 ) return 1;
    
    int pp = 0;
    int p = 1;
    int result =0;
    
    
    countIter++;
    printf("Function fibIter(%d) call%dtimes\n", params, countIter);
    
    for (int i = 2; i <= params; i++){
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
}


int main(int argc, const char * argv[]) {
 
    int number, result; //
       
       clock_t startRec, stopRec, startIter, stopIter;
       double durationRec, durationIter;
       printf("\n 피보나치 수 입력 : ");
       scanf("%d", &number);
    
       printf("interation 방식: \n");
       
       startIter = clock();
       result = interation(number);
       stopIter = clock();
       
       durationIter = (double)(stopIter - startIter) / CLOCKS_PER_SEC;
       
       printf("\n Time duration : %lfs\n", durationIter);
    
       printf("\n recursion 방식: \n");
       
       startRec = clock();
       result = recursion(number);
       stopRec = clock();
       
       durationRec = (double)(stopRec - startRec) / CLOCKS_PER_SEC;
       
       printf("\n Time duration : %lfs\n", durationRec);
    
    return 0;
}
