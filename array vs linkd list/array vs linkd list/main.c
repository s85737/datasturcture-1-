//
//  main.c
//  array vs linkd list
//
//  Created by 최제현 on 2020/04/27.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;
double linkedSum = 0;
int count1=0;
int count2=0;
int count3=0;
int count4=0;

typedef struct ListNode {
    element data;
    struct ListNode* link;
    
} ListNode;

ListNode *linkedFirst(ListNode* head, int value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    
    p->data = value;
    p->link = head;
    head = p;
    
    return head;
    
}

ListNode *linkedRandom(ListNode* head, int value){
    
    ListNode* p = head;
    
    
    
    while(p != NULL){
        
        if ( p-> data == value){
            linkedSum += (p->data);
            count1++;
        }
        p = p-> link;
    }
    
    return head;
    
}

void linkedDelete(ListNode** head, int value){
    
    ListNode* p = *head;
    ListNode* q;
    
    if (value == 1)
    {
        *head = *head -> link;
    }
    else{
    while(p != NULL){
        
        if ( p-> data == value){
            p->data = -1;
            count3++;
        }
        p = p-> link;
        printf("pre의 데이터 : %d\n", p->data);
    }
    }
    
}

int main(int argc, const char * argv[]) {
    ListNode* head = NULL; // 링크드 리스트 생성
    clock_t start, end;
    double duration;
    int arr[10000];
    int value = 0;
    srand((unsigned int)time(NULL));
    double arraySum=0;
    
    printf("\nArray와 Singly Linked List 비교\n");
    
    
    printf("array\n");
    
    start = clock();
    for(int i = 0; i<10000; i++){
        arr[i] = i;
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    
    printf("linked list\n");
    
    start = clock();
    for(int i = 0; i < 10000; i++)
    {
        head = linkedFirst(head, i);
        
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    printf("array ran sum\n");
    start = clock();
    for(int j = 0; j < 1000; j++){
        value = rand() % 10000;
        for(int l = 0; l < 10000; l++)
        {
            if(arr[l] == value){
                arraySum += arr[l];
                count2++;
                
            }
        }
        
    }
    printf("합계 : %.0f\n", arraySum);
    printf("count: %d\n", count2);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    
    printf("linked list ran sum\n");
    start = clock();
        for(int k = 0; k < 1000; k++)
    {
        head = linkedRandom(head, (rand() % 10000));
    }
    printf("합계 : %.0f\n", linkedSum);
    printf("count: %d\n", count1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    
    printf("linked list delete\n");
    start = clock();
        for(int k = 0; k < 1000; k++)
    {
        head = linkedDelete(&head, (rand() % 10000)-k);
    }
    
    printf("count: %d\n", count3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
}



