//
//  main.c
//  주소록
//
//  Created by 최제현 on 2020/04/02.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <string.h>


// 1. 목록 보기 2. 사용자 추가 3. 사용자 비교 4. 사용자 삭제 5. 종료

//구조체 배열에서의 index

int count = 0;



//주소록 구조체

struct addressBook {

    char name[10];

    char phone[20];

    char addr[10];

    int age;

};

struct addressBook aB_2020[50]; //최소한 34바이트 공간 할당됨


//사용자 보기

void list() {

    int i;

    if (count == 0) printf("등록된 사람이 없습니다. \n\n");

    else {

        printf("\n 이름 \t\t전화번호 \t\t주소 \t\t나이\n");

        printf("---------------------------------------------------\n");

        for (i = 0; i < count; i++) {

            printf("%s\t %s\t %s\t %d\n", aB_2020[i].name, aB_2020[i].phone, aB_2020[i].addr, aB_2020[i].age);

        }

    }

}



//사용자 추가

void append(){

    count++;

    printf("추가할 이름: "); scanf("%s", aB_2020[count - 1].name); //count 0번에 구조체가 들어있기 때문에 .name 식으로 구조체의 이름항목 변경

    printf("추가할 전화번호: "); scanf("%s", aB_2020[count - 1].phone);

    printf("추가할 주소: "); scanf("%s", aB_2020[count - 1].addr);

    printf("추가할 나이: "); scanf("%d", &aB_2020[count - 1].age); // age는 배열로 선언하지 않았기 때문에 주소에다가 입력을 받아야함

    printf("-------추가 완료------\n");

}


// 과제

//사용자 검색

void search() {
    char name[10];
    
    if (count > 0){
        printf("이름을 입력해 주세요 : ");
        scanf("%s", name);
        
        for (int i = 0; i < 50; i++){ // 주소록 최대 등록수까지 탐색
            if(!strcmp(name, aB_2020[i].name)){  //strcmp는 문자열이 일치할때 0을 반환
                printf("검색성공!\n");
            
                printf("\n 이름 \t\t전화번호 \t\t주소 \t\t나이\n");
                printf("%s\t %s\t %s\t %d\n", aB_2020[i].name, aB_2020[i].phone, aB_2020[i].addr, aB_2020[i].age);
                return;
            }
            
        }
        printf("주소록에서 없는 사람입니다. 대소문자를 확인해 주세요.\n"); //일치하는 이름이 없을시
        return;
    }
    else{ //주소록에 등록된 사람이 없을시
        printf("등록된 사람이 없습니다.");
    }
}
    





//사용자 삭제

void del() {
    char name[10];
    
    if (count > 0){
        printf("이름을 입력해 주세요 : ");
        scanf("%s", name);
        
        for (int i = 0; i < 50; i++){ // 주소록 최대 등록수까지 탐색
            if(!strcmp(name, aB_2020[i].name)){  //strcmp는 문자열이 일치할때 0을 반환
                printf("검색성공!\n");
            
                for (int j = i; j < count ; j++){ // 삭제 하고자 하는 이름 앞부분부터 복사후 삭제하고 싶은 이름부터 덮어쓴다.
                    strcpy(aB_2020[j].name, aB_2020[j+1].name);
                    strcpy(aB_2020[j].phone, aB_2020[j+1].phone);
                    strcpy(aB_2020[j].addr, aB_2020[j+1].addr);
                    aB_2020[j].age = aB_2020[j+1].age;
                        
                    }
                count --; //사람수 1명 삭제
                printf("삭제성공!\n");
                    return;
                    
                }
            
            }
            printf("주소록에서 없는 사람입니다. 대소문자를 확인해 주세요.\n"); //일치하는 이름이 없을시
            return;
        }
        else{ //주소록에 등록된 사람이 없을시
        printf("이미 등록된 사람이 없습니다.");
        
    }
    
    }






void menu()

{

    char choice;

    do {

        printf("\n\n============================================================\n");

        printf("-------------------------- 주소록 메뉴 -------------------------\n");



        printf(" 1) 목록보기 2)사용자 추가 3) 사용자 검색 4) 사용자 삭제 5) 종료\n");

        printf("============================================================\n");



        scanf("%c", &choice); getchar(); //입력중 enter값 제거

        switch (choice) {



        case '1': list(); break;

        case '2': append(); getchar(); break;

        case '3': search(); getchar(); break;

        case '4': del(); getchar(); break;

        case '5': printf("\n 주소록 프로그램을 종료합니다.\n"); return;



        default: printf("메뉴 번호를 다시 확인해주세요\n");

        }

    } while (choice != '5');

}





int main() {

    menu();

}

