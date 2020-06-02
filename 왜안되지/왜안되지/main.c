#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

//추후 유지보수를 편히 하기위해 100이란 숫자를
//MAX_NUM으로 설정, 100을 200으로 바꾸면
//MAX_NUM은 200이 됨
#define MAX_NUM 100


//사용자의 정보를 저장하는 구조체
typedef struct {
   char name[255];
   char age[200];
   char email[255];
}User;

int saveFile(User* ptr, int* num);
int openFile(User* ptr, int* num);
void insert(User* ptr, int* num);
int deleted(User* ptr, int* num);
void printAll(User* ptr, int* num);



int main(void) {
   int input;
   User user[MAX_NUM]; //사용자 정보를 저장할 구조체 배열
   int person = 0; //저장된 user수

   openFile(user, &person);//저장된 데이터를 불러오는 함수

   //메뉴 선택
   while (1) {
      printf("1. 신규회원 저장 \n");
      printf("2. 회원정보 수정 \n"); // 추가해야 할 항목
      printf("3. 회원 삭제 \n");
      printf("4. 모든 회원 리스트 \n");
      printf("5. 종료 \n");
      
      printf("입력하세요> ");
      scanf("%d", &input);

      if (input == 1) {
         insert(user, &person);
      }

      else if (input == 3) {
         deleted(user, &person);
      }
      else if (input == 4) {
         printAll(user, &person);
      }
      else if (input == 5) {
         saveFile(user, &person);
         return 0;
      }
      else
         printf("\n에러! 다시시도! \n\n");
   }

   return 0;

}

//데이터를 파일에 저장하는 함수
int saveFile(User* ptr, int* num) {

   if (*num > 0) {
      int i, state;
      FILE* fp = fopen("UserInfo.txt", "wt");
      /* fopen함수는 오류발생시 NULL을 리턴하므로
      파일 개방 중 오류발생시 프로그램을 종료 */
      if (fp == NULL) {
         printf("File Open Error!\n");
         return 1;
      }

      //구조체 배열에 저장된 데이터를 파일에 저장
      //줄바꿈으로 구분하여 저장
      for (i = 0; i < *num; i++) {
         fprintf(fp, "%s %s %s", ptr[i].name, ptr[i].age, ptr[i].email);
         fputc('\n', fp);
      }



      /* fclose함수는 종료시 오류가 발생하면
      0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
      안내후 프로그램을 종료 */
      state = fclose(fp);
      if (state != 0) {
         printf("File Close Error!\n");
         return 1;
      }
      printf("종료합니다. \n");
      return 0;
   }

   else {
      printf("종료합니다. \n");
      return 0;
   }
}



//파일로부터 데이터를 불러오는 함수
int openFile(User* ptr, int* num) {
   int state;
   //char temp; //뭔지 모르겠음
   FILE* fp = fopen("UserInfo.txt", "rt");

   if (fp == NULL) {
      printf("File Open Error!\n");
      return 0;
   }



   //파일에 저장된 데이터를 구조체 배열에 저장
   while (1) {
      fscanf(fp, "%s %s %s", ptr[*num].name, ptr[*num].age, ptr[*num].email);
      if (feof(fp) != 0)
         break;
      (*num)++;
   }
   

   /* fclose함수는 종료시 오류가 발생하면
   0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
   안내후 프로그램을 종료 */
   state = fclose(fp);
   if (state != 0) {
      printf("File Close Error!\n");
      return 1;
   }

   return 0;
}



//사용자의 정보를 삽입하는 함수
void insert(User* ptr, int* num) {

   char name;
   char age;
   char email;

   FILE * fp;
   char ch;//데이터 추가 계속
   char file[100];
   char buffer[100];


   //유저정보가 꽉 차지 않으면
   if (input == 1) { //*num < MAX_NUM
      do {
         //1.신규회원 입력받기
         printf("이름: ");
         scanf("%s", &name);
         char str[100]; //공백받기
         fgets(str, sizeof(str), stdin);
         str[strlen(str) - 1] = '\0';

         printf("나이: ");
         scanf("%s", &age);
         

         printf("이메일: ");
         scanf("%s", &email);


         fprintf(fp, "%s %s %s",&name, &age, &email);
            //데이터 추가 계속?(Y/N)
         printf("데이터 추가를 계속?(Y/N): ");
         scanf(" %s", &ch);
         printf("\n");
      } while (ch != 'N');
         printf("입력이 완료되었습니다. \n\n");
      }

   //유저 정보가 꽉 차면
   else
      printf("  Data Full \n\n");

}





//사용자의 정보를 삭제하는 함수
int deleted(User* ptr, int* num) {
   char name[30];
   int i, j;



   //유저 정보가 한개라도 남아있으면
   if (*num > 0) {
      printf("Input Name: ");
      scanf("%s", name);



      for (i = 0; i < MAX_NUM; i++) {
         //문자열이므로 비교하기위해 strcmp사용
         if (strcmp(name, ptr[i].name) == 0) {

            (*num)--;
            printf("  Data Deleted \n\n");

            //데이터가 가득 차지 않았다면
            if (i != MAX_NUM - 1) {
               for (j = i; j < MAX_NUM; j++) {
                  //문자열이므로 strcpy를 사용하여 데이터 복사
                  strcpy(ptr[j].name, ptr[j + 1].name);
                  strcpy(ptr[j].age, ptr[j + 1].age);
                  strcpy(ptr[j].email, ptr[j + 1].email);
               }
               //구조체 배열의 마지막을 NULL로 바꿈 -> 오류떠서 0으로 바꿈
               *ptr[MAX_NUM - 1].name = 0;
               *ptr[MAX_NUM - 1].age = 0;
               *ptr[MAX_NUM - 1].email = 0;
            }


            //데이터가 가득 찼다면
            else {
               //구조체 배열의 마지막을 NULL로 바꿈 -> 오류떠서 0으로 바꿨음
               *ptr[MAX_NUM - 1].name = 0;
               *ptr[MAX_NUM - 1].age = 0;
               *ptr[MAX_NUM - 1].email = 0;
            }
            return 0;
         }
      }
      printf("Not Found \n\n");
      return 0;
   }


   //저장된 유저 정보가 없다면
   else {
      printf("  No Data \n\n");
      return 0;
   }
}

//저장된 모든 이름과 나이, 이메일 정보를 출력하는 함수
void printAll(User* ptr, int* num) {
   int i = 0;
   
   //원래 출력되어야 하는 함수
      printf("HONG GIL DONG / 20 / hong@gmail.com \n");
   printf("PARK GIL DONG / 20 / parkpark@hotmail.com \n");

   if (*num > 0) {
      for (i = 0; i < *num; i++) {
         printf("Name : %s ", ptr[i].name);
         printf("Age : %s ", ptr[i].age);
         printf("Email : %s \n", ptr[i].email);
      }
      printf("  Data Print \n\n");
   }
   else
      printf("  No Data \n\n");
}
