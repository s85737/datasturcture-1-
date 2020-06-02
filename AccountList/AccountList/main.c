//
//  main.c
//  AccountList
//
//  Created by 최제현 on 2020/05/28.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LEN 255
#define BUF_SIZE 512


void showList();
void memberAdd();
void memberDel();
void showMenu();
void memberEdit();




int main(int argc, char* argv[]){

  FILE *fd = fopen("Student_List.txt", "a+");

  //예외처리: 파일 열기 실패
  if (fd == NULL){
    fprintf(stderr ,"파일을 여는데 실패하였습니다.\n");
    exit(1);
  }

  showMenu(fd);

  fclose(fd);
}


//show main menu function
void showMenu(FILE* fd){

  char choice;

    fprintf(stdout, "1. 신규회원 저장\n");
    fprintf(stdout, "2. 회원정보 수정\n");
    fprintf(stdout, "3. 회원 삭제\n");
    fprintf(stdout, "4. 모든 회원 리스트\n");
    fprintf(stdout, "5. 종료\n");
    fprintf(stdout, "입력하세요> ");
    fscanf(stdin,"%c", &choice);

    switch(choice){

      case '1' : memberAdd(fd); break;
      case '2' : memberEdit(); break;
      case '3' : memberDel(); break;
      case '4' : showList(); break;
      case '5' : fprintf(stdout, "\n 종료합니다. \n"); return;
      default : fprintf(stderr, "\n메뉴 번호를 확인해 주세요\n"); //예외처리: 잘못된 번호가 입>력되었을 시
    }


}


// add member function
void memberAdd(FILE* fd){

  char buf[BUF_SIZE];
  char choice;

  fprintf(stdout, "\n이름 : ");
  fgets(buf, MAX_LEN, stdin);
  fputs(buf, fd);
  fprintf(stdout, "\n나이: ");
  fprintf(stdout, "\n이메일 : ");
  fprintf(stdout, "\n계속 입력할까요? Y/N ");
  fscanf(stdin,"%s", &choice);
  if(choice == 'Y'){
    memberAdd(fd);
  }
  else if(choice == 'N'){
    showMenu(fd);
  }
  else{
    fprintf(stderr, "Y/N 둘중 하나만 입력해 주세요. 메뉴로 돌아갑니다.\n");
    showMenu(fd);

  }

  return;

}

void memberDel(){
}

// edit member function
void memberEdit(){
}

// show memeber list fucntion
void showList(){

}


