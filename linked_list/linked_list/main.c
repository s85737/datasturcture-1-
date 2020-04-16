#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
    
} ListNode;

ListNode *insert_first(ListNode* head, int value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    printf("\nnew node의 주소 : %p\n", p);
    
    p->data = value;
    p->link = head;
    head = p;
     
    printf("head의 주소 %p\n", head);
    printf("head의 데이터 %d\n", head->data);
    printf("head의 링크값 %p\n", head->link);
    
    return head;
    
}
//insert_last 구현 제일끝에 어떤 값을 ,노드를 입력하고 마치는 함수 제출

ListNode *insert_last(ListNode* head, int value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    ListNode* temp = head; //임시 값에 head 저장
    printf("\nnew node의 주소 : %p\n", p);
    
 
        p->data = value;
        p->link = NULL; //해당 list의 마지막값 이므로 link에는 NULL 저장

        // 마지막 노드 탐색
        while(temp->link != NULL) temp = temp->link ;

        temp->link = p; // 마지막 노드의 link에 새 노드 주소 저장

    
    printf("new node의 데이터 : %d\n", p->data);
    
    return head;
}


ListNode *insert(ListNode* head, ListNode* pre, element value)
{
    printf("pre의 데이터 : %d\n", pre->data);
    printf("pre의 링크값 : %p\n", pre->link);
    
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    printf("\nnew node의 주소 : %p\n", p);
    
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    
    printf("new node의 데이터 : %d\n", p->data);
    printf("new node의 링크값 : %p\n", p->link);
    
    return head;
    
}

//delete first

ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    
    return head;
}
// 서칭함수
ListNode* search_list(ListNode* head, element x)
{
    ListNode* p = head;
    int count = 0;
    
    while(p != NULL){
        count++;
        if( p->data == x)
            return p;
        p = p-> link;
    }
    return NULL;
}

// delete Linked List

void deleteLinkedList(ListNode** h){
    ListNode* auxilarayNode, * iterator;
    iterator = *h;
    while (iterator){
        printf("삭제할 노드의 데이터 : %d\n", iterator->data);
        auxilarayNode= iterator ->link;
        free(iterator);
        iterator = auxilarayNode;
    }
    h = NULL;
}
//insert position

ListNode* insert_position(ListNode*h, int position, int value)
{
    int k =1;
    ListNode* p = NULL, * q = NULL;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = value;
    p = h;
    
    if  (position ==1){ //1번 위치에 입력
        newNode -> link = p;
        h = newNode;
    }
        
    else{ //position 까지 진행
        while(p != NULL && (k < position )){
        k++;
        q = p;
        p = p ->link;
    }
        
        if(p == NULL){ //끝 노드에 추가
            q->link = newNode;
            newNode->link = NULL;
        }
        else { //중간노드에 추가
            q-> link = newNode;
            newNode->link = p;
        }
        
    }
    return h;

}


void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}

int main(int argc, const char * argv[]) {
    ListNode* head = NULL; // 링크드 리스트 생성
    
    for(int i = 0; i < 5; i++)
    {
        head = insert_first(head, i);
        print_list(head);
    }
    
    //delete_first
    
//    for(int i = 0; i < 5; i++)
//    {
//        head = delete_first(head);
//        print_list(head);
//    }
//
    
    // insert_position
    
    head = insert_position(head, 2, 50);
    print_list(head);
    
    // search data
    
    ListNode* cnt;
    if ((cnt=search_list(head, 50)) != NULL)
        printf("찾는 값 %d은 번째 위치에 있습니다.\n", cnt->data);
    else
        printf("리스트에 값이 없습니다.\n");
    
    // delete Linked List
    deleteLinkedList(&head);
    
    
    ListNode* pre = head;
    head = insert(head, pre, 50);
    print_list(head);
    
    head = insert_last(head, 202020);
    print_list(head);
    
    return 0;
}


//
//  main.c
//  insert_position
//
//  Created by 최제현 on 2020/04/16.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//header를 받을 때 이중 포인터를 사용해서 받아라.
typedef struct StudentList {
    
    char* id;
    char* name;
    int studentId;
    char* grade;
    
    struct StudentList *link; //자기참조 구조체
} StudentList;


void print_list(StudentList* head)
{
    StudentList* result = head;

    
    for (StudentList* p = head; p != NULL; p = p->link)
        printf("%s\t\t%s\t%d\t %s\n", result->id, result->name, result->studentId, result->grade);
}

StudentList* insert_position(StudentList** head, int position, char* id, char* name, int studentId, char* grade)
{
    int k =1;
    StudentList* p = NULL, * q = NULL;
    StudentList* newNode = (StudentList*)malloc(sizeof(StudentList));
    
    newNode->id = id;
    newNode->name = name;
    newNode->studentId = studentId;
    newNode->grade = grade;
    p = head;
    
    if  (position == 1){ //1번 위치에 입력
        newNode->link = p;
        head = newNode;
    }
        
    else{ //position 까지 진행
        while(p != NULL && (k < position )){
        k++;
        q = p;
        p = p ->link;
    }
        
        if(p == NULL){ //끝 노드에 추가
            q->link = newNode;
            newNode->link = NULL;
        }
        else { //중간노드에 추가
            q-> link = newNode;
            newNode->link = p;
        }
       
    }
    return head;

}

StudentList *insert_first(StudentList** head, char* id, char* name, int studentId, char* grade)
{

    StudentList* p = (StudentList*)malloc(sizeof(StudentList));
    
    p->id = id;
    p->name = name;
    p->studentId = studentId;
    p->grade = grade;
    p->link = *head;
    head = p;
    print_list(head);
    
    return *head;
    
}


int main(int argc, const char * argv[]) {
    StudentList* head = NULL;

    
    printf("\n 순서\t\t이름\t\t학번\t\t성적\n");

    printf("---------------------------------------------------\n");
    insert_first(&head, "1", "김철수", 551212, "A"); //head의 주소를 준다. (이중 포인터 사용이므로)
    insert_first(&head, "2", "이영희", 542323, "B");
    insert_first(&head, "3", "박찬호", 533434, "C");
    insert_position(&head, 2, "추가입력" ,"김연아", 567788, "A");
     print_list(head);
    
    return 0;
}
