#include <stdio.h>
#include <string.h>


// 1. 목록보기2. 사용자추가3. 사용자비교4. 사용자삭제5. 종료

//구조체배열에서의index

int count = 0;



//주소록구조체

struct addressBook {

    char name[10];

    char phone[20];

    char addr[10];

    int age;

};

struct addressBook aB_2020[50]; //최소한34바이트공간할당됨


//사용자보기

void list() {

    int i;

    if (count == 0) printf("등록된사람이없습니다. \n\n");

    else {

        printf("\n 이름\t\t전화번호\t\t주소\t\t나이\n");

        printf("---------------------------------------------------\n");

        for (i = 0; i < count; i++) {

            printf("%s\t %s\t %s\t %d\n", aB_2020[i].name, aB_2020[i].phone, aB_2020[i].addr, aB_2020[i].age);

        }

    }

    }
    
    
    
//사 용자추가
    
void append(){

 count++;

    printf("추가할이름: "); scanf("%s", aB_2020[count - 1].name); //count 0번에구조체가들어있기때문에.name 식으로구조체의이름항목변경

    printf("추가할전화번호: "); scanf("%s", aB_2020[count - 1].phone);

    printf("추가할주소: "); scanf("%s", aB_2020[count - 1].addr);
    
    printf("추가할나이: "); scanf("%d", &aB_2020[count - 1].age); // age는배열로선언하지않았기때문에주소에다가입력을받아야함

    printf("-------추가완료------\n");

    }


// 과제

//사용자검색

    void search() {
        char name[10];
   
        if (count > 0){
            printf("이름을입력해주세요: ");
            scanf("%s", name);
    
            for (int i = 0; i < 50; i++){ // 주소록최대등록수까지탐색
                if(!strcmp(name, aB_2020[i].name)){ //strcmp는문자열이일치할때0을반환
                    printf("검색성공!\n");
     
                    printf("\n 이름\t\t전화번호\t\t주소\t\t나이\n");
                    printf("%s\t %s\t %s\t %d\n", aB_2020[i].name, aB_2020[i].phone, aB_2020[i].addr, aB_2020[i].age);
                    return;
                }
     
            }
            printf("주소록에서없는사람입니다. 대소문자를확인해주세요.\n"); //일치하는이름이없을시
            return;
        }
        else{ //주소록에등록된사람이없을시
            printf("등록된사람이없습니다.");
        }
    }
   





//사용자삭제

    void del() {
        char name[10];
   
        if (count > 0){
            printf("이름을입력해주세요: ");
            scanf("%s", name);
    
            for (int i = 0; i < 50; i++){ // 주소록최대등록수까지탐색
                if(!strcmp(name, aB_2020[i].name)){ //strcmp는문자열이일치할때0을반환
                    printf("검색성공!\n");
    
                    for (int j = i; j < count ; j++){ // 삭제하고자하는이름앞부분부터복사후삭제하고싶은이름부터덮어쓴다.
                        strcpy(aB_2020[j].name, aB_2020[j+1].name);
                        strcpy(aB_2020[j].phone, aB_2020[j+1].phone);
                        strcpy(aB_2020[j].addr, aB_2020[j+1].addr);
                        aB_2020[j].age = aB_2020[j+1].age;
        
                    }
                    count --; //사람수1명삭제
                    printf("삭제성공!\n");
                    return;
       
                }
     
            }
            printf("주소록에서없는사람입니다. 대소문자를확인해주세요.\n"); //일치하는이름이없을시
            return;
        }
        else{ //주소록에등록된사람이없을시
            printf("이미등록된사람이없습니다.");
    
        }
   
    }






    void menu()

    {

        char choice;

        do {

            printf("\n\n============================================================\n");

            printf("-------------------------- 주소록메뉴-------------------------\n");



            printf(" 1) 목록보기2)사용자추가3) 사용자검색4) 사용자삭제5) 종료\n");

            printf("============================================================\n");



            scanf("%c", &choice); getchar(); //입력중enter값제거

            switch (choice) {



                case '1': list(); break;

                case '2': append(); getchar(); break;

                case '3': search(); getchar(); break;

                case '4': del(); getchar(); break;

                case '5': printf("\n 주소록프로그램을종료합니다.\n"); return;



                default: printf("메뉴번호를다시확인해주세요\n");

            }

        } while (choice != '5');

    }





    int main() {

    menu();

    }


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

    char name[10];
    int studentId;
    char grade[2];
    struct ListNode* link;
    
} ListNode;

ListNode *insert_first(ListNode** head, char* name, int studentId, char* grade)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    
    printf("추가할이름: "); scanf("%s", p->name);

    printf("추가할학번: "); scanf("%d", &p->studentId);
    
    printf("추가할석정: "); scanf("%s", p->grade);
    


    printf("-------추가완료------\n");
    

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
    
    printf("추가할이름: "); scanf("%s", p->name);

    printf("추가할학번: "); scanf("%d", &p->studentId);
    
    printf("추가할석정: "); scanf("%s", p->grade);
    


    printf("-------추가완료------\n");
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
    print_list(head);
    head = insert_position(&head, 3, "김연아", 567788, "A");
    print_list(head);
    return 0;
}
