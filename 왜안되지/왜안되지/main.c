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
    

    
    printf("linked list\n");
    
    start = clock();
    for(int i = 0; i < 10; i++)
    {
        head = linkedFirst(head, i);
        
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
   
    printf("linked list delete\n");
    start = clock();

       head = linkedDelete(head, 1);
    
    printf("count: %d\n", count3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    print_list(head);

}



