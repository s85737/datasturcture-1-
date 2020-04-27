//
//  main.c
//  123
//
//  Created by 최제현 on 2020/04/23.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a[] = {10,20,30,40,50};
    int * p = a+2;
    int ** q = &p;
    
    printf("%d\n", p[1]);
    printf("%d\n", *(*q+2));
    printf("%d\n", *q+2);
}
