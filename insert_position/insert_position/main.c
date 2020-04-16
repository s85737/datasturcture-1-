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
