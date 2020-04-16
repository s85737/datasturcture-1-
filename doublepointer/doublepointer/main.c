//
//  main.c
//  doublepointer
//
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
    struct ListNode* link;
    
} ListNode;

ListNode *insert_first(ListNode** head, char* name, int studentId, char* grade)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    
    strcpy(p->name, name);
    p->studentId = studentId;
    strcpy(p->grade, grade);
    

    p->link = *head;
    *head = p;

    
    return *head;
    
}

void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s\t%d\t %s\n", p->name, p->studentId, p->grade);
}

ListNode* insert_position(ListNode**head, int position, char* name, int studentId, char* grade)
{
    int k =1;
    ListNode* p = NULL, * q = NULL;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    
    strcpy(newNode->name, name);
    newNode->studentId = studentId;
    strcpy(newNode->grade, grade);
   
    p = *head;
    
    
    
    if  (position ==1){ //1번 위치에 입력
        newNode -> link = p;
        *head = newNode;
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
    return *head;

}

int main(int argc, const char * argv[]) {
    ListNode* head = NULL;
    
    printf("\n이름\t\t학번\t\t성적\n");

    printf("---------------------------------------------------\n");
    
    head = insert_first(&head, "김철수", 551212, "A");
    head = insert_first(&head, "이영희", 542323, "B");
    head = insert_first(&head, "박찬호", 533434, "C");
    head = insert_position(&head, 3, "김연아", 567788, "A");
    print_list(head);
    return 0;
}
