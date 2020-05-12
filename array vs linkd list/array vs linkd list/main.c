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
double linkedSum = 0;   // 랜덤 index의 데이터값의 합을 구하기 위한 변수
double dlinkedSum = 0;

typedef struct ListNode { // singly linked list 헤더
    element data;
    struct ListNode* link;
    
} ListNode;

typedef struct DListNode { //doubly linked list 헤더
    dllElement dllData;
    struct DListNode* dllLlink;
    struct DListNode* dllRlink;
    
} DListNode;

// singly linked list 맨앞에 삽입 함수
ListNode *linkedFirst(ListNode* head, int value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    
    p->data = value;
    p->link = head;
    head = p;
    
    return head;
    
}

//doubly linked list 맨앞에 삽입 함수
DListNode *dLinkedFirst(DListNode* dllHead, int value){
    
    DListNode* p = (DListNode*)malloc(sizeof(DListNode));
    
    p->dllData = value;
    
    if(dllHead == NULL) //header 노드 초기화하지 않았을때 동작
    {
        p->dllLlink = NULL;
        p->dllRlink = dllHead;
        dllHead = p;
    }
    else{ // header 노드가 이미 초기화 되었을때 맨 앞에 삽입
        
        p->dllLlink = NULL;
        p->dllRlink = dllHead;
        dllHead->dllLlink = p; // header 노드를 초기화 하지 않았을때 에러가 발생할 수 있는 code
        dllHead = p;
    }
    
    
    
    return dllHead;
}

//singly linked list 랜덤 index의 데이터의 합 함수
ListNode *linkedRandom(ListNode* head, int value){

    
    ListNode* p = head;
    
    
    
    while(p != NULL){
        
        if ( p-> data == value){ //랜덤으로 준 value 값과 해당 데이터가 같을 시 linkedSum에 더함
            linkedSum += (p->data);
            return head; //조건 만족시 return
        }
        p = p-> link; //if문 조건 충족하지 않을시 계속해서 탐색
    }
    
    return head;
    
}

//doubly linked list 랜덤 index의 데이터 합 함수
DListNode *dlinkedRandom(DListNode* dllHead, int value){
    
    DListNode* p = dllHead;
    
    
    
    while(p != NULL){
        
        if ( p-> dllData == value){ //랜덤으로 준 value 값과 해당 데이터가 같을 시 dlinkedSum에 더함
            dlinkedSum += (p->dllData);
            return dllHead; //조건 만족시 return
        }
        p = p->dllRlink; //if문 조건 충족하지 않을시 계속해서 탐색
    }
    
    return dllHead;
    
}

//singly linked list 의 랜덤 index 삭제 함수
ListNode *linkedDelete(ListNode* head, int value){
    
    ListNode* pre; //삭제할 노드 뒤에 따라다니는 노드
    ListNode* deleteNode = head; // 삭제할 노드
    
    
    if ((deleteNode -> data == value) && (deleteNode == head)) //value 가 맨앞의 노드일 때 삭제 예외처리
    {
        head = deleteNode -> link; //삭제할 노드의 link값을 header에 저장
        return head;
    }
    else{
        while(deleteNode != NULL){
            if (deleteNode-> data == value){ // 그외 상황일 때 실행
                pre -> link = deleteNode -> link;  // 삭제할 노드의 앞의 노드의 Link 값을 삭제할 노드의 link 값 저장
                
                break;
            }
            pre = deleteNode; //삭제할 노드의 이전위치 저장
            deleteNode = deleteNode-> link; //해당 value를 찾을때 까지 계속해서 탐색
        }
        return head;
    }
    
}

//doubly linked list 랜덤 index값 삭제함수
DListNode *dlinkedDelete(DListNode* dllHead, int value){
    
    DListNode* pre; //삭제할 노드 뒤에 따라다니는 노드
    DListNode* deleteNode = dllHead; // 삭제할 노드
    
    
    if ((deleteNode -> dllData == value) && (deleteNode == dllHead)) //value 가 맨앞의 노드(head)일 때 삭제 예외처리
    {
        dllHead = deleteNode -> dllRlink;  //삭제할 노드의 link값을 header에 저장
        return dllHead;
    }
    else{
        while(deleteNode != NULL){
            if ( deleteNode-> dllData == value && deleteNode -> dllRlink != NULL){ //그 외 일때 동작
                pre -> dllRlink = deleteNode -> dllRlink;
                deleteNode -> dllRlink -> dllLlink = pre; //tail일때 에러가 발생할수 있는 code
                break;
            }
            else if( deleteNode-> dllData == value && deleteNode -> dllRlink == NULL){ // value 가 맨뒤의 노드(tail)일 때 삭제 예외처리
                pre -> dllRlink = deleteNode -> dllRlink;
                
                break;
            }
            pre = deleteNode;
            deleteNode = deleteNode-> dllRlink;
            
        }
        return dllHead;
    }
    
}

//linked list 함수 동작을 테스트하기 위한 함수
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
    int arr[10000]; //index가 10000개인 배열 생성
    int value = 0;
    srand((unsigned int)time(NULL)); //난수생성
    double arraySum=0; // 랜덤 index의 데이터값의 합을 구하기 위한 변수
    
    printf("\nArray, Singly Linked List, Doubly Linked List 비교\n");
    
    
    printf("\nArray, Singly Linked List, Doubly Linked List 맨앞에 삽입 속도비교\n");
    
    printf("\narray\n");
    
    //index가 10000개인 배열 생성
    start = clock();
    for(int i = 0; i<10000; i++){
        arr[i] = i;
        //testcode        printf("%d->",arr[i]);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    
    
    printf("\nlinked list\n");
    
    //index가 10000개인 singly linked list 생성
    start = clock();
    for(int i = 0; i < 10000; i++){
        head = linkedFirst(head, i);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    //    print_list(head);
    
    // index가 10000개인 doubly linked list 생성
    printf("\n doublelylinked list\n");
    
    start = clock();
    for(int i = 0; i < 10000; i++){
        dllHead = dLinkedFirst(dllHead, i);
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    //    print_dllList(dllHead);
    
    
    printf("\nArray, Singly Linked List, Doubly Linked List 랜덤 index안의 데이터의 합 \n");
    
    //array일때 랜덤 index의 합
    printf("\narray ran sum\n");
    start = clock();
    for(int i = 0; i < 1000; i++){
        value = rand() % 10000; // 0~ 9999까지의 난수생성
        for(int j = 0; j < 10000; j++){
            if(arr[j] == value){
                arraySum += arr[j];
                break; //해당 index의 데이터 탐색 후 발견하면 동작중지
            }
        }
        
    }
    printf("합계 : %.0f\n", arraySum);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n\n", duration);
    
    //singly linked list일때 랜덤 index의 합
    printf("\nlinked list ran sum\n");
    start = clock();
    for(int i = 0; i < 1000; i++){
        head = linkedRandom(head, (rand() % 10000));
    }
    printf("합계 : %.0f\n", linkedSum);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    //doubly linked list일때 랜덤 index의 합
    printf("\ndoubly linked list ran sum\n");
    start = clock();
    for(int i = 0; i < 1000; i++){
        dllHead = dlinkedRandom(dllHead, (rand() % 10000));
    }
    printf("합계 : %.0f\n", dlinkedSum);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    
    printf("\nArray, Singly Linked List, Doubly Linked List 랜덤 index안의 데이터의 삭제 \n");
    
    //array일때 랜덤 index 데이터 삭제
    printf("\narray delete\n");
    start = clock();
    printf("삭제된 데이터 데이터 : \n");
    for(int i = 0; i < 1000; i++){
        value = rand() % 10000;
        for(int j = 0; j < 10000; j++)
        {
            if(arr[j] == value){
                arr[j] = -1;
                //                   printf("%d->",arr[i]);
            }
        }
        
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    //singly linked list 일때 랜덤 index 데이터 삭제
    printf("\nlinked list delete\n");
    start = clock();
    
    
    for(int k = 0; k < 1000; k++){
        head = linkedDelete(head, (rand()%(10000-k))); //난수 생성 범위가 계속해서 줄어듬
    }
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    
    //doubly linked list 일때 랜덤 index 데이터 삭제
    printf("\ndoubly linked list delete\n");
    start = clock();
    //    print_list(head);
    
    
    for(int k = 0; k < 1000; k++){
        dllHead = dlinkedDelete(dllHead,(rand()%(10000-k)));
    }
    
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("수행시간은 %lf초 입니다.\n", duration);
    //    print_dllList(dllHead);
    
}



