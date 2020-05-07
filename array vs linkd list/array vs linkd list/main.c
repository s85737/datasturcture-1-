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
typedef int dllElement;
double linkedSum = 0;
double dlinkedSum = 0;
int count1=0;
int count2=0;
int count3=0;
int count4=0;
int count5=0;
int count6=0;
int count7=0;
int position = 0;

typedef struct ListNode {
    element data;
    struct ListNode* link;
    
} ListNode;

typedef struct DListNode {
    dllElement dllData;
    struct DListNode* dllLlink;
    struct DListNode* dllRlink;
    
} DListNode;


ListNode *linkedFirst(ListNode* head, int value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    
    p->data = value;
    p->link = head;
    head = p;
    
    return head;
    
}

DListNode *dLinkedFirst(DListNode* dllHead, int value){
    
    DListNode* p = (DListNode*)malloc(sizeof(DListNode));
    
    p->dllData = value;
    
    if(dllHead == NULL)
    {
        p->dllLlink = NULL;
        p->dllRlink = dllHead;
        dllHead = p;
    }
    else{
    
    p->dllLlink = NULL;
    p->dllRlink = dllHead;
    dllHead->dllLlink = p;
    dllHead = p;
    }
    
    
    count5 ++;
    
    return dllHead;
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

DListNode *dlinkedRandom(DListNode* dllHead, int value){
    
    DListNode* p = dllHead;
    
    
    
    while(p != NULL){
        
        if ( p-> dllData == value){
            dlinkedSum += (p->dllData);
            count6++;
        }
        p = p->dllRlink;
    }
    
    return dllHead;
    
}

ListNode *linkedDelete(ListNode* head, int value){
    
    ListNode* pre;
    ListNode* deleteNode = head;
    
    count3++;
    
    if ((deleteNode -> data == value) && (deleteNode == head))
    {
        head = deleteNode -> link;
        return head;
    }
    else{
    while(deleteNode != NULL){
        if (deleteNode-> data == value){
            pre -> link = deleteNode -> link;

            break;
        }
        pre = deleteNode;
        deleteNode = deleteNode-> link;
    }
        return head;
}

}

DListNode *dlinkedDelete(DListNode* dllHead, int value){
    
    DListNode* pre;
    DListNode* deleteNode = dllHead;
    
    count7++;
    
    if ((deleteNode -> dllData == value) && (deleteNode == dllHead))
    {
        dllHead = deleteNode -> dllRlink;
        return dllHead;
    }
    else{
    while(deleteNode != NULL){
        if ( deleteNode-> dllData == value && deleteNode -> dllRlink != NULL){
            pre -> dllRlink = deleteNode -> dllRlink;
            deleteNode -> dllRlink -> dllLlink = pre;
            break;
        }
        else if( deleteNode-> dllData == value && deleteNode -> dllRlink == NULL){
            pre -> dllRlink = deleteNode -> dllRlink;
            
            break;
        }
        pre = deleteNode;
        deleteNode = deleteNode-> dllRlink;
        
    }
        return dllHead;
}

}
    
void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

void print_dllList(DListNode* dllHead)
{
    for (DListNode* p = dllHead; p != NULL; p = p->dllRlink)
        printf("<-|%d|->", p->dllData);
    printf("NULL \n");
}

int main(int argc, const char * argv[]) {
    ListNode* head = NULL; // 링크드 리스트 생성
    DListNode* dllHead = NULL;
    
    
    clock_t start, end;
    double duration;
    int arr[10000];
    int value = 0;
    srand((unsigned int)time(NULL));
    double arraySum=0;
    
    printf("\nArray, Singly Linked List, Doubly Linked List 비교\n");
    
    
    printf("\narray\n");
    
    start = clock();
    for(int i = 0; i<10000; i++){
        arr[i] = i;
//        printf("%d->",arr[i]);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    
    
    printf("\nlinked list\n");
    
    start = clock();
    for(int i = 0; i < 10; i++){
        head = linkedFirst(head, i);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
//    print_list(head);
    printf("\n doublelylinked list\n");
    
    start = clock();
    for(int i = 0; i < 10; i++){
    dllHead = dLinkedFirst(dllHead, i);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
//    print_dllList(dllHead);
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    printf("count: %d\n", count5);
    
    
    
    printf("\narray ran sum\n");
    start = clock();
    for(int i = 0; i < 1000; i++){
        value = rand() % 10000;
        for(int j = 0; j < 10000; j++){
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
        for(int i = 0; i < 1000; i++){
        head = linkedRandom(head, (rand() % 10000));
    }
    printf("합계 : %.0f\n", linkedSum);
    printf("count: %d\n", count1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    
    printf("\ndoubly linked list ran sum\n");
    start = clock();
        for(int i = 0; i < 1000; i++){
        dllHead = dlinkedRandom(dllHead, (rand() % 10000));
    }
    printf("합계 : %.0f\n", dlinkedSum);
    printf("count: %d\n", count6);
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

    
        for(int k = 0; k < 3; k++){
        head = linkedDelete(head, (rand()%10-k));
    }
    printf("count: %d\n", count3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
   printf("\ndoubly linked list delete\n");
   start = clock();
    print_list(head);

   
       for(int k = 0; k < 3; k++){
       dllHead = dlinkedDelete(dllHead,(rand()%10-k));
   }
   printf("count: %d\n", count7);
   end = clock();
   duration = (double)(end - start) / CLOCKS_PER_SEC;
   printf("수행시간은 %lf초 입니다.\n", duration);
    print_dllList(dllHead);

}



