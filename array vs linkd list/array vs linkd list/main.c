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
int position = 0;

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

ListNode *linkedDelete(ListNode* head, int value){
    
    ListNode* pre;
    ListNode* deleteNode = head;
    
    count3++;
    
    if (value == 1)
    {
        head = deleteNode -> link;
        return head;
    }
    else{
    while(deleteNode != NULL){
        if ( deleteNode-> data == value){
            pre -> link = deleteNode -> link;

            break;
        }
        pre = deleteNode;
        deleteNode = deleteNode-> link;
    }
        return head;
}

}
    
void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
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
    
    
    printf("\narray\n");
    
    start = clock();
    for(int i = 0; i<10000; i++){
        arr[i] = i;
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    
    printf("\nlinked list\n");
    
    start = clock();
    for(int i = 0; i < 10000; i++)
    {
        head = linkedFirst(head, i);
        
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    printf("\narray ran sum\n");
    start = clock();
    for(int i = 0; i < 1000; i++){
        value = rand() % 10000;
        for(int j = 0; j < 10000; j++)
        {
            if(arr[j] == value){
                arraySum += arr[j];
                count2++;
                
            }
        }
        
    }
    printf("합계 : %.0f\n", arraySum);
    printf("count: %d\n", count2);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    
    printf("\nlinked list ran sum\n");
    start = clock();
        for(int i = 0; i < 1000; i++)
    {
        head = linkedRandom(head, (rand() % 10000));
    }
    printf("합계 : %.0f\n", linkedSum);
    printf("count: %d\n", count1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    

    printf("\narray delete\n");
       start = clock();
       printf("삭제된 데이터 데이터 : \n");
       for(int i = 0; i < 1000; i++){
           value = rand() % 10000;
           for(int j = 0; j < 10000; j++)
           {
               if(arr[j] == value){
                   arr[j] = -1;
                   count4++;
                   
               }
           }
           
       }
       printf("count: %d\n", count4);
       end = clock();
       duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("수행시간은 %lf초 입니다.\n", duration);
    
    printf("\nlinked list delete\n");
    start = clock();

    
        for(int k = 0; k < 1000; k++)
    {
        head = linkedDelete(head, rand() % (10000-k));
    }
    printf("count: %d\n", count3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
   


}



