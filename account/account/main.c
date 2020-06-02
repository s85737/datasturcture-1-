#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 256
#define MAX_BUF 1024

// add member function

void showMenu();
void memberDel();
void clearBuffer();

void memberAdd(){

  FILE* fd = fopen("/Users/s85737/Documents/2020 1학기/과제/컴공창/5.28/account/account/Student_List.txt", "at");

  if (fd == NULL){
    fprintf(stderr ,"파일을 여는데 실패하였:습니다.\n");
    exit(1);
  }


  char name[MAX_SIZE], email[MAX_SIZE], choice, *result;
  int age,lenName,lenEmail;

  rewind(stdin);

  fprintf(stdout, "이름 : ");
  if((result = fgets(name, sizeof(name), stdin)) != NULL){
    lenName = strlen(name)-1;
    fprintf(fd,"NAME %d %s",lenName, name);
  }else{
    fprintf(stderr, "input error!\n");
    exit(-1);
  }

  fprintf(stdout, "나이: ");
  fscanf(stdin, "%d", &age);
  if(age <= 200 && age >= 0) fprintf(fd,"AGE %d\n", age);
  else{
    rewind(stdin);
    fprintf(stderr, "나이는 음수이거나, 200살을 넘을 수 없습니다. 임의값 21살로 저장됩니다.\n");
    age = 21;
    fprintf(fd,"AGE %d\n", age);

  }

  fprintf(stdout, "이메일 : ");
  fscanf(stdin, "%s", email);
    lenEmail = strlen(email);
      if (lenEmail < 256 && lenEmail >= 0 ) fprintf(fd,"EMAIL %d %s\n",lenEmail, email);
      else {
        fprintf(stderr, "EMAIL 입력이 잘못되었거나, 자리수가 초과하였습니다.\n");
        fputs("Edit it\n",fd);
      }

      fprintf(stdout, "계속 입력할까요? Y/N ");
      fscanf(stdin,"%s", &choice);

      rewind(stdin);
      fclose(fd);

      if(toupper(choice) == 'Y'){
        memberAdd();
      }
      else if(toupper(choice) == 'N'){
        showMenu();
      }
      else{
        fprintf(stderr, "Y/N 둘중 하나만 입력해 주세요. 메뉴로 돌아갑니다.\n");
        showMenu();

      }

      return;

  }


// delete member function
void memberDel(){
    
}

// edit member function
void memberEdit(){
    
     FILE *fd = fopen("/Users/s85737/Documents/2020 1학기/과제/컴공창/5.28/account/account/Student_List.txt", "r+t");
     FILE *fdc = fopen("/Users/s85737/Documents/2020 1학기/과제/컴공창/5.28/account/account/copy.txt", "w+");
     char buffer[MAX_SIZE], *ptr, word[MAX_SIZE], temp[MAX_SIZE], input[MAX_SIZE], *result;
     char cpyBuf[MAX_BUF];
     int wordPo, age, wordSize, intResult, currPo;
     long copySize;
    
    
    rewind(stdin);
    rewind(fd);
    
    if (fd == NULL){
      fprintf(stderr ,"파일을 여는데 실패하였습니다.\n");
      exit(1);
    }
    
     printf("검색할 이름은 ? : ");
     fscanf(stdin, "%s", word);

     while(fgets(buffer, MAX_SIZE, fd) != NULL){
         ptr = strstr(buffer, word);
         if (ptr != NULL){
             wordPo = -1*(strlen(buffer))+5;
             fseek(fd, wordPo, SEEK_CUR);
             fscanf(fd,"%d %s", &wordSize, input); // 글자수를 통한 정확한 검색
             if(wordSize == strlen(word)){
                 currPo = ftell(fd);
                 
                 copySize = currPo - strlen(buffer);
                 intResult = fread(cpyBuf, 1, copySize, fd);
                 if (intResult != copySize){
                     fprintf(stderr,"Reading error");
                     exit(1);
                 }
                 intResult = fwrite(cpyBuf, 1, copySize, fdc);
                 if (intResult != copySize){
                     fprintf(stderr,"writing error");
                     exit(1);
                 }
                 
                 fseek(fd, currPo, SEEK_SET);
                 fgets(temp, MAX_SIZE, fd); //NAME에서 2줄 이동을 위해 fgets 사용
                 fgets(temp, MAX_SIZE, fd);
                 fgets(temp, MAX_SIZE, fd);
                 
                 while(!feof(fd)){
                     fgets(cpyBuf, 1024, fd);
                     fputs(cpyBuf, fdc);
                     cpyBuf[0] = '\0';
                 }
                 
                 
                 
                 fprintf(stdout,"이름: ");
                 rewind(stdin);
                 if((result = fgets(word, sizeof(word), stdin)) != NULL){
                   wordSize = strlen(word)-1;
                   fprintf(fd,"\nNAME %d %s",wordSize, word);
                 }else{
                   fprintf(stderr, "input error!\n");
                   exit(-1);
                 }
                 fprintf(stdout, "나이: ");
                 fscanf(stdin, "%d", &age);
                 if(age <= 200 && age >= 0) fprintf(fd,"AGE %d\n", age);
                 else{
                   rewind(stdin);
                   fprintf(stderr, "나이는 음수이거나, 200살을 넘을 수 없습니다. 임의값 21살로 저장됩니다.\n");
                   age = 21;
                   fprintf(fd,"AGE %d\n", age);

                 }

                 fprintf(stdout, "이메일 : ");
                 fscanf(stdin, "%s", word);
                   wordSize = strlen(word);
                     if (wordSize < 256 && wordSize >= 0 ) fprintf(fd,"EMAIL %d %s\n",wordSize, word);
                     else {
                       fprintf(stderr, "EMAIL 입력이 잘못되었거나, 자리수가 초과하였습니다.\n");
                       fputs("Edit it\n",fd);
                     }
                 
                 fseek(fd, 0, SEEK_END);
                 fseek(fdc,0, SEEK_SET);
                 
                 cpyBuf[0] = '\0';
                 
                 while(!feof(fdc)){
                     fgets(cpyBuf, 1024, fdc);
                     fputs(cpyBuf, fd);
                     cpyBuf[0] = '\0';
                 }
                 fclose(fdc);
                 
             }else{
                 wordPo = fseek(fd, 1, SEEK_CUR);
                 wordPo = ftell(fd);
                 continue;
             }
         }
         
     }
    
     fclose(fd);

}

// show memeber list fucntion
void showList(){

}

//show main menu function
void showMenu(){


  char choice;

  fprintf(stdout, "1. 신규회원 저장\n");
  fprintf(stdout, "2. 회원정보 수정\n");
  fprintf(stdout, "3. 회원 삭제\n");
  fprintf(stdout, "4. 모든 회원 리스트\n");
  fprintf(stdout, "5. 종료\n");
  fprintf(stdout, "입력하세요> ");
  fscanf(stdin, "%c", &choice);

  switch(choice){

    case '1' : memberAdd(); break;
    case '2' : memberEdit(); break;
    case '3' : memberDel(); break;
    case '4' : showList(); break;
    case '5' : fprintf(stdout, "\n 종료합니다. \n"); return;
    default : fprintf(stderr, "\n메뉴 번호를 확인해 주세요\n"); break;//예외처리: 잘못된 번호가 입력되었을 시
  }


}


int main(int argc, char* argv[]){
  showMenu();
}

