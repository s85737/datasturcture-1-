//
//  main.c
//  doublepointer
//t
//  Created by 최제현 on 2020/04/16.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//header를 받을 때 이중 포인터를 사용해서 받아라.


typedef struct ListNode {

    char name[20];
    int studentId;
    char grade[2];
    struct ListNode* link; // 구조체 자기참조 ListNode를 가르키는 포인터
    
} ListNode;

ListNode *insert_first(ListNode** head, char* name, int studentId, char* grade)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드 생성

    
    strcpy(p->name, name); //노드에 학생의 정보 저장
    p->studentId = studentId;
    strcpy(p->grade, grade);
    

    p->link = *head; //새로운 노드 p의 link에 header에 저장되었던 포인터 저장
    *head = p; // header에 p로 향하는 포인터 저장

    
    return *head;
    
}

void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s\t%d\t %s\n", p->name, p->studentId, p->grade);
}

ListNode* insert_position(ListNode**head, char* name, int studentId, char* grade)
{
    int k =1;
    ListNode* p = NULL, * q = NULL;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    
    strcpy(newNode->name, name);    //새 노드에 학생정보 저장
    newNode->studentId = studentId;
    strcpy(newNode->grade, grade);
   
    p = *head;
    
    
        while(p != NULL && (k < 3 )){
        k++;
        q = p;
        p = p ->link; //position 위치까지 p이동
    }
        
        if(p == NULL){ //끝 노드에 추가
            q->link = newNode; // p가 끝지점이므로 따라오던 q노드의 link를 새 노드에 저장
            newNode->link = NULL;
        }
        else { //중간노드에 추가
            q-> link = newNode;
            newNode->link = p;
        }
        
    
    return *head;

}

int main(int argc, const char * argv[]) {
    ListNode* head = NULL;
    
    printf("\n이름\t\t학번\t\t성적\n");

    printf("---------------------------------------------------\n");
    
    head = insert_first(&head, "김철수", 551212, "A"); //이중포인터를 매개변수로 받으므로, 인수는 head의 주소
    head = insert_first(&head, "이영희", 542323, "B"); //단일 포인터의 메모리 주소는 이중 포인터와 같다.
    head = insert_first(&head, "박찬호", 533434, "C");
    head = insert_position(&head, "김연아", 567788, "A");
    print_list(head);
    return 0;
}
